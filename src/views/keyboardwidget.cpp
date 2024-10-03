#include "keyboardwidget.h"




KeyboardWidget::KeyboardWidget(QWidget* parent) : QLabel(parent) {

	setFixedSize(1078, 469);
	keyWidgetsVector = new std::vector<KeyWidget*>;
	updateTimer = new QTimer(this); 
	connect(updateTimer, &QTimer::timeout, this, &KeyboardWidget::onTimeout);

	keyboardPixmap = new QPixmap(QString::fromStdString(KEYBOARD_IMAGE_PATH));
	*keyboardPixmap = keyboardPixmap->scaled(size());
	setPixmap(*keyboardPixmap);

	buildKeyboard();
	updateTimer->start(30);


}

KeyboardWidget::~KeyboardWidget() {

	delete keyboardPixmap;
	for (KeyWidget* keyWidget : *keyWidgetsVector)
	{
		delete keyWidget;
	}
	delete keyWidgetsVector;
	delete updateTimer;
}


void KeyboardWidget::onTimeout() {
	for (KeyWidget* keyWidget : *keyWidgetsVector) {
		keyWidget->updatePixmap();
	}
}


KeyWidget* KeyboardWidget::getKeyWidget(std::string keySymbol) {

	int index = 0;
	std::string keySymbolGot = getKeyWidgetsVector()[index]->getKeySymbol();

	while (keySymbolGot != keySymbol)
	{
		index++;
		keySymbolGot = getKeyWidgetsVector()[index]->getKeySymbol();
	}
	
	return getKeyWidgetsVector()[index];

}

KeyWidget* KeyboardWidget::getKeyWidget(int keyID) {

	int index = 0;
	int idGot = getKeyWidgetsVector()[index]->getKeyID();

	while (idGot != keyID)
	{
		index++;
		idGot = getKeyWidgetsVector()[index]->getKeyID();
	}

	return getKeyWidgetsVector()[index];

}

void KeyboardWidget::addNewKeyWidget(std::string keySymbol, int id, int x, int y ) {
	KeyWidget* newKey = new KeyWidget(this, keySymbol, id);
	newKey->move(x, y);
	keyWidgetsVector->push_back(newKey);
}


