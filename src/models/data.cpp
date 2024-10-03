#include "data.h"


AudioSource* SoundEffects::soundC2 = new AudioSource(65, "C2");
AudioSource* SoundEffects::soundD2 = new AudioSource(73, "D2");
AudioSource* SoundEffects::soundE2 = new AudioSource(82, "E2");
AudioSource* SoundEffects::soundF2 = new AudioSource(87, "F2");
AudioSource* SoundEffects::soundG2 = new AudioSource(98, "G2");
AudioSource* SoundEffects::soundA2 = new AudioSource(110, "A2");
AudioSource* SoundEffects::soundB2 = new AudioSource(123, "B2");
AudioSource* SoundEffects::soundC3 = new AudioSource(131, "C3");
AudioSource* SoundEffects::soundD3 = new AudioSource(147, "D3");
AudioSource* SoundEffects::soundE3 = new AudioSource(165, "E3");
AudioSource* SoundEffects::soundF3 = new AudioSource(175, "F3");
AudioSource* SoundEffects::soundG3 = new AudioSource(196, "G3");
AudioSource* SoundEffects::soundA3 = new AudioSource(220, "A3");
AudioSource* SoundEffects::soundB3 = new AudioSource(247, "B3");
AudioSource* SoundEffects::soundC4 = new AudioSource(262, "C4");
AudioSource* SoundEffects::soundD4 = new AudioSource(294, "D4");
AudioSource* SoundEffects::soundE4 = new AudioSource(330, "E4");
AudioSource* SoundEffects::soundF4 = new AudioSource(349, "F4");
AudioSource* SoundEffects::soundG4 = new AudioSource(392, "G4");
AudioSource* SoundEffects::soundA4 = new AudioSource(440, "A4");
AudioSource* SoundEffects::soundB4 = new AudioSource(494, "B4");
AudioSource* SoundEffects::soundC5 = new AudioSource(523, "C5");
AudioSource* SoundEffects::soundD5 = new AudioSource(587, "D5");
AudioSource* SoundEffects::soundE5 = new AudioSource(659, "E5");
AudioSource* SoundEffects::soundF5 = new AudioSource(698, "F5");
AudioSource* SoundEffects::soundG5 = new AudioSource(784, "G5");
AudioSource* SoundEffects::soundA5 = new AudioSource(880, "A5");
AudioSource* SoundEffects::soundB5 = new AudioSource(988, "B5");
AudioSource* SoundEffects::soundC6 = new AudioSource(1047, "C6");



HRESULT SoundEffects::setSoundsFormats(WAVEFORMATEX* format) {
	HRESULT hr;
	hr = soundC2->SetFormat(format);
	hr = soundD2->SetFormat(format);
	hr = soundE2->SetFormat(format);
	hr = soundF2->SetFormat(format);
	hr = soundG2->SetFormat(format);
	hr = soundA2->SetFormat(format);
	hr = soundB2->SetFormat(format);
	hr = soundC3->SetFormat(format);
	hr = soundD3->SetFormat(format);
	hr = soundE3->SetFormat(format);
	hr = soundF3->SetFormat(format);
	hr = soundG3->SetFormat(format);
	hr = soundA3->SetFormat(format);
	hr = soundB3->SetFormat(format);
	hr = soundC4->SetFormat(format);
	hr = soundD4->SetFormat(format);
	hr = soundE4->SetFormat(format);
	hr = soundF4->SetFormat(format);
	hr = soundG4->SetFormat(format);
	hr = soundA4->SetFormat(format);
	hr = soundB4->SetFormat(format);
	hr = soundC5->SetFormat(format);
	hr = soundD5->SetFormat(format);
	hr = soundE5->SetFormat(format);
	hr = soundF5->SetFormat(format);
	hr = soundG5->SetFormat(format);
	hr = soundA5->SetFormat(format);
	hr = soundB5->SetFormat(format);
	hr = soundC6->SetFormat(format);
	return hr;
}


std::queue<std::pair<AudioSource*, int>>* NoteData::recordedAudioBuffer = new std::queue<std::pair<AudioSource*, int>>;



bool NoteData::recordingAudio = false;

std::vector<std::queue<std::pair<AudioSource*, int>>*>* NoteData::recordedTracks = new std::vector<std::queue<std::pair<AudioSource*, int>>*>;


