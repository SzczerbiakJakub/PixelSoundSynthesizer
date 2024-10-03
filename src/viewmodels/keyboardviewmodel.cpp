#include "keyboardviewmodel.h"


KeyboardViewModel::KeyboardViewModel(QObject* parent, KeyboardWidget* keyboardWidgetPtr) :
	QObject(parent), view(keyboardWidgetPtr) {

	updateTimer = new QTimer(this);
	connect(updateTimer, &QTimer::timeout, this, &KeyboardViewModel::updateKeysPixmaps);
	updateTimer->start(30);
}


//void KeyboardViewModel::appendNewKeyWidget(KeyWidget* keyWidgetPtr) {
//	KeyboardData::keyWidgetsVector->push_back(keyWidgetPtr);
//}

void KeyboardViewModel::buildKeyboard() {

}


void KeyboardViewModel::updateKeysPixmaps() {
	for (KeyWidget* keyWidget : *keyWidgetsVector) {
		keyWidget->updatePixmap();
	}
}

