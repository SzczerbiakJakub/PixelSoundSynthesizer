#include "notewidget.h"


NoteWidget::NoteWidget(QWidget* parent, int y, int beat) : QLabel(parent), x(1030), y(y) {

	viewModel = new NoteViewModel();

	QObject::connect(this, &NoteWidget::getCustomNotePixmap, viewModel, &NoteViewModel::createCustomNotePixmap);
	QObject::connect(viewModel, &NoteViewModel::sendCustomNotePixmap, this, &NoteWidget::setCustomNotePixmap);

	emit getCustomNotePixmap(y, beat);

	setAttribute(Qt::WA_TranslucentBackground);
	setScaledContents(true);

	move(this->x, this->y);
}


NoteWidget::~NoteWidget() {

}


void NoteWidget::setCustomNotePixmap(QPixmap* pixmap, bool noteInverted) {

	setPixmap(*pixmap);
	delete pixmap;

	if (noteInverted)
		this->y += 28;

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