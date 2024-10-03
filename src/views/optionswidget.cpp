#include "optionswidget.h"



MenuLabelWidget::MenuLabelWidget(QWidget* parent, std::string text) : QLabel(parent) {
	setStyleSheet("border: none; color: white;");
	setText(QString::fromStdString(text));
	adjustSize();
	setFont(FONT);
}

KeyOptionLabel::KeyOptionLabel(QWidget* parent) : QLabel(parent) {}


void KeyOptionLabel::paintEvent(QPaintEvent* paintEvent) {

	if (selectionPointX != NULL && selectionPointY != NULL)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::black, 3));
		painter.setBrush(QBrush(Qt::white));

		painter.drawEllipse(QPoint(selectionPointX, selectionPointY), 8, 8);
	}
}


void KeyOptionLabel::moveSelectionPoint(MenuLabelWidget* option) {
	selectionPointX = option->x() - 20;
	selectionPointY = option->y() + option->height() / 2;
	repaint();
};


MenuInfoWidget::MenuInfoWidget(QWidget* parent, int layoutOption) : QLabel(parent) {
	setStyleSheet("background-color: #1f1f1f;");
	menuInfoLayout = new QVBoxLayout(this);
	buildMainUi(layoutOption);
}


void MenuInfoWidget::buildMainUi(int layoutOption) {
	switch (layoutOption) {
		case 0:
			setFixedSize(380, 250);
			menuInfoLayout->addWidget(new MenuLabelWidget(this, ESCAPE_TEXT), 0, Qt::AlignHCenter);
			menuInfoLayout->addWidget(new MenuLabelWidget(this, ENTER_TEXT), 0, Qt::AlignHCenter);
			menuInfoLayout->addWidget(new MenuLabelWidget(this, UP_DOWN_TEXT), 0, Qt::AlignHCenter);
			break;
		case 1:
			setFixedSize(380, 0);
			break;
		case 2:
			setFixedSize(380, 150);
			menuInfoLayout->addWidget(new MenuLabelWidget(this, ENTER_RECORD_TEXT), 0, Qt::AlignHCenter);
			menuInfoLayout->addWidget(new MenuLabelWidget(this, UP_DOWN_TEXT), 0, Qt::AlignHCenter);
			break;
		case 3:
			setFixedSize(380, 70);
			if (KeyboardData::changeSoundKeyValue)
				menuInfoLayout->addWidget(new MenuLabelWidget(this, CHANGE_KEY_TEXT), 0, Qt::AlignHCenter);
			else
				menuInfoLayout->addWidget(new MenuLabelWidget(this, SELECT_SOUND_TEXT), 0, Qt::AlignHCenter);
			break;
	}
}


MenuOptionsWidget::MenuOptionsWidget(QWidget* parent, int layoutOption) : QLabel(parent) {
	setStyleSheet("background-color: #252526;");
	optionsPtrVector = new std::vector<MenuLabelWidget*>;
	buildMainUi(layoutOption);
}


MenuOptionsWidget::~MenuOptionsWidget() {
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
		
	delete optionsPtrVector;
}


void MenuOptionsWidget::buildMainUi(int layoutOption) {
	switch (layoutOption) {
	case 0:
		setFixedSize(380, 450);
		menuOptionsVerticalLayout = new QVBoxLayout(this);
		optionsPtrVector->push_back(new MenuLabelWidget(this, RECORD_SOUND));
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
		optionsPtrVector->push_back(new MenuLabelWidget(this, RECORDS_MENU));
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
		optionsPtrVector->push_back(new MenuLabelWidget(this, CHANGE_KEYS));
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
		moveSelectionPoint(0);
		break;
	case 1:
		setFixedSize(380, 700);
		menuOptionsVerticalLayout = new QVBoxLayout(this);
		optionsPtrVector->push_back(new MenuLabelWidget(this, STOP_RECORDING));
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
		moveSelectionPoint(0);
		break;
	case 2:
		setFixedSize(380, 550);
		menuOptionsVerticalLayout = new QVBoxLayout(this);
		optionsPtrVector->push_back(new MenuLabelWidget(this, BACK_TO_MAIN));
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
		optionsPtrVector->back()->setFixedHeight(20);
		buildRecordsLabels();
		moveSelectionPoint(0);
		break;
	case 3:
		setFixedSize(380, 670);
		menuOptionsHorizontalLayout = new QHBoxLayout(this);
		optionsPtrVector->push_back(new MenuLabelWidget(this, BACK_TO_MAIN));
		buildSoundKeyLabels();
		moveSelectionPoint(0);
		break;
	}
	setInitialSelectionPoint(layoutOption);
}


