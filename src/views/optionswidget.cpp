#include "optionswidget.h"




OptionsWidget::OptionsWidget(QWidget* parent, int layoutOption) : QLabel(parent) {
	setStyleSheet("background-color: #252526;");

	viewModel = new OptionsViewModel();

	QObject::connect(this, &OptionsWidget::pushbackMenuLabelSignal, viewModel, &OptionsViewModel::pushbackMenuLabel);
	QObject::connect(this, &OptionsWidget::moveSelectionPointSignal, viewModel, &OptionsViewModel::moveSelectionPoint);
	QObject::connect(this, &OptionsWidget::buildRecordsLabelsSignal, viewModel, &OptionsViewModel::buildRecordsLabels);
	QObject::connect(this, &OptionsWidget::buildSoundKeyLabelsSignal, viewModel, &OptionsViewModel::buildSoundKeyLabels);
	QObject::connect(this, &OptionsWidget::setInitialSelectionPointSignal, viewModel, &OptionsViewModel::setInitialSelectionPoint);
	QObject::connect(viewModel, &OptionsViewModel::repaintOptionsSignal, this, &OptionsWidget::repaintOptions);
	QObject::connect(viewModel, &OptionsViewModel::addNewLabelSignal, this, &OptionsWidget::addNewLabel);

	buildMainUi(layoutOption);
}


OptionsWidget::~OptionsWidget() {
	if (menuOptionsVerticalLayout != nullptr)
		delete menuOptionsVerticalLayout;
	if (menuOptionsHorizontalLayout != nullptr)
	{
		delete firstLabelLayout;
		delete firstHalfLabel;
		delete secondLabelLayout;
		delete secondHalfLabel;
		delete menuOptionsHorizontalLayout;
	}
}


void OptionsWidget::buildMainUi(int layoutOption) {
	switch (layoutOption) {
	case 0:
		setFixedSize(380, 450);
		menuOptionsVerticalLayout = new QVBoxLayout(this);

		emit pushbackMenuLabelSignal(new MenuLabelWidget(this, RECORD_SOUND), menuOptionsVerticalLayout);
		emit pushbackMenuLabelSignal(new MenuLabelWidget(this, RECORDS_MENU), menuOptionsVerticalLayout);
		emit pushbackMenuLabelSignal(new MenuLabelWidget(this, CHANGE_KEYS), menuOptionsVerticalLayout);

		break;
	case 1:
		setFixedSize(380, 700);
		menuOptionsVerticalLayout = new QVBoxLayout(this);

		emit pushbackMenuLabelSignal(new MenuLabelWidget(this, STOP_RECORDING), menuOptionsVerticalLayout);

		break;
	case 2:
		setFixedSize(380, 550);
		menuOptionsVerticalLayout = new QVBoxLayout(this);
		buildRecordsLabels();

		break;
	case 3:
		setFixedSize(380, 670);
		menuOptionsHorizontalLayout = new QHBoxLayout(this);
		buildSoundKeyLabels();

		break;
	}
	setInitialSelectionPoint(layoutOption);
}


void OptionsWidget::buildRecordsLabels() {
	emit pushbackMenuLabelSignal(new MenuLabelWidget(this, BACK_TO_MAIN), menuOptionsVerticalLayout, 20);
	emit buildRecordsLabelsSignal(menuOptionsVerticalLayout);
}


void OptionsWidget::buildSoundKeyLabels() {

	firstHalfLabel = new KeyOptionLabel(this), secondHalfLabel = new KeyOptionLabel(this);
	firstHalfLabel->setFixedSize(200, 650);
	secondHalfLabel->setFixedSize(150, 650);

	firstLabelLayout = new QVBoxLayout(firstHalfLabel), secondLabelLayout = new QVBoxLayout(secondHalfLabel);

	emit pushbackMenuLabelSignal(new MenuLabelWidget(this, BACK_TO_MAIN), firstLabelLayout, 20);
	emit buildSoundKeyLabelsSignal(firstLabelLayout, secondLabelLayout);

	menuOptionsHorizontalLayout->addWidget(firstHalfLabel);
	menuOptionsHorizontalLayout->addWidget(secondHalfLabel);
}


void OptionsWidget::moveSelectionPointOption(int option) {
	emit moveSelectionPointSignal(option, menuOptionsHorizontalLayout, firstHalfLabel, secondHalfLabel);
};


void OptionsWidget::moveSelectionPoint(MenuLabelWidget* option) {
	if (option != nullptr)
	{
		selectionPointX = option->x() - 20;
		selectionPointY = option->y() + option->height() / 2;
		repaint();
	}
};


void OptionsWidget::setInitialSelectionPoint(int layoutOption) {
	switch (layoutOption) {
	case 0:
		selectionPointX = 64;
		selectionPointY = 79;
		repaint();
		break;
	case 1:
		selectionPointX = 77;
		selectionPointY = 350;
		repaint();
		break;
	case 2:
		selectionPointX = 123;
		selectionPointY = 40;
		repaint();
		break;
	case 3:
		if (!KeyboardData::changeSoundKeyValue)
		{
			firstHalfLabel->setSelectionPointX(33);
			firstHalfLabel->setSelectionPointY(35);
			firstHalfLabel->repaint();
		}
		break;
	}
};


void OptionsWidget::paintEvent(QPaintEvent* paintEvent) {

	if (selectionPointX != NULL && selectionPointY != NULL)
	{
		QPainter painter(this);

		painter.setRenderHint(QPainter::Antialiasing);

		painter.setPen(QPen(Qt::black, 3));
		painter.setBrush(QBrush(Qt::white));

		painter.drawEllipse(QPoint(selectionPointX, selectionPointY), 10, 10);
	}
}


bool OptionsWidget::isHorizontalLayoutPresent()
{
	bool logic;
	if (menuOptionsHorizontalLayout == nullptr)
		logic = false;
	else
		logic = true;

	return logic;
}


void OptionsWidget::repaintOptions(int pointX, int pointY) {
	selectionPointX = pointX;
	selectionPointY = pointY;
	repaint();
}

void OptionsWidget::addNewLabel(std::string labelText, int height, QVBoxLayout* layout) {
	emit pushbackMenuLabelSignal(new MenuLabelWidget(this, labelText), layout, 20);
}