void NoteData::saveRecordedAudio() {
	std::queue<std::pair<AudioSource*, int>>* copyOfRecord = new std::queue<std::pair<AudioSource*, int>>;
	while (!recordedAudioBuffer->empty()) {
		copyOfRecord->push(recordedAudioBuffer->front());
		recordedAudioBuffer->pop();
	}

	recordedTracks->push_back(copyOfRecord);
	if (recordedTracks->size() > 10)
		recordedTracks->erase(recordedTracks->begin());
}



std::list<int> OptionsData::menuLayoutsOptions = { 0, 1, 2, 3 };

std::list<int> OptionsData::mainMenuOptions = { 0, 1, 2 };

std::list<int> OptionsData::recordAudioOptions = { 0 };

std::list<int> OptionsData::audioMenuOptions = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

std::list<int> OptionsData::soundKeyMenuOptions = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29
};


AudioSource* NoteData::getSound(int qtKey) {
	AudioSource* sound = NoteData::keyToNoteDictionary.find(qtKey)->second;
	return sound;
}

void NoteData::toggleRecordingAudio() { 
	recordingAudio = isRecordingAudio() ? false : true; 
};

std::unordered_map<int, AudioSource*> NoteData::keyToNoteDictionary = {
	{Qt::Key_1, SoundEffects::soundC2},
	{Qt::Key_2, SoundEffects::soundD2},
	{Qt::Key_3, SoundEffects::soundE2},
	{Qt::Key_4, SoundEffects::soundF2},
	{Qt::Key_5, SoundEffects::soundG2},
	{Qt::Key_6, SoundEffects::soundA2},
	{Qt::Key_7, SoundEffects::soundB2},
	{Qt::Key_8, SoundEffects::soundC3},
	{Qt::Key_9, SoundEffects::soundD3},
	{Qt::Key_0, SoundEffects::soundE3},
	{Qt::Key_Q, SoundEffects::soundF3},
	{Qt::Key_W, SoundEffects::soundG3},
	{Qt::Key_E, SoundEffects::soundA3},
	{Qt::Key_R, SoundEffects::soundB3},
	{Qt::Key_T, SoundEffects::soundC4},
	{Qt::Key_Y, SoundEffects::soundD4},
	{Qt::Key_U, SoundEffects::soundE4},
	{Qt::Key_I, SoundEffects::soundF4},
	{Qt::Key_O, SoundEffects::soundG4},
	{Qt::Key_P, SoundEffects::soundA4},
	{Qt::Key_A, SoundEffects::soundB4},
	{Qt::Key_S, SoundEffects::soundC5},
	{Qt::Key_D, SoundEffects::soundD5},
	{Qt::Key_F, SoundEffects::soundE5},
	{Qt::Key_G, SoundEffects::soundF5},
	{Qt::Key_H, SoundEffects::soundG5},
	{Qt::Key_J, SoundEffects::soundA5},
	{Qt::Key_K, SoundEffects::soundB5},
	{Qt::Key_L, SoundEffects::soundC6},
};

std::unordered_map<AudioSource*, int> const NoteData::soundToPositionDictionary = {
	{SoundEffects::soundC2, 285},
	{SoundEffects::soundD2, 275},
	{SoundEffects::soundE2, 265},
	{SoundEffects::soundF2, 255},
	{SoundEffects::soundG2, 245},
	{SoundEffects::soundA2, 235},
	{SoundEffects::soundB2, 225},
	{SoundEffects::soundC3, 215},
	{SoundEffects::soundD3, 205},
	{SoundEffects::soundE3, 195},
	{SoundEffects::soundF3, 185},
	{SoundEffects::soundG3, 175},
	{SoundEffects::soundA3, 165},
	{SoundEffects::soundB3, 155},
	{SoundEffects::soundC4, 145},
	{SoundEffects::soundD4, 135},
	{SoundEffects::soundE4, 125},
	{SoundEffects::soundF4, 115},
	{SoundEffects::soundG4, 105},
	{SoundEffects::soundA4, 95},
	{SoundEffects::soundB4, 85},
	{SoundEffects::soundC5, 75},
	{SoundEffects::soundD5, 65},
	{SoundEffects::soundE5, 55},
	{SoundEffects::soundF5, 45},
	{SoundEffects::soundG5, 35},
	{SoundEffects::soundA5, 25},
	{SoundEffects::soundB5, 15},
	{SoundEffects::soundC6, 5},
};