void MenuOptionsWidget::buildRecordsLabels() {

	for (int i = 0; i < NoteData::recordedTracks->size(); i++)
	{
		optionsPtrVector->push_back(new MenuLabelWidget(this, std::to_string(i+1)));
		optionsPtrVector->back()->setFixedHeight(20);
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
	}
	for (int i = 0; i < 10 - NoteData::recordedTracks->size(); i++)
	{
		optionsPtrVector->push_back(new MenuLabelWidget(this, "-"));
		optionsPtrVector->back()->setFixedHeight(20);
		menuOptionsVerticalLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
	}

}


void MenuOptionsWidget::buildSoundKeyLabels() {

	firstHalfLabel = new KeyOptionLabel(this), secondHalfLabel = new KeyOptionLabel(this);
	firstHalfLabel->setFixedSize(200, 650);
	secondHalfLabel->setFixedSize(150, 650);

	firstLabelLayout = new QVBoxLayout(firstHalfLabel), secondLabelLayout = new QVBoxLayout(secondHalfLabel);

	std::vector<std::string>* labels = NoteData::getSoundToKeyStrings();
	auto middle = labels->begin() + labels->size() / 2;
	std::vector<std::string> firstHalf(labels->begin(), middle), secondHalf(middle, labels->end());

	optionsPtrVector->back()->setFixedHeight(20);
	firstLabelLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);

	for (std::string text : firstHalf)
	{
		optionsPtrVector->push_back(new MenuLabelWidget(this, text));
		optionsPtrVector->back()->setFixedHeight(20);
		firstLabelLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
	}
	for (std::string text : secondHalf)
	{
		optionsPtrVector->push_back(new MenuLabelWidget(this, text));
		optionsPtrVector->back()->setFixedHeight(20);
		secondLabelLayout->addWidget(optionsPtrVector->back(), 0, Qt::AlignHCenter);
	}

	menuOptionsHorizontalLayout->addWidget(firstHalfLabel);
	menuOptionsHorizontalLayout->addWidget(secondHalfLabel);

	delete labels;
}


void MenuOptionsWidget::moveSelectionPoint(int option) {

	std::vector<MenuLabelWidget*> optionsVector = *optionsPtrVector;

	if (!optionsVector.empty())
	{
		if (menuOptionsHorizontalLayout != nullptr)
		{
			if(option < 15)
			{
				firstHalfLabel->moveSelectionPoint(optionsVector[option]);
				secondHalfLabel->resetSelectionPoint();
				secondHalfLabel->repaint();
			}
			else
			{
				firstHalfLabel->resetSelectionPoint();
				firstHalfLabel->repaint();
				secondHalfLabel->moveSelectionPoint(optionsVector[option]);
			}
			moveSelectionPoint(nullptr);
		}
		else
			moveSelectionPoint(optionsVector[option]);
	}
	else
	{
		selectionPointX = -100;
		selectionPointY = -100;
		repaint();
	}
};


void MenuOptionsWidget::moveSelectionPoint(MenuLabelWidget* option ) {
	if (option != nullptr)
	{
		selectionPointX = option->x() - 20;
		selectionPointY = option->y() + option->height() / 2;
		repaint();
	}
};


