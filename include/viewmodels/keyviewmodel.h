#pragma once
#include <QObject>
#include <QPixmap>
#include <QDebug>


#define KEY_PIXMAP_DIR_PATH "assets/"
#define KEY_PIXMAP_EXTENSION ".png"
#define HIGHLIGHTED_POSTFIX "_pressed"



class KeyViewModel : public QObject
{
	Q_OBJECT

public:
	KeyViewModel(std::string keySymbol, int keyID, QObject* parent = nullptr);
	~KeyViewModel();
	std::string getKeySymbol() { return keySymbol; };
	int getKeyID() { return keyID; };

	/// <summary>
	/// Metoda zwracająca wartość parametru pressed.
	/// </summary>
	bool isPressed() { return pressed; };
	QPixmap* getReleasedKeyPixmap() { return keyPixmap; }

private:

	/// <summary>
	/// Parametr przechowujący ID klawisza przypisanego do obiektu.
	/// </summary>
	int keyID;

	/// <summary>
	/// PArametr przechowujący symbol słowny klawisza.
	/// </summary>
	std::string keySymbol;

	/// <summary>
	/// Parametr logiczny przechowujący wartość o wciśnięciu klawisza.
	/// </summary>
	bool pressed;

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

signals:
	void sendPixmap(QPixmap* pixmapPtr);

public slots:
	void pressKey(int qKey);
	void releaseKey(int qKey);
};

