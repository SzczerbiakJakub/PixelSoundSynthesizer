#pragma once
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFont>
#include <QPainter>
#include <QFontDatabase>
#include <data.h>


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
	/// Metoda przemieszczająca punkt wyboru zależnie do wybranej opcji.
	/// </summary>
	/// <param name=option> Wskaźnik na obiekt MenuLabelWidget. </param>
	void moveSelectionPoint(MenuLabelWidget* option);

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

};


/// <summary>
/// Klasa reprezentująca obiekt informacyjny w menu.
/// </summary>
class MenuInfoWidget : public QLabel
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	MenuInfoWidget(QWidget* parent, int layoutOption);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~MenuInfoWidget() {};

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


/// <summary>
/// Klasa reprezentująca obiekt wyboru opcji w menu.
/// </summary>
class MenuOptionsWidget : public QLabel
{
public:
	/// <summary>
	/// Konstruktor klasy.
	/// </summary>
	/// <param name=parent> Nadrzędny widget. </param>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu. </param>
	MenuOptionsWidget(QWidget* parent, int layoutOption);

	/// <summary>
	/// Destruktor klasy.
	/// </summary>
	~MenuOptionsWidget();

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	/// <param name=layoutOption> Liczbowa reprezentacja obecnego layoutu menu.</param>
	void buildMainUi(int layoutOption);

	/// <summary>
	/// Metoda przesuwająca punkt wyboru zależnie do wybranej opcji.
	/// </summary>
	/// <param name=option> Liczbowa reprezentacja zaznaczonej opcji.</param>
	void moveSelectionPoint(int option);

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
	/// Metoda zwracająca wskaźnik na pierwszy obiekt opcji.
	/// </summary>
	MenuLabelWidget* getFirstMenuLabel() { return optionsPtrVector->front(); };

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
	/// Wskaźnik na wektor wskaźników na opcje menu.
	/// </summary>
	std::vector<MenuLabelWidget*>* optionsPtrVector;

	/// <summary>
	/// Metoda tworząca opcje nagrań.
	/// </summary>
	void buildRecordsLabels();

	/// <summary>
	/// Metoda tworząca opcje par dźwięk-klawisz.
	/// </summary>
	void buildSoundKeyLabels();
};

/// <summary>
/// Klasa reprezentująca menu programu.
/// </summary>
class MenuWidget : public QLabel
{
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
	
	/// <summary>
	/// Metoda wywołująca kolejną opcję.
	/// </summary>
	void nextOption();

	/// <summary>
	/// Metoda wywołująca poprzednią opcję.
	/// </summary>
	void prevOption();

	/// <summary>
	/// Metoda wywołująca opcję po lewo od obecnej.
	/// </summary>
	void leftRelativeOption();

	/// <summary>
	/// Metoda wywołująca opcję po prawo od obecnej.
	/// </summary>
	void rightRelativeOption();

	/// <summary>
	/// Metoda ponownie tworzy GUI obiektu.
	/// </summary>
	void rebuildUi();

	/// <summary>
	/// Metoda odpowiada za wybór opcji.
	/// </summary>
	void selectOption();

	/// <summary>
	/// Metoda zwraca obecny layout menu.
	/// </summary>
	int getCurrentLayout() { return *layoutIterator; }

	/// <summary>
	/// Metoda zwraca obecną opcję menu.
	/// </summary>
	int getCurrentOption() { return *optionIterator; }

	/// <summary>
	/// Metoda zmienia pare dźwięk-klawisz na dźwięk-wybrany_klawisz dla ID wybranego klawisza.
	/// </summary>
	/// <param name=selectedKeyID> ID wybranego klawisza. </param>
	void changeSoundKeyPair(int selectedKeyID);
	
private:
	/// <summary>
	/// Iterator listy layoutów menu.
	/// </summary>
	std::list<int>::iterator layoutIterator;

	/// <summary>
	/// Iterator obecnej listy opcji.
	/// </summary>
	std::list<int>::iterator optionIterator;

	/// <summary>
	/// Wskaźnik na obecną listę opcji.
	/// </summary>
	std::list<int>* currentListPtr;

	/// <summary>
	/// Wskaźnik na layout obiektu.
	/// </summary>
	QVBoxLayout* menuWidgetLayout;

	/// <summary>
	/// Wskaźnik na widget informacyjny obiektu.
	/// </summary>
	MenuInfoWidget* menuInfoWidget;

	/// <summary>
	/// Wskaźnik na widget zawierający opcje obiektu.
	/// </summary>
	MenuOptionsWidget* menuOptionsWidget;

	/// <summary>
	/// Metoda tworząca GUI obiektu.
	/// </summary>
	void buildUi(int layoutOption);

	/// <summary>
	/// Metoda aktualizująca punkt wyboru.
	/// </summary>
	void updateSelectionPoint();

	/// <summary>
	/// Metoda aktualizuje iterator dla nowej listy.
	/// </summary>
	/// <param name=layoutOption> Liczbowa wartość danego layoutu menu. </param>
	void newListIterator(int layoutOption);

	/// <summary>
	/// Zmienna logiczna zawierająca informację na temat chwilowego przemieszczania punktu wyboru opcji.
	/// </summary>
	bool movingSelectionPoint;

	/// <summary>
	/// Zmienna logiczna zawierająca informację na temat chwilowego zmieniania klawisza dla dźwięku.
	/// </summary>
	bool changingKey;

};