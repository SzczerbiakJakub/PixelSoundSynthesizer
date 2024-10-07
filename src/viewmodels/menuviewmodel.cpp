#include "menuviewmodel.h"



MenuViewModel::MenuViewModel(QObject* parent) : QObject(parent) {
	currentListPtr = &OptionsData::mainMenuOptions;
	layoutIterator = OptionsData::menuLayoutsOptions.begin();
	optionIterator = OptionsData::mainMenuOptions.begin();
	movingSelectionPoint = false;
	changingKey = false;
}


MenuViewModel::~MenuViewModel() {

}


void MenuViewModel::nextOption() {
	if (*optionIterator == currentListPtr->back())
	{
		while (*optionIterator != currentListPtr->front())
			optionIterator--;
	}
	else
		optionIterator++;
	updateSelectionPoint();
}


void MenuViewModel::prevOption() {
	if (*optionIterator == currentListPtr->front())
	{
		while (*optionIterator != currentListPtr->back())
			optionIterator++;
	}
	else
		optionIterator--;
	updateSelectionPoint();
}


void MenuViewModel::leftRelativeOption() {
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


void MenuViewModel::rightRelativeOption() {
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


void MenuViewModel::updateSelectionPoint() {

	movingSelectionPoint = true;

	if (KeyboardData::changeSoundKeyValue)
	{
		KeyboardData::changeSoundKeyValue = false;
		rebuildUi();
	}

	emit moveSelectionPointSignal(*optionIterator);
	//menuOptionsWidget->moveSelectionPoint(*optionIterator);

	movingSelectionPoint = false;

}


void MenuViewModel::rebuildUi() {

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

	emit rebuildUISignal(*layoutIterator);

	/*if (*layoutIterator == 2 and *optionIterator != 0)
		emit startPlayingSignal();
	else
		emit stopPlayingSignal();*/
}


void MenuViewModel::newListIterator(int layoutOption) {
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


void MenuViewModel::selectOption() {
	switch (getCurrentLayout())
	{
	case 0:
		if (getCurrentOption() == 0)
		{
			NoteData::toggleRecordingAudio();
			emit startRecordingSignal();
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
			emit stopRecordingSignal();
		}
		break;
	case 2:
		if (getCurrentOption() == 0)
		{
			emit stopRecordingSignal();
			rebuildUi();
		}
		else
		{
			if (getCurrentOption() <= NoteData::recordedTracks->size())
			{
				emit displaySelectedAudioSignal(getCurrentOption());
			}
			
		}
		break;
	case 3:
		if (getCurrentOption() != 0)
		{
			KeyboardData::changeSoundKeyValue = true;
			emit changingSoundKeyValueSignal();
		}
		rebuildUi();
		break;
	}
}


void MenuViewModel::changeSoundKeyPair(int selectedKeyID) {
	changingKey = true;
	KeyboardData::changeKeyOfSelectedSound(getCurrentOption(), selectedKeyID);
	rebuildUi();
	while (*optionIterator != 0)
		optionIterator--;
	changingKey = false;
}