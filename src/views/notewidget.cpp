#include "notewidget.h"


NoteWidget::NoteWidget(QWidget* parent, int y, int beat) : QLabel(parent), x(1030), y(y), beat(beat) {
	setAttribute(Qt::WA_TranslucentBackground);

	QImage* noteImage = getRgbaNoteImage();
	QPixmap* pixmap = new QPixmap(QPixmap::fromImage(*noteImage));
		
	y -= 30;
	this->y = y;

	setScaledContents(true);

	if ((y <= 175 && y >= 125) || (y <= 55))
	{
		pixmap = invertPixmap(pixmap);
		this->y += 28;
	}
	
	setPixmap(*pixmap);
	delete noteImage;
	delete pixmap;
	move(this->x, this->y);
}

NoteWidget::~NoteWidget() {}

QPixmap* NoteWidget::invertPixmap(QPixmap* pixmap) {
	QTransform transform;
	transform.rotate(180);
	*pixmap = pixmap->transformed(transform);
	return pixmap;
}

QImage* NoteWidget::getRgbaNoteImage() {
	QImage* noteImage;

	switch (beat)
	{
	case 8:
		noteImage = new QImage(WHOLE_NOTE_IMG_PATH);
		break;
	case 4:
		noteImage = new QImage(HALF_NOTE_IMG_PATH);
		break;
	case 2:
		noteImage = new QImage(QUARTER_NOTE_IMG_PATH);
		break;
	default:
		noteImage = new QImage(OCTO_NOTE_IMG_PATH);
		break;
	}

	noteImage->convertToFormat(QImage::Format_RGBA8888);
	setImageColor(noteImage);
	return noteImage;
}


void NoteWidget::setImageColor(QImage* image) {

	int r = getValueR(), g = getValueG(), b = getValueB();
	for (int y = 0; y < image->height(); y++) {
		for (int x = 0; x < image->width(); x++) {
			if (image->pixelColor(x, y).alpha() != 0) {
				image->setPixelColor(x, y, QColor(r, g, b));
			}
		}
	}
}

int NoteWidget::getValueR() {
	int r;
	switch (y >= 192 or y <= 98)
	{
		case true:
			r = (y >= 192) ? (int)(255 * (y - 192) / 93) : (int)(255 * (y - 98) / -93);
			break;
		default:
			r = 0;
			break;
	}
	return r;
}

int NoteWidget::getValueG() {
	int g;
	switch (y >= 98)
	{
	case true:
		g = (y >= 192) ? (int)(255 * (y - 285) / -93) : (int)(255 * (y - 98) / 93);
		break;
	default:
		g = 0;
		break;
	}
	return g;
}

int NoteWidget::getValueB() {
	int b;
	switch (y <= 192)
	{
	case true:
		b = (y >= 98) ? (int)(255 * (y - 192) / -93) : (int)(255 * (y - 5) / 93);
		break;
	default:
		b = 0;
		break;
	}
	return b;
}


ClefWidget::ClefWidget(QWidget* parent, int x, int y) : QLabel(parent) {
	setAttribute(Qt::WA_TranslucentBackground);
	move(x, y);
}


TrebleClefWidget::TrebleClefWidget(QWidget* parent, int x, int y) : ClefWidget(parent, x, y) {
	setPixmap(QPixmap(QString::fromStdString(TREBLE_CLEF_IMG_PATH)));
}

BassClefWidget::BassClefWidget(QWidget* parent, int x, int y) : ClefWidget(parent, x, y) {
	setPixmap(QPixmap(QString::fromStdString(BASS_CLEF_IMG_PATH)));
}