std::vector<std::string>* NoteData::getSoundToKeyStrings() {

	std::vector<std::string>* soundToKeyString = new std::vector<std::string>();
	std::string keySymbol, soundToKey;

	for (std::map<int, std::pair<AudioSource*, int>>::iterator it = KeyboardData::soundToKeyDictionary.begin();
		it != KeyboardData::soundToKeyDictionary.end(); ++it)
	{
		keySymbol = KeyStringDictionary::keyStringDictionary.find(it->second.second)->second;
		soundToKey = it->second.first->noteSymbol + " - " + keySymbol;
		soundToKeyString->push_back(soundToKey);
		qDebug() << soundToKey;
	}

	return soundToKeyString;
}


std::vector<int> KeyboardData::functionalKeysUsed = {
	Qt::Key_Escape, Qt::Key_Return, Qt::Key_Space, Qt::Key_Up, Qt::Key_Down, Qt::Key_Left, Qt::Key_Right, Qt::Key_Backspace
};


bool KeyboardData::isFunctionalKeyPressed(int keyID) {

	bool logic = false;
	for (int functionalKeyID : KeyboardData::functionalKeysUsed)
	{
		if (functionalKeyID == keyID)
			logic = true;
	}
	return logic;
}


std::map<int, std::pair<AudioSource*, int>> KeyboardData::soundToKeyDictionary = {
	{1, std::pair<AudioSource*, int>(SoundEffects::soundC2, Qt::Key_1)},
	{2, std::pair<AudioSource*, int>(SoundEffects::soundD2, Qt::Key_2)},
	{3, std::pair<AudioSource*, int>(SoundEffects::soundE2, Qt::Key_3)},
	{4, std::pair<AudioSource*, int>(SoundEffects::soundF2, Qt::Key_4)},
	{5, std::pair<AudioSource*, int>(SoundEffects::soundG2, Qt::Key_5)},
	{6, std::pair<AudioSource*, int>(SoundEffects::soundA2, Qt::Key_6)},
	{7, std::pair<AudioSource*, int>(SoundEffects::soundB2, Qt::Key_7)},
	{8, std::pair<AudioSource*, int>(SoundEffects::soundC3, Qt::Key_8)},
	{9, std::pair<AudioSource*, int>(SoundEffects::soundD3, Qt::Key_9)},
	{10, std::pair<AudioSource*, int>(SoundEffects::soundE3, Qt::Key_0)},
	{11, std::pair<AudioSource*, int>(SoundEffects::soundF3, Qt::Key_Q)},
	{12, std::pair<AudioSource*, int>(SoundEffects::soundG3, Qt::Key_W)},
	{13, std::pair<AudioSource*, int>(SoundEffects::soundA3, Qt::Key_E)},
	{14, std::pair<AudioSource*, int>(SoundEffects::soundB3, Qt::Key_R)},
	{15, std::pair<AudioSource*, int>(SoundEffects::soundC4, Qt::Key_T)},
	{16, std::pair<AudioSource*, int>(SoundEffects::soundD4, Qt::Key_Y)},
	{17, std::pair<AudioSource*, int>(SoundEffects::soundE4, Qt::Key_U)},
	{18, std::pair<AudioSource*, int>(SoundEffects::soundF4, Qt::Key_I)},
	{19, std::pair<AudioSource*, int>(SoundEffects::soundG4, Qt::Key_O)},
	{20, std::pair<AudioSource*, int>(SoundEffects::soundA4, Qt::Key_P)},
	{21, std::pair<AudioSource*, int>(SoundEffects::soundB4, Qt::Key_A)},
	{22, std::pair<AudioSource*, int>(SoundEffects::soundC5, Qt::Key_S)},
	{23, std::pair<AudioSource*, int>(SoundEffects::soundD5, Qt::Key_D)},
	{24, std::pair<AudioSource*, int>(SoundEffects::soundE5, Qt::Key_F)},
	{25, std::pair<AudioSource*, int>(SoundEffects::soundF5, Qt::Key_G)},
	{26, std::pair<AudioSource*, int>(SoundEffects::soundG5, Qt::Key_H)},
	{27, std::pair<AudioSource*, int>(SoundEffects::soundA5, Qt::Key_J)},
	{28, std::pair<AudioSource*, int>(SoundEffects::soundB5, Qt::Key_K)},
	{29, std::pair<AudioSource*, int>(SoundEffects::soundC6, Qt::Key_L)}
};

