#include "stavewidget.h"



StaveWidget::StaveWidget(QWidget* parent) : QLabel(parent) {
	setFixedSize(1110, 300);
	setStyleSheet("StaveWidget { border: 2px solid black; background-color: #000000; }");

	viewModel = new StaveViewModel();

	QObject::connect(this, &StaveWidget::createNewNoteSignal, viewModel, &StaveViewModel::createNewNote);
	QObject::connect(viewModel, &StaveViewModel::addNewNoteSignal, this, &StaveWidget::addNewNote);
	QObject::connect(this, &StaveWidget::pushNewNoteSignal, viewModel, &StaveViewModel::pushNewNoteToQueue);
	QObject::connect(this, &StaveWidget::clearStaveSignal, viewModel, &StaveViewModel::clearStave);


	trebleClef = new TrebleClefWidget(this, 5, 3);
	bassClef = new BassClefWidget(this, 10, 171);

	repaint();

}


StaveWidget::~StaveWidget() {
	delete bassClef;
	delete trebleClef;
	delete viewModel;
};


void StaveWidget::paintEvent(QPaintEvent* event) {

	QColor color = QColor(0xFFFFFF);
	color.setAlpha(0x80);
	QPen pen(color);
	pen.setWidth(3);

	QPainter painter(this);
	painter.setPen(pen);
	buildStaveLines(&painter);
}


void StaveWidget::drawHighPitchLines(QPainter* painter) {
	painter->drawLine(0, 45, 1110, 45);
	painter->drawLine(0, 65, 1110, 65);
	painter->drawLine(0, 85, 1110, 85);
	painter->drawLine(0, 105, 1110, 105);
	painter->drawLine(0, 125, 1110, 125);
}


void StaveWidget::drawLowPitchLines(QPainter* painter) {
	painter->drawLine(0, 175, 1110, 175);
	painter->drawLine(0, 195, 1110, 195);
	painter->drawLine(0, 215, 1110, 215);
	painter->drawLine(0, 235, 1110, 235);
	painter->drawLine(0, 255, 1110, 255);
}


void StaveWidget::buildStaveLines(QPainter* painter) {
	drawHighPitchLines(painter);
	drawLowPitchLines(painter);
}


void StaveWidget::addNewNote(int notePosY, int beat) {

	NoteWidget* note = new NoteWidget(this, notePosY, beat);
	note->setVisible(true);
	emit pushNewNoteSignal(note);
}