#ifndef CAPTURE3_CAMERA_CONNECTION_H
#define CAPTURE3_CAMERA_CONNECTION_H


#include <gphoto2/gphoto2-camera.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-widget.h>
#include <gphoto2/gphoto2-port.h>
#include <gphoto2/gphoto2-port-info-list.h>
#include <gphoto2/gphoto2-abilities-list.h>
#include <gphoto2/gphoto2-file.h>
#include <omp.h>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QFileInfo>
#include <QtGui/QImage>


#include "CameraPreview.h"


namespace Capture3
{
	class CameraConnection final
	{
		public:
			CameraConnection(
				const QString &cameraModel,
				const QString &cameraPort
			);

			virtual ~CameraConnection();

			bool connect();

			void disconnect();

			CameraPreview capturePreview();

			void capture(const QString &path);

			void getValue(const QString &name, QVariant &var);

			void setValue(const QString &name, const QVariant &var);

		private:
			const QString cameraModel;
			const QString cameraPort;
			bool connected;
			Camera *camera;
			GPContext *context;
			GPPortInfoList *cameraPortInfoList;
			GPPortInfo cameraPortInfo;
			CameraAbilitiesList *cameraAbilitiesList;
			CameraAbilities cameraAbilities;
			char *cameraPortInfoName;
			char *cameraPortInfoPath;
			int indexPort;
			int indexModel;
	};
}


#endif // CAPTURE3_CAMERA_CONNECTION_H
