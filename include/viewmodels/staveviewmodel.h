#pragma once

#include <QObject>
#include <queue>
#include <QTimer>
#include "notewidget.h"
#include "threads.h"



class StaveViewModel : public QObject
{
	Q_OBJECT

public:
	StaveViewModel(QObject* parent=nullptr);
	~StaveViewModel();

	QTimer* getRenderTimer() { return renderTimer; };
	bool isRecording() { return recording; };
	bool isPlaying() { return playing; };
	bool isPainted() { return painted; };

private:
	/// <summary>
	/// Wskaźnik do kolejki wskaźników nutek
	/// </summary>
	std::queue<NoteWidget*>* notes;

	QTimer* renderTimer;
	StaveWidgetRenderThread* renderThread;

	bool recording;
	bool playing;
	bool painted;

	void pushNotes();
	void addNote(int notePosY, int beat);

signals:
	void addNewNoteSignal(int notePosY, int beat);
	void updateRecordStateSignal(QPainter* painter, bool* recording, bool* playing, bool* painted);
	void renderStaveSignal();

public slots:
	void createNewNote(AudioSource* audioSource, int beats);
	void pushNewNoteToQueue(NoteWidget* note);
	void clearStave();
	void checkRecordState(QPainter* painter);

	void setRecording();
	void unsetRecording();
	void setPlaying();
	void unsetPlaying();
	
};

