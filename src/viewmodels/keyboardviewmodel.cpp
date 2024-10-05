#include "keyboardviewmodel.h"


KeyboardViewModel::KeyboardViewModel(QObject* parent) : QObject(parent) {

	keyWidgetsVector = new std::vector<KeyWidget*>;
}



void KeyboardViewModel::addNewKeyToVector(KeyWidget* keyWidgetPtr) {
	QObject::connect(this, &KeyboardViewModel::pressKeySignal, keyWidgetPtr->getViewModel(), &KeyViewModel::pressKey);
	QObject::connect(this, &KeyboardViewModel::releaseKeySignal, keyWidgetPtr->getViewModel(), &KeyViewModel::releaseKey);
	keyWidgetsVector->push_back(keyWidgetPtr);
}


KeyWidget* KeyboardViewModel::getKeyWidget(std::string keySymbol) {

	int index = 0;
	std::string keySymbolGot = getKeyWidgetsVector()[index]->getViewModel()->getKeySymbol();

	while (keySymbolGot != keySymbol)
	{
		index++;
		keySymbolGot = getKeyWidgetsVector()[index]->getViewModel()->getKeySymbol();
	}

	return getKeyWidgetsVector()[index];

}

KeyWidget* KeyboardViewModel::getKeyWidget(int keyID) {

	int index = 0;
	int idGot = getKeyWidgetsVector()[index]->getViewModel()->getKeyID();

	while (idGot != keyID)
	{
		index++;
		idGot = getKeyWidgetsVector()[index]->getViewModel()->getKeyID();
	}

	return getKeyWidgetsVector()[index];

}