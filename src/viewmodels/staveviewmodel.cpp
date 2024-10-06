#include "staveviewmodel.h"


StaveViewModel::StaveViewModel(QObject* parent) : QObject(parent) {

	notes = new std::queue<NoteWidget*>;

	renderTimer = new QTimer();
	renderThread = new StaveWidgetRenderThread(&recording, &playing);

	recording = false;
	playing = false;
	painted = false;

}

StaveViewModel::~StaveViewModel() {

	while (!notes->empty())
	{
		NoteWidget* widget = notes->front();
		notes->pop();
		delete widget;
	}
	delete notes;
	delete renderTimer;
}



void StaveViewModel::clearStave() {
	while (!notes->empty())
	{
		NoteWidget* noteWidget = notes->front();
		notes->pop();
		delete noteWidget;
	}
}


void StaveViewModel::pushNotes() {
	std::queue<NoteWidget*> tempQueue;

	while (!notes->empty())
	{
		NoteWidget* noteWidget = notes->front();
		tempQueue.push(noteWidget);
		notes->pop();
	}

	while (!tempQueue.empty())
	{
		NoteWidget* noteWidget = tempQueue.front();
		tempQueue.pop();
		noteWidget->setX(noteWidget->getX() - 60);
		noteWidget->move(noteWidget->getX(), noteWidget->getY());
		if (noteWidget->getX() > 120)
			notes->push(noteWidget);
		else
			delete noteWidget;
	}
}


void StaveViewModel::createNewNote(AudioSource* audioSource, int beats) {

	int notePosY = NoteData::soundToPositionDictionary.find(audioSource)->second;


	while (beats > 8)
	{
		pushNotes();
		emit addNewNoteSignal(notePosY, 8);
		beats -= 8;
	}

	if (beats == 8)
	{
		pushNotes();
		emit addNewNoteSignal(notePosY, 8);
		beats -= 9;
	}
	else if (beats > 4)
	{
		pushNotes();
		emit addNewNoteSignal(notePosY, 4);
		beats -= 4;
	}
	if (beats > 2)
	{
		pushNotes();
		emit addNewNoteSignal(notePosY, 2);
		beats -= 2;
	}
	if (beats >= 0)
	{
		pushNotes();
		emit addNewNoteSignal(notePosY, beats);
	}
}



void StaveViewModel::pushNewNoteToQueue(NoteWidget* note) {
	notes->push(note);
}


void StaveViewModel::checkRecordState(QPainter* painter) {
	if (painted)
		painted = false;
	else
		painted = true;
	emit updateRecordStateSignal(painter, &recording, &playing, &painted);
}


void StaveViewModel::setRecording() {
	recording = true;
	playing = false;
	emit clearStave();
	renderTimer->start(RECORD_STATE_RENDER_TIME);
	qDebug() << "SETTING RECORDING";
}


void StaveViewModel::unsetRecording() {
	emit clearStave();
	recording = false;
	playing = false;
	qDebug() << "RESETING RECORDING";
}


void StaveViewModel::setPlaying() {
	playing = true;
	recording = false;
	emit clearStave();
	renderTimer->start(RECORD_STATE_RENDER_TIME);
	qDebug() << "SETTING PLAYING";
}


void StaveViewModel::unsetPlaying() {
	emit clearStave();
	playing = false;
	recording = false;
	qDebug() << "RESETING PLAYING";
}