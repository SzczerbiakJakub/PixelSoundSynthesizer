#pragma once
#include <QLabel>
#include <QTransform>
#include <QImage>
#include <QPixmap>
#include <QObject>
#include <QPen>
#include <QPainter>
#include <data.h>
#include "noteviewmodel.h"


#define WHOLE_NOTE_IMG_PATH "assets/whole_note.png"
#define HALF_NOTE_IMG_PATH "assets/half_note.png"
#define QUARTER_NOTE_IMG_PATH "assets/quarter_note.png"
#define OCTO_NOTE_IMG_PATH "assets/octo_note.png"
#define TREBLE_CLEF_IMG_PATH "assets/treble_clef.png"
#define BASS_CLEF_IMG_PATH "assets/bass_clef.png"


/// <summary>
/// Klasa reprezentująca nutkę pojawiającą się na pięciolinii programu.
/// </summary>
class NoteWidget : public QLabel
{
	Q_OBJECT

public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=y> Pozycja Y obiektu. </param>
	/// <param name=beat> Ilość beatów w zagranym dźwięku. </param>
	NoteWidget(QWidget *parent, int y, int beat);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~NoteWidget();

	/// <summary>
	/// Metoda ustawiająca parametr x obiektu na zadaną wartość int.
	/// </summary>
	/// <param name=x> Zadany koordynat X. </param>
	void setX(int x) { this->x = x; };

	/// <summary>
	/// Metoda zwracająca wartość parametru x obiektu.
	/// </summary>
	int getX() { return x; };

	/// <summary>
	/// Metoda zwracająca wartość parametru y obiektu.
	/// </summary>
	int getY() { return y; };


private:

	NoteViewModel* viewModel;

	/// <summary>
	/// Koordynat X obiektu.
	/// </summary>
	int x;

	/// <summary>
	/// Koordynat Y obiektu.
	/// </summary>
	int y;


signals:
	void getCustomNotePixmap(int y, int beat);

private slots:
	void setCustomNotePixmap(QPixmap* pixmap, bool noteInverted);

};


/// <summary>
/// Klasa reprezentująca znak poczatkowy pięciolinii.
/// </summary>
class ClefWidget : public QLabel
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=x> Pozycja X obiektu. </param>
	/// <param name=y> Pozycja Y obiektu. </param>
	ClefWidget(QWidget* parent, int x, int y);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~ClefWidget() {};

protected:
	/// <summary>
	/// Koordynat X obiektu.
	/// </summary>
	int x;

	/// <summary>
	/// Koordynat Y obiektu.
	/// </summary>
	int y;
};


/// <summary>
/// Klasa reprezentująca znak poczatkowy oktaw wyższych pięciolinii.
/// </summary>
class TrebleClefWidget : public ClefWidget
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=x> Pozycja X obiektu. </param>
	/// <param name=y> Pozycja Y obiektu. </param>
	TrebleClefWidget(QWidget* parent, int x, int y);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~TrebleClefWidget() {};
};

/// <summary>
/// Klasa reprezentująca znak poczatkowy oktaw niższych pięciolinii.
/// </summary>
class BassClefWidget : public ClefWidget
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=x> Pozycja X obiektu. </param>
	/// <param name=y> Pozycja Y obiektu. </param>
	BassClefWidget(QWidget* parent, int x, int y);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~BassClefWidget() {};
};