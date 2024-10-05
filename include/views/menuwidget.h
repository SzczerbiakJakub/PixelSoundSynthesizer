#pragma once

#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include "infowidget.h"
#include "optionswidget.h"
#include "menuviewmodel.h"


/// <summary>
/// Klasa reprezentująca menu programu.
/// </summary>
class MenuWidget : public QLabel
{
	Q_OBJECT

public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	MenuWidget(QWidget* parent);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~MenuWidget();


private:

	MenuViewModel* viewModel;

	/// <summary>
	/// Wskaźnik na layout obiektu.
	/// </summary>
	QVBoxLayout* menuWidgetLayout;

	/// <summary>
	/// Wskaźnik na widget informacyjny obiektu.
	/// </summary>
	InfoWidget* menuInfoWidget;

	/// <summary>
	/// Wskaźnik na widget zawierający opcje obiektu.
	/// </summary>
	OptionsWidget* menuOptionsWidget;

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	void buildUi(int layoutOption=0);


signals:
	void selectOptionSignal();
	void leftRelativeOptionSignal();
	void rightRelativeOptionSignal();
	void nextOptionSignal();
	void prevOptionSignal();
	void changeSoundKeyPairSignal(int selectedKeyID);
	void displaySelectedAudioSignal(int option);


private slots:

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	void rebuildUI(int layoutOption);

	void displaySelectedAudio(int option);

};