void MenuOptionsWidget::setInitialSelectionPoint(int layoutOption) {
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


void MenuOptionsWidget::paintEvent(QPaintEvent* paintEvent) {

	if (selectionPointX != NULL && selectionPointY != NULL)
	{
		QPainter painter(this);

		painter.setRenderHint(QPainter::Antialiasing);

		painter.setPen(QPen(Qt::black, 3));
		painter.setBrush(QBrush(Qt::white));

		painter.drawEllipse(QPoint(selectionPointX, selectionPointY), 10, 10);
	}
}


bool MenuOptionsWidget::isHorizontalLayoutPresent() 
{
	bool logic;
	if (menuOptionsHorizontalLayout == nullptr)
		logic = false;
	else
		logic = true;

	return logic;
}

MenuWidget::MenuWidget(QWidget* parent)
	: QLabel(parent),
	currentListPtr(&OptionsData::mainMenuOptions),
	layoutIterator(OptionsData::menuLayoutsOptions.begin()),
	optionIterator(OptionsData::mainMenuOptions.begin()) {
	setStyleSheet("background-color: #1f1f1f;");
	setFixedSize(458, 770);
	menuWidgetLayout = new QVBoxLayout(this);
	movingSelectionPoint = false;
	changingKey = false;
	buildUi(0);
}


MenuWidget::~MenuWidget() {
};


void MenuWidget::nextOption() {
	if (*optionIterator == currentListPtr->back())
	{
		while (*optionIterator != currentListPtr->front())
			optionIterator--;
	}
	else
		optionIterator++;
	updateSelectionPoint();
}

void MenuWidget::prevOption() {
	if (*optionIterator == currentListPtr->front())
	{
		while (*optionIterator != currentListPtr->back())
			optionIterator++;
	}
	else
		optionIterator--;
	updateSelectionPoint();
}


void MenuWidget::leftRelativeOption() {
	if (currentListPtr == &OptionsData::soundKeyMenuOptions)
	{
		for (int i = 0; i < currentListPtr->size() / 2; i++)
		{
			if (*optionIterator == currentListPtr->front())
			{
				while (*optionIterator != currentListPtr->back())
					optionIterator++;
			}
			else
				optionIterator--;
		}
		updateSelectionPoint();
	}
	
}


void MenuWidget::rightRelativeOption() {
	if (currentListPtr == &OptionsData::soundKeyMenuOptions)
	{
		for (int i = 0; i < currentListPtr->size() / 2; i++)
		{
			if (*optionIterator == currentListPtr->back())
			{
				while (*optionIterator != currentListPtr->front())
					optionIterator--;
			}
			else
				optionIterator++;
		}
		updateSelectionPoint();
	}
	
}


void MenuWidget::updateSelectionPoint() {

	movingSelectionPoint = true;

	if (KeyboardData::changeSoundKeyValue)
	{
		KeyboardData::changeSoundKeyValue = false;
		rebuildUi();
	}

	menuOptionsWidget->moveSelectionPoint(*optionIterator);

	movingSelectionPoint = false;

}


void MenuWidget::buildUi(int layoutOption) {
	menuInfoWidget = new MenuInfoWidget(this, layoutOption);
	menuWidgetLayout->addWidget(menuInfoWidget, 0, Qt::AlignHCenter);
	menuOptionsWidget = new MenuOptionsWidget(this, layoutOption);
	menuWidgetLayout->addWidget(menuOptionsWidget, 0, Qt::AlignHCenter);
}


void MenuWidget::rebuildUi() {
	menuWidgetLayout->removeWidget(menuInfoWidget);
	delete menuInfoWidget;
	menuWidgetLayout->removeWidget(menuOptionsWidget);
	delete menuOptionsWidget;

	if (!KeyboardData::changeSoundKeyValue and !movingSelectionPoint and !changingKey)
	{
		if (*layoutIterator == 0)
		{
			while (*layoutIterator < *optionIterator + 1)
				layoutIterator++;
		}
		else
		{
			while (*layoutIterator > 0)
				layoutIterator--;
		}


		newListIterator(*layoutIterator);
	}

	buildUi(*layoutIterator);
}


void MenuWidget::newListIterator(int layoutOption) {
	switch (layoutOption) {
	case 0:
		optionIterator = OptionsData::mainMenuOptions.begin();
		currentListPtr = &OptionsData::mainMenuOptions;
		break;
	case 1:
		optionIterator = OptionsData::recordAudioOptions.begin();
		currentListPtr = &OptionsData::recordAudioOptions;
		break;
	case 2:
		optionIterator = OptionsData::audioMenuOptions.begin();
		currentListPtr = &OptionsData::audioMenuOptions;
		break;
	case 3:
		optionIterator = OptionsData::soundKeyMenuOptions.begin();
		currentListPtr = &OptionsData::soundKeyMenuOptions;
		break;
	}
}


void MenuWidget::selectOption() {
	switch (getCurrentLayout())
	{
	case 0:
		if (getCurrentOption() == 0)
		{
			NoteData::toggleRecordingAudio();
		}
		rebuildUi();
		break;
	case 1:
		if (getCurrentOption() == 0)
		{
			NoteData::toggleRecordingAudio();
			if (!NoteData::isRecordingAudio() and !NoteData::recordedAudioBuffer->empty())
				NoteData::saveRecordedAudio();
			rebuildUi();
		}
		break;
	case 2:
		if (getCurrentOption() == 0)
			rebuildUi();
		break;
	case 3:
		if (getCurrentOption() == 0)
			rebuildUi();
		else
		{
			KeyboardData::changeSoundKeyValue = true;
			rebuildUi();
		}
		break;
	}
}


void MenuWidget::changeSoundKeyPair(int selectedKeyID) {
	changingKey = true;
	KeyboardData::changeKeyOfSelectedSound(getCurrentOption(), selectedKeyID);
	rebuildUi();
	while (*optionIterator != 0)
		optionIterator--;
	changingKey = false;
}