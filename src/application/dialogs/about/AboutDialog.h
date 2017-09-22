#ifndef CAPTURE3_ABOUT_DIALOG_H
#define CAPTURE3_ABOUT_DIALOG_H


#include <QtWidgets/QWidget>


namespace Capture3
{
	class AboutDialog final : public QWidget
	{
		Q_OBJECT

		public:
			AboutDialog();

			virtual ~AboutDialog();

	};
}


#endif // CAPTURE3_ABOUT_DIALOG_H
