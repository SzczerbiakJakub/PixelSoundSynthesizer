#include "keyviewmodel.h"



KeyViewModel::KeyViewModel(std::string keySymbol, int keyID, QObject* parent) :
	keySymbol(keySymbol), keyID(keyID), QObject(parent) {

	pressed = false;

	QString pixmapPath = QString::fromStdString(KEY_PIXMAP_DIR_PATH + keySymbol + KEY_PIXMAP_EXTENSION);
	keyPixmap = new QPixmap(pixmapPath);

	QImage img = keyPixmap->toImage();
	img.invertPixels(QImage::InvertRgb);
	pressedKeyPixmap = new QPixmap(QPixmap::fromImage(img));

};


KeyViewModel::~KeyViewModel() {

	if (keyPixmap != nullptr)
		delete keyPixmap;

	if (pressedKeyPixmap != nullptr)
		delete pressedKeyPixmap;

};


void KeyViewModel::pressKey(int qKey) {
	if (qKey == keyID)
	{
		pressed = true;
		qDebug() << "PRESSING KEY: " << keySymbol;
		emit sendPixmap(pressedKeyPixmap);
	}
};


void KeyViewModel::releaseKey(int qKey) {
	if (qKey == keyID)
	{
		pressed = false;
		qDebug() << "RELEASING KEY: " << keySymbol;
		emit sendPixmap(keyPixmap);
	}
};