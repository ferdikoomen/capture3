#include "PanelTabsComponent.h"


namespace Capture3
{

	PanelTabsComponent::PanelTabsComponent() :
		QFrame(),
		layout(),
		tabs(),
		menu(),
		action1("Action 1"),
		action2("Action 2"),
		action3("Action 3"),
		action4("Action 4"),
		button("⋮", &tabs),
		open(true)
	{
		// Allow tabs to focus
		setFocusPolicy(Qt::StrongFocus);

		// Add items
		layout.setSpacing(0);
		layout.setMargin(0);
		layout.setContentsMargins(0, 0, 0, 0);
		layout.setAlignment(Qt::AlignTop | Qt::AlignLeft);
		layout.addWidget(&tabs);
		setLayout(&layout);

		// Add menu options
		menu.addAction(&action1);
		menu.addAction(&action2);
		menu.addAction(&action3);
		menu.addAction(&action4);

		// Install event filter to listen to double clicks on tabs
		tabs.tabBar()->installEventFilter(this);

		// Link events
		QObject::connect(&button, &QPushButton::clicked, this, &PanelTabsComponent::showMenu);
	}


	PanelTabsComponent::~PanelTabsComponent()
	{
		QObject::disconnect(&button, nullptr, nullptr, nullptr);

		action1.deleteLater();
		action2.deleteLater();
		action3.deleteLater();
		action4.deleteLater();
		menu.deleteLater();
		button.deleteLater();
		tabs.deleteLater();
		layout.deleteLater();
	}


	void PanelTabsComponent::addTab(PanelTabComponent *tab)
	{
		// Add tab and listen to focus signals from childeren
		QObject::connect(tab, &PanelTabComponent::onFocusIn, this, &PanelTabsComponent::focusIn);
		QObject::connect(tab, &PanelTabComponent::onFocusOut, this, &PanelTabsComponent::focusOut);
		tabs.addTab(tab, tab->getName());
	}


	void PanelTabsComponent::focusIn()
	{
		// Set class name and redraw
		setObjectName("focus");
		style()->unpolish(&tabs);
		style()->unpolish(tabs.tabBar());
		style()->polish(&tabs);
		style()->polish(tabs.tabBar());
		update();
	}


	void PanelTabsComponent::focusOut()
	{
		// Set class name and redraw
		setObjectName("");
		style()->unpolish(&tabs);
		style()->unpolish(tabs.tabBar());
		style()->polish(&tabs);
		style()->polish(tabs.tabBar());
		update();
	}


	void PanelTabsComponent::showMenu()
	{
		// Show popup menu
		menu.popup(mapToGlobal(QPoint(
			button.x(), button.y() + button.height()
		)));
	}


	void PanelTabsComponent::resizeEvent(QResizeEvent *event)
	{
		QFrame::resizeEvent(event);

		if (width() > tabs.tabBar()->width() + button.width()) {
			button.show();
		} else {
			button.hide();
		}

		button.move(width() - button.width(), 0);
	}


	bool PanelTabsComponent::eventFilter(QObject *watcher, QEvent *event)
	{
		// Toggle height when double clicked
		if (event->type() == QEvent::MouseButtonDblClick) {
			if (open) {
				open = false;
				tabs.setEnabled(false);
				tabs.setObjectName("disabled");
				setMaximumHeight(tabs.tabBar()->height() + 2);
				releaseKeyboard();
				focusOut();
			} else {
				open = true;
				tabs.setEnabled(true);
				tabs.setObjectName("");
				setMaximumHeight(QWIDGETSIZE_MAX);
				grabKeyboard();
				focusIn();
			}
		}

		return QWidget::eventFilter(watcher, event);
	}


	void PanelTabsComponent::focusInEvent(QFocusEvent *event)
	{
		// Draw focus border around tab when child item gets focus
		if (tabs.isEnabled()) {
			QFrame::focusInEvent(event);
			grabKeyboard();
			focusIn();
		} else {
			event->ignore();
		}
	}


	void PanelTabsComponent::focusOutEvent(QFocusEvent *event)
	{
		// Remove focus border around tab when child item lost focus
		if (tabs.isEnabled()) {
			QFrame::focusOutEvent(event);
			releaseKeyboard();
			focusOut();
		} else {
			event->ignore();
		}
	}
}