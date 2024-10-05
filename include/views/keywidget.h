#pragma once

#include <QLabel>
#include <QWidget>
#include <QObject>
#include "keyviewmodel.h"



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


	KeyViewModel* getViewModel() { return viewModel; }

private:
	KeyViewModel* viewModel;

private slots:
	/// <summary>
	/// Metoda aktualizująca wygląd klawisza zależnie do wartości parametru pressed.
	/// </summary>
	void updatePixmap(QPixmap* pixmap);


};
