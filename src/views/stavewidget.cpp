#include "stavewidget.h"


StaveWidget::StaveWidget(QWidget* parent) : QLabel(parent) {
	setFixedSize(1110, 300);
	setStyleSheet("StaveWidget { border: 2px solid black; background-color: #000000; }");

	notes = new std::queue<NoteWidget*>;

	TrebleClefWidget* trebleClef = new TrebleClefWidget(this, 5, 3);
	BassClefWidget* bassClef = new BassClefWidget(this, 10, 171);

}



StaveWidget::~StaveWidget() {
	while (!notes->empty())
	{
		NoteWidget* widget = notes->front();
		notes->pop();
		delete widget;
	}
	delete notes;
};


void StaveWidget::clearStave() {
	while (!notes->empty())
	{
		NoteWidget* noteWidget = notes->front();
		notes->pop();
		delete noteWidget;
	}
}


void StaveWidget::addNote(AudioSource* audioSource, int beat) {
	pushNotes(notes);

	int notePosY = NoteData::soundToPositionDictionary.find(audioSource)->second;
	NoteWidget* note = new NoteWidget(this, notePosY, beat);

	note->setVisible(true);
	notes->push(note);

}

void StaveWidget::newNote(AudioSource* audioSource, int beats) {

	while (beats >= 8)
	{
		addNote(audioSource, 8);
		beats -= 8;
	}
	
	if (beats > 4)
	{
		addNote(audioSource, 4);
		beats -= 4;
	}
	if (beats > 2)
	{
		addNote(audioSource, 2);
		beats -= 2;
	}

	addNote(audioSource, beats);
}


void StaveWidget::pushNotes(std::queue<NoteWidget*>* notesQueue) {
	std::queue<NoteWidget*> tempQueue;

	while(!notesQueue->empty())
	{
		NoteWidget* noteWidget = notesQueue->front();
		tempQueue.push(noteWidget);
		notesQueue->pop();
	}

	while (!tempQueue.empty())
	{
		NoteWidget* noteWidget = tempQueue.front();
		tempQueue.pop();
		noteWidget->setX(noteWidget->getX() - 60);
		noteWidget->move(noteWidget->getX(), noteWidget->getY());
		if (noteWidget->getX() > 70)
			notesQueue->push(noteWidget);
		else
			delete noteWidget;
	}
}


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