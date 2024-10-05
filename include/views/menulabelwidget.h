#pragma once

#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QPainter>
#include <QFontDatabase>




#define ESCAPE_TEXT "[ESCAPE] clear stave"
#define ENTER_TEXT "[ENTER] select"
#define UP_DOWN_TEXT "[←][↑][→][↓] navigate"
#define SELECT_SOUND_TEXT "Select the sound..."
#define CHANGE_KEY_TEXT "Press key to change..."


#define ENTER_RECORD_TEXT "[ESCAPE] play record"

#define RECORD_SOUND "Record new sound"
#define STOP_RECORDING "Stop recording"
#define RECORDS_MENU "Audio records menu"
#define CHANGE_KEYS "Change sound keys"


#define BACK_TO_MAIN "Back..."


#define PIXEL_FONT_PATH "assets/PressStart2P-Regular.ttf"

#define FONT \
		([]() -> QFont { \
			int fontId = QFontDatabase::addApplicationFont(PIXEL_FONT_PATH); \
			if (fontId != -1) { \
				QString pixelFont = QFontDatabase::applicationFontFamilies(fontId).at(0); \
				return QFont(pixelFont, 10, QFont::Bold); \
			} else { \
				QFont("Arial", 15, QFont::Bold); \
			} \
		}())




/// <summary>
/// Klasa reprezentująca obiekt tekstowy w menu.
/// </summary>
class MenuLabelWidget : public QLabel
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=text> Tekst wewnątrz obiektu </param>
	MenuLabelWidget(QWidget* parent, std::string text);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~MenuLabelWidget() {};

};


/// <summary>
/// Klasa reprezentująca obiekt <dźwiek-klawisz> w menu zmiany klawisza.
/// </summary>
class KeyOptionLabel : public QLabel
{
	Q_OBJECT

public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	KeyOptionLabel(QWidget* parent);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~KeyOptionLabel() {};

	/// <summary>
	/// Metoda resetująca punkt wyboru do stanu początkowego dla danego layoutu menu.
	/// </summary>
	void resetSelectionPoint() { selectionPointX = NULL; selectionPointX = NULL; }

	/// <summary>
	/// Metoda ustawiająca koordynat X punktu wyboru.
	/// </summary>
	/// <param name=x> Wartość liczbowa koordynatu x. </param>
	void setSelectionPointX(int x) { selectionPointX = x; }

	/// <summary>
	/// Metoda ustawiająca koordynat Y punktu wyboru.
	/// </summary>
	/// <param name=y> Wartość liczbowa koordynatu y. </param>
	void setSelectionPointY(int y) { selectionPointY = y; }


	void repaintKeyOptions(int pointX, int pointY);

private:
	/// <summary>
	/// Zmienna przechowująca koordynat X punktu wyboru.
	/// </summary>
	int selectionPointX;

	/// <summary>
	/// Zmienna przechowująca koordynat Y punktu wyboru.
	/// </summary>
	int selectionPointY;

	/// <summary>
	/// Metoda umożliwiająca zmianę wyglądu obiektu.
	/// </summary>
	void paintEvent(QPaintEvent* paintEvent) override;


public slots:
	/// <summary>
	/// Metoda przemieszczająca punkt wyboru zależnie do wybranej opcji.
	/// </summary>
	/// <param name=option> Wskaźnik na obiekt MenuLabelWidget. </param>
	void moveSelectionPoint(MenuLabelWidget* option);

};
