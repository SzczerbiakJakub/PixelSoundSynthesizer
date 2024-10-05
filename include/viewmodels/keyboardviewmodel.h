#pragma once
#include "data.h"
#include <QObject>
#include <vector>
#include "keywidget.h"


#define KEYBOARD_IMAGE_PATH "assets/keyboard.png"



class KeyboardViewModel : public QObject
{
	Q_OBJECT

public:
	KeyboardViewModel(QObject* parent=nullptr);
	~KeyboardViewModel() {};

	/// <summary>
	/// Metoda zwracająca wskaźnik na obiekt KeyWidget zależnie do określonego symbolu słownego.
	/// </summary>
	KeyWidget* getKeyWidget(std::string keySymbol);

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


	std::vector<KeyWidget*>* keyWidgetsVector;


signals:
	void pressKeySignal(int qKey);
	void releaseKeySignal(int qKey);


public slots:
	void addNewKeyToVector(KeyWidget* keyWidgetPtr);


private slots:
	void pressKey(int qKey) { emit pressKeySignal(qKey); }
	void releaseKey(int qKey) { emit releaseKeySignal(qKey); }
};

