#include "menuwidget.h"



MenuWidget::MenuWidget(QWidget* parent)
	: QLabel(parent) {
	setStyleSheet("background-color: #1f1f1f;");
	setFixedSize(458, 770);

	viewModel = new MenuViewModel();

	QObject::connect(this, &MenuWidget::selectOptionSignal, viewModel, &MenuViewModel::selectOption);
	QObject::connect(this, &MenuWidget::leftRelativeOptionSignal, viewModel, &MenuViewModel::leftRelativeOption);
	QObject::connect(this, &MenuWidget::rightRelativeOptionSignal, viewModel, &MenuViewModel::rightRelativeOption);
	QObject::connect(this, &MenuWidget::nextOptionSignal, viewModel, &MenuViewModel::nextOption);
	QObject::connect(this, &MenuWidget::prevOptionSignal, viewModel, &MenuViewModel::prevOption);
	QObject::connect(this, &MenuWidget::changeSoundKeyPairSignal, viewModel, &MenuViewModel::changeSoundKeyPair);

	QObject::connect(viewModel, &MenuViewModel::rebuildUISignal, this, &MenuWidget::rebuildUI);
	QObject::connect(viewModel, &MenuViewModel::displaySelectedAudioSignal, this, &MenuWidget::displaySelectedAudio);

	menuWidgetLayout = new QVBoxLayout(this);
	buildUi();
}


MenuWidget::~MenuWidget() {

};



void MenuWidget::buildUi(int layoutOption) {
	menuInfoWidget = new InfoWidget(this, layoutOption);
	menuWidgetLayout->addWidget(menuInfoWidget, 0, Qt::AlignHCenter);
	menuOptionsWidget = new OptionsWidget(this, layoutOption);
	menuWidgetLayout->addWidget(menuOptionsWidget, 0, Qt::AlignHCenter);

	QObject::connect(viewModel, &MenuViewModel::moveSelectionPointSignal, menuOptionsWidget, &OptionsWidget::moveSelectionPointOption);
}


void MenuWidget::rebuildUI(int layoutOption) {

	menuWidgetLayout->removeWidget(menuInfoWidget);
	delete menuInfoWidget;
	menuWidgetLayout->removeWidget(menuOptionsWidget);
	delete menuOptionsWidget;

	buildUi(layoutOption);
}


void MenuWidget::displaySelectedAudio(int option) {
	emit displaySelectedAudioSignal(option);
}