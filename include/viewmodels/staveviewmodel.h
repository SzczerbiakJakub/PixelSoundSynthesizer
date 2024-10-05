#pragma once

#include <QObject>
#include <queue>
#include "notewidget.h"



class StaveViewModel : public QObject
{
	Q_OBJECT

public:
	StaveViewModel(QObject* parent=nullptr);
	~StaveViewModel();

private:
	/// <summary>
	/// Wskaźnik do kolejki wskaźników nutek
	/// </summary>
	std::queue<NoteWidget*>* notes;

	void pushNotes();
	void addNote(int notePosY, int beat);

signals:
	void addNewNoteSignal(int notePosY, int beat);

public slots:
	void createNewNote(AudioSource* audioSource, int beats);
	void pushNewNoteToQueue(NoteWidget* note);
	void clearStave();
	
};

