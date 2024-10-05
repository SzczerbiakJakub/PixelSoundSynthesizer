#pragma once

#include <QLabel>
#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include "optionsviewmodel.h"
#include "data.h"
#include "menulabelwidget.h"



/// <summary>
/// Klasa reprezentująca obiekt wyboru opcji w menu.
/// </summary>
class OptionsWidget : public QLabel
{
	Q_OBJECT

public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu. </param>
	OptionsWidget(QWidget* parent, int layoutOption);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~OptionsWidget();

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	void buildMainUi(int layoutOption);

	/// <summary>
	/// Metoda przesuwająca punkt wyboru zależnie do wybranego wskaźnika na obiekt opcji.
	/// </summary>
	/// <param name=optionPtr> Wskaźnik na obiekt opcji.</param>
	void moveSelectionPoint(MenuLabelWidget* optionPtr);

	/// <summary>
	/// Iterator obecnej listy wyboru.
	/// </summary>
	std::list<int>::iterator optionIterator;


	/// <summary>
	/// Metoda ustawiająca punkt wyboru do pozycji początkowej.
	/// </summary>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	void setInitialSelectionPoint(int layoutOption);


	/// <summary>
	/// Metoda zwracająca wartość true w przypadku obecnego w obiekcie layoutu poziomego, w przeciwnym 
	/// wypadku zwraca wartość false.
	/// </summary>
	bool isHorizontalLayoutPresent();

private:

	OptionsViewModel* viewModel;

	/// <summary>
	/// Zmienna przechowująca koordynat X punktu wyboru.
	/// </summary>
	int selectionPointX;


	/// <summary>
	/// Zmienna przechowująca koordynat Y punktu wyboru.
	/// </summary>
	int selectionPointY;

	/// <summary>
	/// Wskaźnik na pionowy layout obiektu.
	/// </summary>
	QVBoxLayout* menuOptionsVerticalLayout;

	/// <summary>
	/// Wskaźnik na poziomy layout obiektu.
	/// </summary>
	QHBoxLayout* menuOptionsHorizontalLayout;

	/// <summary>
	/// Wskaźnik na widget pierwszej połowy opcji dźwięków.
	/// </summary>
	KeyOptionLabel* firstHalfLabel;

	/// <summary>
	/// Wskaźnik na widget drugiej połowy opcji dźwięków.
	/// </summary>
	KeyOptionLabel* secondHalfLabel;

	/// <summary>
	/// Wskaźnik na layout widgetu pierwszej połowy opcji dźwięków.
	/// </summary>
	QVBoxLayout* firstLabelLayout;

	/// <summary>
	/// Wskaźnik na layout widgetu drugiej połowy opcji dźwięków.
	/// </summary>
	QVBoxLayout* secondLabelLayout;

	/// <summary>
	/// Metoda umożliwiająca zmiane wyglądu obiektu.
	/// </summary>
	void paintEvent(QPaintEvent* paintEvent) override;


	/// <summary>
	/// Metoda tworząca opcje nagrań.
	/// </summary>
	void buildRecordsLabels();

	/// <summary>
	/// Metoda tworząca opcje par dźwięk-klawisz.
	/// </summary>
	void buildSoundKeyLabels();


signals:
	void pushbackMenuLabelSignal(MenuLabelWidget* menuLabel, QVBoxLayout* layout=nullptr, int optionHeight=NULL);

	void moveSelectionPointSignal(int option, QHBoxLayout* hLayout,
		KeyOptionLabel* firstHalf, KeyOptionLabel* secondHalf);

	void buildRecordsLabelsSignal(QVBoxLayout* layout);
	void buildSoundKeyLabelsSignal(QVBoxLayout* firstLayout, QVBoxLayout* secondLayout);
	void setInitialSelectionPointSignal();


public slots:
	/// <summary>
	/// Metoda przesuwająca punkt wyboru zależnie do wybranej opcji.
	/// </summary>
	/// <param name=option> Liczbowa reprezentacja zaznaczonej opcji.</param>
	void moveSelectionPointOption(int option);


private slots:
	void repaintOptions(int pointX, int pointY);
	void addNewLabel(std::string labelText, int labelHeight, QVBoxLayout* layout);

};