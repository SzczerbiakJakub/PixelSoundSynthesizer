#include "optionsviewmodel.h"



OptionsViewModel::OptionsViewModel(QObject* parent) : QObject(parent) {
	optionsPtrVector = new std::vector<MenuLabelWidget*>;
}


OptionsViewModel::~OptionsViewModel() {

	while (optionsPtrVector->size() > 0)
		delete optionsPtrVector->back();

	delete optionsPtrVector;
}


void OptionsViewModel::pushbackMenuLabel(MenuLabelWidget* menuLabel, QVBoxLayout* layout, int optionHeight) {
	if (layout != nullptr)
	{
		optionsPtrVector->push_back(menuLabel);
		if (optionHeight != NULL)
			menuLabel->setFixedHeight(optionHeight);
		layout->addWidget(menuLabel, 0, Qt::AlignHCenter);
	}
}

//void OptionsViewModel::pushbackHorizontalMenuLabel(MenuLabelWidget* menuLabel, QHBoxLayout* layout) {
//	optionsPtrVector->push_back(menuLabel);
//	layout->addWidget(menuLabel, 0, Qt::AlignHCenter);
//}
//void OptionsViewModel::pushbackMenuLabel(MenuLabelWidget* menuLabel, QHBoxLayout* layout) {
//	optionsPtrVector->push_back(menuLabel);
//	layout->addWidget(menuLabel, 0, Qt::AlignHCenter);
//}

void OptionsViewModel::moveSelectionPoint(
	int option, QHBoxLayout* hLayout, KeyOptionLabel* firstHalf, KeyOptionLabel* secondHalf
) {

	if (!optionsPtrVector->empty())
	{
		if (hLayout != nullptr)
		{
			if (option < 15)
			{
				setSelectionPoint(firstHalf, (*optionsPtrVector)[option]);
				resetSelectionPoint(secondHalf);
			}
			else
			{
				resetSelectionPoint(firstHalf);
				setSelectionPoint(secondHalf, (*optionsPtrVector)[option]);
			}
			setSelectionPoint(nullptr);
		}
		else
			setSelectionPoint((*optionsPtrVector)[option]);
	}
	else
	{
		setSelectionPoint(-100, -100);
	}
};


void OptionsViewModel::setSelectionPoint(MenuLabelWidget* option) {
	if (option != nullptr)
	{
		int selectionPointX = option->x() - 20;
		int selectionPointY = option->y() + option->height() / 2;
		
		emit repaintOptionsSignal(selectionPointX, selectionPointY);
	}
};

void OptionsViewModel::setSelectionPoint(KeyOptionLabel* optionLabel, MenuLabelWidget* option) {
	if (option != nullptr)
	{
		int selectionPointX = option->x() - 20;
		int selectionPointY = option->y() + option->height() / 2;

		optionLabel->repaintKeyOptions(selectionPointX, selectionPointY);
	}
};


void OptionsViewModel::setSelectionPoint(int x, int y) {
	int selectionPointX = x;
	int selectionPointY = y;
	emit repaintOptionsSignal(selectionPointX, selectionPointY);
};


void OptionsViewModel::setInitialSelectionPoint() {
	setSelectionPoint(optionsPtrVector->front());
}


void OptionsViewModel::resetSelectionPoint(KeyOptionLabel* optionLabel) {
	optionLabel->resetSelectionPoint();
	optionLabel->repaint();
}


void OptionsViewModel::buildRecordsLabels(QVBoxLayout* layout) {

	for (int i = 0; i < NoteData::recordedTracks->size(); i++)
	{
		emit addNewLabelSignal(std::to_string(i + 1), 20, layout);
	}
	for (int i = 0; i < 10 - NoteData::recordedTracks->size(); i++)
	{
		emit addNewLabelSignal("-", 20, layout);
	}
}

void OptionsViewModel::buildSoundKeyLabels(QVBoxLayout* firstLayout, QVBoxLayout* secondLayout) {

	std::vector<std::string>* labels = NoteData::getSoundToKeyStrings();
	auto middle = labels->begin() + labels->size() / 2;
	std::vector<std::string> firstHalf(labels->begin(), middle), secondHalf(middle, labels->end());


	for (std::string text : firstHalf)
	{
		emit addNewLabelSignal(text, 20, firstLayout);
	}
	for (std::string text : secondHalf)
	{
		emit addNewLabelSignal(text, 20, secondLayout);
	}

	delete labels;
}