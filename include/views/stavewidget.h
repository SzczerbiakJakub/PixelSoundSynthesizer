#pragma once
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QLineF>
#include <QTimer>
#include <QThread>
#include <vector>
#include <queue>
#include "data.h"
#include "notewidget.h"
#include "threads.h"
#include "staveviewmodel.h"


/// <summary>
/// Klasa reprezentująca pięciolinię w programie.
/// </summary>
class StaveWidget : public QLabel
{
	Q_OBJECT
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget.</param>
	StaveWidget(QWidget * parent);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~StaveWidget();


private:

	StaveViewModel* viewModel;

	TrebleClefWidget* trebleClef;

	BassClefWidget* bassClef;


	/// <summary>
	/// Metoda umożliwiająca zmianę wyglądu obiektu.
	/// </summary>
	void paintEvent(QPaintEvent* event) override;

	/// <summary>
	/// Metoda rysująca pięciolinię wysokich tonów.
	/// </summary>
	void drawHighPitchLines(QPainter* painter);

	/// <summary>
	/// Metoda rysująca pięciolinię niskich tonów.
	/// </summary>
	void drawLowPitchLines(QPainter* painter);

	/// <summary>
	/// Metoda rysująca pięciolinie.
	/// </summary>
	void buildStaveLines(QPainter* painter);


signals:
	void createNewNoteSignal(AudioSource* audioSource, int beats);
	void pushNewNoteSignal(NoteWidget* note);
	void clearStaveSignal();


private slots:
	void addNewNote(int notePosY, int beat);
};