void KeyboardWidget::buildKeyboard() {


	addNewKeyWidget("esc", Qt::Key_Escape, 13, 9);

	addNewKeyWidget("f1", Qt::Key_F1, 154, 9);
	addNewKeyWidget("f2", Qt::Key_F2, 224, 9);
	addNewKeyWidget("f3", Qt::Key_F3, 294, 9);
	addNewKeyWidget("f4", Qt::Key_F4, 364, 9);
	addNewKeyWidget("f5", Qt::Key_F5, 469, 9);
	addNewKeyWidget("f6", Qt::Key_F6, 539, 9);
	addNewKeyWidget("f7", Qt::Key_F7, 609, 9);
	addNewKeyWidget("f8", Qt::Key_F8, 689, 9);
	addNewKeyWidget("f9", Qt::Key_F9, 784, 9);
	addNewKeyWidget("f10", Qt::Key_F10, 854, 9);
	addNewKeyWidget("f11", Qt::Key_F11, 924, 9);
	addNewKeyWidget("f12", Qt::Key_F11, 994, 9);
	
	addNewKeyWidget("tilde", Qt::Key_AsciiTilde, 13, 89);
	addNewKeyWidget("1", Qt::Key_1, 84, 89);
	addNewKeyWidget("2", Qt::Key_2, 154, 89);
	addNewKeyWidget("3", Qt::Key_3, 225, 89);
	addNewKeyWidget("4", Qt::Key_4, 295, 89);
	addNewKeyWidget("5", Qt::Key_5, 366, 89);
	addNewKeyWidget("6", Qt::Key_6, 436, 89);
	addNewKeyWidget("7", Qt::Key_7, 505, 89);
	addNewKeyWidget("8", Qt::Key_8, 576, 89);
	addNewKeyWidget("9", Qt::Key_9, 645, 89);
	addNewKeyWidget("0", Qt::Key_0, 716, 89);
	addNewKeyWidget("minus", Qt::Key_Minus, 787, 89);
	addNewKeyWidget("plus", Qt::Key_Plus, 857, 89);
	addNewKeyWidget("backspace", Qt::Key_Backspace, 927, 89);

	addNewKeyWidget("tab", Qt::Key_Tab, 13, 158);
	addNewKeyWidget("q", Qt::Key_Q, 118, 158);
	addNewKeyWidget("w", Qt::Key_W, 189, 158);
	addNewKeyWidget("e", Qt::Key_E, 259, 158);
	addNewKeyWidget("r", Qt::Key_R, 328, 158);
	addNewKeyWidget("t", Qt::Key_T, 398, 158);
	addNewKeyWidget("y", Qt::Key_Y, 469, 158);
	addNewKeyWidget("u", Qt::Key_U, 540, 158);
	addNewKeyWidget("i", Qt::Key_I, 609, 158);
	addNewKeyWidget("o", Qt::Key_O, 680, 158);
	addNewKeyWidget("p", Qt::Key_P, 749, 158);
	addNewKeyWidget("[", Qt::Key_BracketLeft, 820, 158);
	addNewKeyWidget("]", Qt::Key_BracketRight, 889, 158);
	addNewKeyWidget("backslash", Qt::Key_Backslash, 960, 158);

	addNewKeyWidget("caps", Qt::Key_CapsLock, 13, 228);
	addNewKeyWidget("a", Qt::Key_A, 128, 228);
	addNewKeyWidget("s", Qt::Key_S, 199, 228);
	addNewKeyWidget("d", Qt::Key_D, 270, 228);
	addNewKeyWidget("f", Qt::Key_F, 341, 228);
	addNewKeyWidget("g", Qt::Key_G, 412, 228);
	addNewKeyWidget("h", Qt::Key_H, 483, 228);
	addNewKeyWidget("j", Qt::Key_J, 554, 228);
	addNewKeyWidget("k", Qt::Key_K, 625, 228);
	addNewKeyWidget("l", Qt::Key_L, 696, 228);
	addNewKeyWidget(";", Qt::Key_Semicolon, 767, 228);
	addNewKeyWidget("apostrophe", Qt::Key_Apostrophe, 838, 228);
	addNewKeyWidget("enter", Qt::Key_Return, 907, 228);

	addNewKeyWidget("leftshift", Qt::Key_Shift, 13, 299);
	addNewKeyWidget("z", Qt::Key_Z, 172, 299);
	addNewKeyWidget("x", Qt::Key_X, 242, 299);
	addNewKeyWidget("c", Qt::Key_C, 313, 299);
	addNewKeyWidget("v", Qt::Key_V, 381, 299);
	addNewKeyWidget("b", Qt::Key_B, 452, 299);
	addNewKeyWidget("n", Qt::Key_N, 523, 299);
	addNewKeyWidget("m", Qt::Key_M, 593, 299);
	addNewKeyWidget("comma", Qt::Key_Comma, 663, 299);
	addNewKeyWidget("period", Qt::Key_Period, 734, 299);
	addNewKeyWidget("slash", Qt::Key_Slash, 803, 299);
	addNewKeyWidget("rightshift", Qt::Key_Shift, 874, 299);

	
	addNewKeyWidget("leftcontrol", Qt::Key_Control, 13, 368);
	addNewKeyWidget("leftalt", Qt::Key_Alt, 189, 368);
	addNewKeyWidget("space", Qt::Key_Space, 276, 368);
	addNewKeyWidget("rightalt", Qt::Key_Alt, 731, 368);
	addNewKeyWidget("rightcontrol", Qt::Key_Control, 977, 368);
	
}