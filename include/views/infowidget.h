#pragma once

#include <QLabel>
#include <QVBoxLayout>
#include <QObject>
#include "menulabelwidget.h"
#include "data.h"


/// <summary>
/// Klasa reprezentująca obiekt informacyjny w menu.
/// </summary>
class InfoWidget : public QLabel
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	InfoWidget(QWidget* parent, int layoutOption);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~InfoWidget() {};

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	void buildMainUi(int layoutOption);

private:
	/// <summary>
	/// Wskaźnik na layout obiektu.
	/// </summary>
	QVBoxLayout* menuInfoLayout;
};
