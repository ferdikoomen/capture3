#ifndef CAPTURE3_PROGRESS_DIALOG_COMPONENT_H
#define CAPTURE3_PROGRESS_DIALOG_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QProgressDialog>


namespace Capture3
{
	class ProgressDialogComponent : public QProgressDialog
	{
		Q_OBJECT

		public:
			ProgressDialogComponent();

			virtual ~ProgressDialogComponent();

		protected:

		private:

	};
}


#endif // CAPTURE3_PROGRESS_DIALOG_COMPONENT_H
