#ifndef CAPTURE3_PROGRESS_BAR_COMPONENT_H
#define CAPTURE3_PROGRESS_BAR_COMPONENT_H


#include <QtWidgets/QWidget>
#include <QtWidgets/QProgressBar>


namespace Capture3
{
	class ProgressBarComponent : public QProgressBar
	{
		Q_OBJECT

		public:
			ProgressBarComponent();

			virtual ~ProgressBarComponent();

		protected:

		private:

	};
}


#endif // CAPTURE3_PROGRESS_BAR_COMPONENT_H
