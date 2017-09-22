#include "CameraConnection.h"


namespace Capture3
{

	CameraConnection::CameraConnection(
		const QString &cameraModel,
		const QString &cameraPort
	) :
		cameraModel(cameraModel),
		cameraPort(cameraPort),
		connected(false)
	{
		connect();
	}


	CameraConnection::~CameraConnection()
	{
		disconnect();
	}


	bool CameraConnection::connect()
	{
		// Kill any USB processes
		system("killall PTPCamera");

		// Create new camera object
		gp_camera_new(&camera);

		// Create camera context
		context = gp_context_new();

		// Find port
		gp_port_info_list_new(&cameraPortInfoList);
		gp_port_info_list_load(cameraPortInfoList);
		indexPort = gp_port_info_list_lookup_path(cameraPortInfoList, cameraPort.toLatin1().constData());

		// Find port information
		gp_port_info_new(&cameraPortInfo);
		gp_port_info_list_get_info(cameraPortInfoList, indexPort, &cameraPortInfo);

		// Find port name and path
		gp_port_info_get_name(cameraPortInfo, &cameraPortInfoName);
		gp_port_info_get_path(cameraPortInfo, &cameraPortInfoPath);

		// Find camera model
		gp_abilities_list_new(&cameraAbilitiesList);
		gp_abilities_list_load(cameraAbilitiesList, context);
		indexModel = gp_abilities_list_lookup_model(cameraAbilitiesList, cameraModel.toLatin1().constData());

		// Find camera model options
		gp_abilities_list_get_abilities(cameraAbilitiesList, indexModel, &cameraAbilities);
		gp_camera_set_port_info(camera, cameraPortInfo);
		gp_camera_set_abilities(camera, cameraAbilities);

		// Init camera (can take up to 10 seconds)
		connected = (gp_camera_init(camera, context) == GP_OK);
		return connected;
	}


	void CameraConnection::disconnect()
	{
		gp_port_info_list_free(cameraPortInfoList);
		gp_abilities_list_free(cameraAbilitiesList);
		gp_camera_exit(camera, context);
		gp_camera_unref(camera);
		gp_context_unref(context);
		camera = nullptr;
		context = nullptr;
		connected = false;
	}


	CameraPreview CameraConnection::capturePreview()
	{
		// Return object (NULL by default)
		CameraPreview image;

		if (connected) {

			// Create preview file handler
			CameraFile *file;
			gp_file_new(&file);

			// Capture preview
			if (gp_camera_capture_preview(camera, file, context) == GP_OK) {

				// Read data (JPEG format)
				const char *fileData;
				unsigned long int fileSize;
				gp_file_get_data_and_size(file, &fileData, &fileSize);

				// Parse jpeg data
				image.load(fileData, fileSize);
			}

			// Cleanup file handler
			gp_file_free(file);
		}

		return image;
	}


	void CameraConnection::capture(const QString &path)
	{
		if (connected) {

			// Flags
			bool success = false;
			unsigned int count = 0;

			// In some cases the capture does not record a file, this can be due
			// to focus issues, camera connection, etc, etc. So we want to try
			// to capture a file (with a max of 3x).
			while (!success && count < 3) {

				// Start capture
				if (gp_camera_trigger_capture(camera, context) != GP_OK) {

					// Wait until capture is done
					while (true) {

						// Receive events from camera
						CameraEventType eventType;
						void *eventData;
						if (gp_camera_wait_for_event(camera, 1000, &eventType, &eventData, context) != GP_OK) {
							count++;
							break;
						}

						// When we receive a file, we create new camera RAW object,
						// this is a basic container that holds the references to the file object.
						if (eventType == GP_EVENT_FILE_ADDED) {

							// Fetch file path on camera
							auto *filePath = (CameraFilePath *) eventData;
							char *fileFolder = strdup(filePath->folder);
							char *fileName = strdup(filePath->name);

							// Download file and delete from camera
							QFile output(path);
							output.open(QIODevice::WriteOnly);
							CameraFile *file;
							gp_file_new_from_fd(&file, output.handle());
							gp_camera_file_get(camera, fileFolder, fileName, GP_FILE_TYPE_NORMAL, file, context);
							gp_camera_file_delete(camera, fileFolder, fileName, context);
							gp_file_free(file);
							output.close();

							// Done!
							success = true;
						}

						// Capture is done (does not mean we have a file)
						if (eventType == GP_EVENT_CAPTURE_COMPLETE) {
							count++;
							break;
						}
					}

				} else {
					count++;
				}
			}
		}
	}


	void CameraConnection::getValue(const QString &name, QVariant &var)
	{
		// Find widget value and return as a string
		if (connected) {

			// Grab widget
			CameraWidget *widget;
			if (gp_camera_get_single_config(camera, name.toLatin1().constData(), &widget, context) == GP_OK) {

				// Grab widget type
				CameraWidgetType type;
				if (gp_widget_get_type(widget, &type) == GP_OK) {

					// Store value
					const char *value = nullptr;
					if (gp_widget_get_value(widget, &value) == GP_OK) {
						if (value != nullptr) {
							var.setValue(QString(strdup(value)));
						}
					}
				}
			}
		}
	}


	void CameraConnection::setValue(const QString &name, const QVariant &var)
	{
		if (connected) {

			// Grab widget
			CameraWidget *widget;
			if (gp_camera_get_single_config(camera, name.toLatin1().constData(), &widget, context) == GP_OK) {

				// Grab widget type
				CameraWidgetType type;
				if (gp_widget_get_type(widget, &type) == GP_OK) {

					// Grab widget read/write status
					int readonly;
					gp_widget_get_readonly(widget, &readonly);

					// Write value based on type
					if (!readonly) {

						// Possible values
						int valueInt;
						float valueFloat;
						QString valueString;

						switch (type) {

							case GP_WIDGET_TOGGLE:
								valueInt = var.toInt();
								gp_widget_set_value(widget, &valueInt);
								gp_camera_set_single_config(camera, name.toLatin1().constData(), widget, context);
								break;

							case GP_WIDGET_RANGE:
								valueFloat = var.toFloat();
								gp_widget_set_value(widget, &valueFloat);
								gp_camera_set_single_config(camera, name.toLatin1().constData(), widget, context);
								break;

							case GP_WIDGET_TEXT:
							case GP_WIDGET_RADIO:
							case GP_WIDGET_MENU:
							default:
								valueString = var.toString();
								gp_widget_set_value(widget, valueString.toLatin1().constData());
								gp_camera_set_single_config(camera, name.toLatin1().constData(), widget, context);
								break;
						}
					}
				}
			}
		}
	}

}