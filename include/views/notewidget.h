#pragma once
#include <QLabel>
#include <QTransform>
#include <QImage>
#include <QPixmap>
#include <QPen>
#include <QPainter>
#include <data.h>


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
	/// <summary>
	/// Koordynat X obiektu.
	/// </summary>
	int x;

	/// <summary>
	/// Koordynat Y obiektu.
	/// </summary>
	int y;

	/// <summary>
	/// Ilość beatów w przynależnym do obiektu dźwięku.
	/// </summary>
	int beat;

	/// <summary>
	/// Metoda zmieniająca kolor obrazu przedstawiającego obiekt.
	/// </summary>
	void setImageColor(QImage* image);

	/// <summary>
	/// Metoda zwracająca składową R koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueR();

	/// <summary>
	/// Metoda zwracająca składową G koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueG();

	/// <summary>
	/// Metoda zwracająca składową B koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueB();

	/// <summary>
	/// Metoda zwracająca obraz nutki przekształcony na kolorowy na podstawie zaimplementowanego w funkcji algorytmu.
	/// </summary>
	QImage* getRgbaNoteImage();

	/// <summary>
	/// Metoda przekształcająca pixmapę obiektu na odwróconą do góry nogami.
	/// </summary>
	QPixmap* invertPixmap(QPixmap* pixmap);
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