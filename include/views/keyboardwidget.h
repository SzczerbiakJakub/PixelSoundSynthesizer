#pragma once
#include <QLabel>
#include <QTimer>
#include <QLabel>
#include <QPixmap>
#include "keywidget.h"
#include "keyboardviewmodel.h"



#define KEYBOARD_IMAGE_PATH "assets/keyboard.png"





/// <summary>
/// Klasa reprezentująca klawiaturę na ekranie.
/// </summary>
class KeyboardWidget : public QLabel
{
	Q_OBJECT

public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget.</param>
	KeyboardWidget(QWidget* parent);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~KeyboardWidget();

	/// <summary>
	/// Metoda zwracająca wskaźnik na obiekt KeyWidget zależnie do określonego symbolu słownego.
	/// </summary>
	KeyWidget * getKeyWidget(std::string keySymbol);

	/// <summary>
	/// Metoda zwracająca wskaźnik na obiekt KeyWidget zależnie do określonego ID klawisza.
	/// </summary>
	KeyWidget* getKeyWidget(int keyID);


	/// <summary>
	/// Metoda zwracająca wektor przechowujący wskaźniki do obiektów KeyWidget przynależnych do klawiatury.
	/// </summary>
	std::vector<KeyWidget*> getKeyWidgetsVector() { return *keyWidgetsVector; };
		

private:
	/// <summary>
	/// Wskaźnik na pixmapę obiektu.
	/// </summary>
	QPixmap* keyboardPixmap;

	/// <summary>
	/// Metoda dodająca nowy obiekt KeyWidget do klawiatury.
	/// </summary>
	/// <param name = keySymbol> Symbol słowny sprzężony z obiektem.</param>
	/// <param name = id> ID klawisza sprzężonego z obiektem.</param>
	/// <param name = x> Pozycja X dodawanego obiektu.</param>
	/// <param name = y> Pozycja Y dodawanego obiektu.</param>
	void addNewKeyWidget(std::string keySymbol, int id, int x, int y);

	/// <summary>
	/// Metoda tworząca GUI klawiatury.
	/// </summary>
	void buildKeyboard();

	/// <summary>
	/// Wskaźnik na wektor wskaźników na klawisze klawiatury.
	/// </summary>
	std::vector<KeyWidget*>* keyWidgetsVector;

	/// <summary>
	/// Wskaźnik na timer renderujący klawiaturę.
	/// </summary>
	QTimer* updateTimer;


private slots:

	/// <summary>
	/// Metoda wywoływana gdy upłynie czas timera klawiatury. Odpowiada za przywrócenie domyślnego wyglądu 
	/// klawiszom.
	/// </summary>
	void onTimeout();
};