#pragma once

#include <QObject>
#include <QImage>
#include <QPixmap>



#define WHOLE_NOTE_IMG_PATH "assets/whole_note.png"
#define HALF_NOTE_IMG_PATH "assets/half_note.png"
#define QUARTER_NOTE_IMG_PATH "assets/quarter_note.png"
#define OCTO_NOTE_IMG_PATH "assets/octo_note.png"
#define TREBLE_CLEF_IMG_PATH "assets/treble_clef.png"
#define BASS_CLEF_IMG_PATH "assets/bass_clef.png"



class NoteViewModel : public QObject
{
	Q_OBJECT

public:
	NoteViewModel(QObject* parent=nullptr);
	~NoteViewModel();

private:
	bool inverted;

	/// <summary>
	/// Metoda zmieniająca kolor obrazu przedstawiającego obiekt.
	/// </summary>
	void setImageColor(QImage* image, int y);

	/// <summary>
	/// Metoda zwracająca składową R koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueR(int y);

	/// <summary>
	/// Metoda zwracająca składową G koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueG(int y);

	/// <summary>
	/// Metoda zwracająca składową B koloru RGB zależnie od położenia obiektu na pięciolinii.
	/// </summary>
	int getValueB(int y);

	/// <summary>
	/// Metoda zwracająca obraz nutki przekształcony na kolorowy na podstawie zaimplementowanego w funkcji algorytmu.
	/// </summary>
	QImage* getRgbaNoteImage(int y, int beat);

	/// <summary>
	/// Metoda przekształcająca pixmapę obiektu na odwróconą do góry nogami.
	/// </summary>
	QPixmap* invertPixmap(QPixmap* pixmap);

signals:
	void sendCustomNotePixmap(QPixmap* pixmap, bool noteInverted);

public slots:
	void createCustomNotePixmap(int y, int beat);

};

