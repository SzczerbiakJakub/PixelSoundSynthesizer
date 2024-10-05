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



	KeyboardViewModel* getViewModel() { return viewModel; }
		

private:

	KeyboardViewModel* viewModel;

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




signals:
	void keyPressedSignal(int qKey);
	void keyReleasedSignal(int qKey);
	void newKeyWidgetCreated(KeyWidget* keyWidget);

private slots:

};