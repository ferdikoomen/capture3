#include "CameraConfigItem.h"


namespace Capture3
{

	CameraConfigItem::CameraConfigItem(
		const QString &name,
		CameraConnection &connection
	) :
		name(name),
		connection(connection),
		var()
	{
		//
	}


	CameraConfigItem::~CameraConfigItem()
	{
		//
	}


	const QVariant &CameraConfigItem::getValue()
	{
		connection.getValue(name, var);
		return var;
	}


	void CameraConfigItem::setValue(const QString &value)
	{
		var.setValue(value);
		write();
	}


	void CameraConfigItem::setValue(const int value)
	{
		var.setValue(value);
		write();
	}


	void CameraConfigItem::setValue(const unsigned int value)
	{
		var.setValue(value);
		write();
	}


	void CameraConfigItem::setValue(const double value)
	{
		var.setValue(value);
		write();
	}


	void CameraConfigItem::toggle()
	{
		var.setValue(var.toInt() == 0 ? 1 : 0);
		write();
	}


	void CameraConfigItem::write()
	{
		connection.setValue(name, var);
	}
}