std::pair<AudioSource*, int> KeyboardData::getPairByKeyID(int keyID) {
	std::map<int, std::pair<AudioSource*, int>>::iterator it = KeyboardData::soundToKeyDictionary.begin();
	while (it != KeyboardData::soundToKeyDictionary.end() and it->second.second != keyID)
		it++;
	return it->second;
}

AudioSource* KeyboardData::getAudio(int keyID) {

	return getPairByKeyID(keyID).first;
}

bool KeyboardData::changeSoundKeyValue = false;

void KeyboardData::changeKeyOfSelectedSound(int selectedSoundOption, int keyID) {

	KeyboardData::soundToKeyDictionary[selectedSoundOption].second = keyID;
	changeSoundKeyValue = false;
}

bool KeyboardData::isKeyUsed(int keyID) {
	bool isUsed = false;

	for (auto& pair : KeyboardData::soundToKeyDictionary) {

		if (keyID == pair.second.second)
			isUsed = true;
	}

	for (int gotKeyID : functionalKeysUsed)
	{
		if (keyID == gotKeyID)
			isUsed = true;
	}
	return isUsed;
}


std::unordered_map<int, std::string> const KeyStringDictionary::keyStringDictionary = {

	{Qt::Key_F1, "f1"},
	{Qt::Key_F2, "f2"},
	{Qt::Key_F3, "f3"},
	{Qt::Key_F4, "f4"},
	{Qt::Key_F5, "f5"},
	{Qt::Key_F6, "f6"},
	{Qt::Key_F7, "f7"},
	{Qt::Key_F8, "f8"},
	{Qt::Key_F9, "f9"},
	{Qt::Key_F10, "f10"},
	{Qt::Key_F11, "f11"},
	{Qt::Key_F12, "f12"},
	{Qt::Key_A, "a"},
	{Qt::Key_B, "b"},
	{Qt::Key_C, "c"},
	{Qt::Key_D, "d"},
	{Qt::Key_E, "e"},
	{Qt::Key_F, "f"},
	{Qt::Key_G, "g"},
	{Qt::Key_H, "h"},
	{Qt::Key_I, "i"},
	{Qt::Key_J, "j"},
	{Qt::Key_K, "k"},
	{Qt::Key_L, "l"},
	{Qt::Key_M, "m"},
	{Qt::Key_N, "n"},
	{Qt::Key_O, "o"},
	{Qt::Key_P, "p"},
	{Qt::Key_Q, "q"},
	{Qt::Key_R, "r"},
	{Qt::Key_S, "s"},
	{Qt::Key_T, "t"},
	{Qt::Key_U, "u"},
	{Qt::Key_V, "v"},
	{Qt::Key_W, "w"},
	{Qt::Key_X, "x"},
	{Qt::Key_Y, "y"},
	{Qt::Key_Z, "z"},
	{Qt::Key_0, "0"},
	{Qt::Key_1, "1"},
	{Qt::Key_2, "2"},
	{Qt::Key_3, "3"},
	{Qt::Key_4, "4"},
	{Qt::Key_5, "5"},
	{Qt::Key_6, "6"},
	{Qt::Key_7, "7"},
	{Qt::Key_8, "8"},
	{Qt::Key_9, "9"},
	{Qt::Key_Tab, "tab"},
	{Qt::Key_CapsLock, "caps"},
	{Qt::Key_Return, "enter"},
	{Qt::Key_Space, "spacebar"},
	{Qt::Key_Shift, "leftshift"},
	{Qt::Key_Control, "leftcontrol"},
	{Qt::Key_Alt, "leftalt"},
	{Qt::Key_BracketLeft, "["},
	{Qt::Key_BracketRight, "]"},
	{Qt::Key_Backslash, "backslash"},
	{Qt::Key_Colon, ":"},
	{Qt::Key_Semicolon, ";"},
	{Qt::Key_Equal, "plus"},
	{Qt::Key_Minus, "minus"},
	{Qt::Key_Comma, "comma"},
	{Qt::Key_Period, "dot"},
	{Qt::Key_Slash, "slash"},
	{Qt::Key_QuoteLeft, "tilde"},
	{Qt::Key_Apostrophe, "apostrophe" }
};