#pragma once

#include <QObject>
#include "data.h"


class MenuViewModel : public QObject
{
	Q_OBJECT

public:
	MenuViewModel(QObject* parent = nullptr);
	~MenuViewModel();

	/// <summary>
	/// Metoda ponownie tworzy GUI obiektu.
	/// </summary>
	void rebuildUi();

	/// <summary>
	/// Metoda zwraca obecny layout menu.
	/// </summary>
	int getCurrentLayout() { return *layoutIterator; }

	/// <summary>
	/// Metoda zwraca obecną opcję menu.
	/// </summary>
	int getCurrentOption() { return *optionIterator; }


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


signals:
	void moveSelectionPointSignal(int option);
	void rebuildUISignal(int layoutOption);
	void displaySelectedAudioSignal(int option);

	void startRecordingSignal();
	void stopRecordingSignal();

	void startPlayingSignal();
	void stopPlayingSignal();


public slots:
	/// <summary>
	/// Metoda odpowiada za wybór opcji.
	/// </summary>
	void selectOption();

	/// <summary>
	/// Metoda wywołująca opcję po lewo od obecnej.
	/// </summary>
	void leftRelativeOption();

	/// <summary>
	/// Metoda wywołująca opcję po prawo od obecnej.
	/// </summary>
	void rightRelativeOption();

	/// <summary>
	/// Metoda wywołująca kolejną opcję.
	/// </summary>
	void nextOption();

	/// <summary>
	/// Metoda wywołująca poprzednią opcję.
	/// </summary>
	void prevOption();


	/// <summary>
	/// Metoda zmienia pare dźwięk-klawisz na dźwięk-wybrany_klawisz dla ID wybranego klawisza.
	/// </summary>
	/// <param name=selectedKeyID> ID wybranego klawisza. </param>
	void changeSoundKeyPair(int selectedKeyID);
};

