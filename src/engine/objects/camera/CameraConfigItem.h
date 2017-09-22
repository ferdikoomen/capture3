#ifndef CAPTURE3_CAMERA_CONFIG_ITEM_H
#define CAPTURE3_CAMERA_CONFIG_ITEM_H


#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>


#include "CameraConnection.h"


namespace Capture3
{
	class CameraConfigItem final
	{
		public:
			CameraConfigItem(
				const QString &name,
				CameraConnection &connection
			);

			virtual ~CameraConfigItem();

			const QVariant &getValue();

			void setValue(const QString &value);

			void setValue(const int value);

			void setValue(const unsigned int value);

			void setValue(const double value);

			void toggle();

			void write();

		private:
			const QString name;
			CameraConnection &connection;
			QVariant var;
	};
}

#endif // CAPTURE3_CAMERA_CONFIG_ITEM_H
