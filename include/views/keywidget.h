#pragma once

#include <QLabel>
#include <QWidget>
#include <QObject>



#define KEY_PIXMAP_DIR_PATH "assets/"
#define KEY_PIXMAP_EXTENSION ".png"
#define HIGHLIGHTED_POSTFIX "_pressed"


/// <summary>
/// Klasa reprezentująca klawisz klawiatury na ekranie.
/// </summary>
class KeyWidget : public QLabel
{
	Q_OBJECT

public:

	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget.</param>
	/// <param name=keySymbol> Symbol klawisza.</param>
	/// <param name=id> ID odpowiadającego klawisza.</param>
	KeyWidget(QWidget* parent, std::string& keySymbol, int id);

	/// <summary>
	/// Konstruktor kopiujący klasy.
	/// </summary>
	/// <param name=otherKeyWidget> Inny obiekt klasy KeyWidget.</param>
	KeyWidget(const KeyWidget& otherKeyWidget);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~KeyWidget();

	/// <summary>
	/// Metoda ustawiająca wartość zmiennej pressed na true.
	/// </summary>
	void highlightPressedKey() { pressed = true; };

	/// <summary>
	/// Metoda ustawiająca wartość parametru pressed na false.
	/// </summary>
	void unhighlightPressedKey() { pressed = false; };

	/// <summary>
	/// Metoda aktualizująca wygląd klawisza zależnie do wartości parametru pressed.
	/// </summary>
	void updatePixmap();

	/// <summary>
	/// Metoda zwracająca symbol klawisza.
	/// </summary>
	std::string getKeySymbol() { return keySymbol; };

	/// <summary>
	/// Metoda zwracająca ID klawisza.
	/// </summary>
	int getKeyID() { return keyID; };

	/// <summary>
	/// Metoda zwracająca wartość parametru pressed.
	/// </summary>
	bool isPressed() { return pressed; };


private:
	/// <summary>
	/// Parametr logiczny przechowujący wartość o wciśnięciu klawisza.
	/// </summary>
	bool pressed;

	/// <summary>
	/// Parametr przechowujący ID klawisza przypisanego do obiektu.
	/// </summary>
	int keyID;

	/// <summary>
	/// PArametr przechowujący symbol słowny klawisza.
	/// </summary>
	std::string keySymbol;

	/// <summary>
	/// Wskaźnik na pixmapę zawierający wygląd klawisza niewciśniętego.
	/// </summary>
	QPixmap* keyPixmap;

	/// <summary>
	/// Wskaźnik na pixmapę zawierający wygląd klawisza wciśniętego.
	/// </summary>
	QPixmap* pressedKeyPixmap;

	/// <summary>
	/// Metoda inline zwracająca ścieżkę względną do pliku zawierającego pixmapę klawisza niewciśniętego.
	/// </summary>
	inline std::string getPixmapPath() { return KEY_PIXMAP_DIR_PATH + keySymbol + KEY_PIXMAP_EXTENSION; };

	/// <summary>
	/// Metoda inline zwracająca ścieżkę względną do pliku zawierającego pixmapę klawisza wciśniętego.
	/// </summary>
	inline std::string getHighlightedPixmapPath() {
		return KEY_PIXMAP_DIR_PATH + keySymbol + HIGHLIGHTED_POSTFIX + KEY_PIXMAP_EXTENSION;
	};
};
