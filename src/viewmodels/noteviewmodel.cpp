#include "noteviewmodel.h"


NoteViewModel::NoteViewModel(QObject* parent) : QObject(parent) {
	inverted = false;
}


NoteViewModel::~NoteViewModel() {

}



void NoteViewModel::createCustomNotePixmap(int y, int beat) {

	QImage* noteImage = getRgbaNoteImage(y+30, beat);
	QPixmap* pixmap = new QPixmap(QPixmap::fromImage(*noteImage));

	if ((y <= 175 && y >= 125) || (y <= 55))
	{
		pixmap = invertPixmap(pixmap);
		inverted = true;
	}

	delete noteImage;
	emit sendCustomNotePixmap(pixmap, inverted);
}



QImage* NoteViewModel::getRgbaNoteImage(int y, int beat) {
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
	setImageColor(noteImage, y);
	return noteImage;
}


void NoteViewModel::setImageColor(QImage* image, int y) {

	int r = getValueR(y), g = getValueG(y), b = getValueB(y);
	for (int y = 0; y < image->height(); y++) {
		for (int x = 0; x < image->width(); x++) {
			if (image->pixelColor(x, y).alpha() != 0) {
				image->setPixelColor(x, y, QColor(r, g, b));
			}
		}
	}
}

int NoteViewModel::getValueR(int y) {
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

int NoteViewModel::getValueG(int y) {
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

int NoteViewModel::getValueB(int y) {
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


QPixmap* NoteViewModel::invertPixmap(QPixmap* pixmap) {
	QTransform transform;
	transform.rotate(180);
	*pixmap = pixmap->transformed(transform);
	return pixmap;
}