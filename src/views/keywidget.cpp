#include "keywidget.h"



KeyWidget::KeyWidget(QWidget* parent, std::string& keySymbol, int id) : QLabel(parent), keySymbol(keySymbol), keyID(id) {
	QString pixmapPath = QString::fromStdString(KEY_PIXMAP_DIR_PATH + keySymbol + KEY_PIXMAP_EXTENSION);
	keyPixmap = new QPixmap(pixmapPath);

	QImage img = keyPixmap->toImage();
	img.invertPixels(QImage::InvertRgb);
	pressedKeyPixmap = new QPixmap(QPixmap::fromImage(img));
	setPixmap(*keyPixmap);
}


KeyWidget::KeyWidget(const KeyWidget& otherKeyWidget) : QLabel(otherKeyWidget.parentWidget()), keySymbol(otherKeyWidget.keySymbol) {
	QString pixmapPath = QString::fromStdString(getPixmapPath());
	keyPixmap = new QPixmap(pixmapPath);
	setPixmap(*keyPixmap);
}


KeyWidget::~KeyWidget() {
	delete keyPixmap;
	delete pressedKeyPixmap;
}


void KeyWidget::updatePixmap() {
	QString pixmapPath;
	if (pressed)
		setPixmap(*pressedKeyPixmap);
	else
		setPixmap(*keyPixmap);
}