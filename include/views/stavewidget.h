#pragma once
#include <QLabel>
#include <QPainter>
#include <QPen>
#include <QLineF>
#include <QTimer>
#include <QThread>
#include <vector>
#include <queue>
#include <data.h>
#include <notewidget.h>
#include <threads.h>



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

	/// <summary>
	/// Metoda dodająca nutkę.
	/// </summary>
	/// <param name=audioSource> Wskaźnik na źródło dźwięku.</param>
	/// <param name=beat> Ilość beatów w odebranym dźwięku.</param>
	void addNote(AudioSource* audioSource, int beat);

	/// <summary>
	/// Metoda tworząca nową nutkę.
	/// </summary>
	/// <param name=audioSource> Wskaźnik na źródło dźwięku.</param>
	/// <param name=beats> Ilość beatów w odebranym dźwięku.</param>
	void newNote(AudioSource* audioSource, int beats);

	/// <summary>
	/// Metoda czyszcząca pięciolinię.
	/// </summary>
	void clearStave();

	/// <summary>
	/// Metoda zwracająca kolejkę wskaźników do obiektów nutek.
	/// </summary>
	std::queue<NoteWidget*> getNotes() { return *notes; };

private:
	/// <summary>
	/// Wskaźnik do kolejki wskaźników nutek
	/// </summary>
	std::queue<NoteWidget*>* notes;

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
	/// Metoda przemieszczająca nutki w stronę klucza.
	/// </summary>
	void pushNotes(std::queue<NoteWidget*>* notesQueue);

	/// <summary>
	/// Metoda rysująca pięciolinie.
	/// </summary>
	void buildStaveLines(QPainter* painter);
};