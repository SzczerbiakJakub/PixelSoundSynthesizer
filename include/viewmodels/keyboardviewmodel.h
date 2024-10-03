#pragma once
#include "data.h"
#include <QObject>
#include <QTimer>
#include <vector>
#include "keywidget.h"




class KeyViewModel
{
public:

private:


};


class KeyboardWidget;


class KeyboardViewModel : public QObject
{
	Q_OBJECT

public:
	KeyboardViewModel(QObject* parent, KeyboardWidget* keyboardWidgetPtr);
	~KeyboardViewModel() {};
	//void appendNewKeyWidget(KeyWidget* keyWidgetPtr);

private:
	QTimer* updateTimer;
	KeyboardWidget* view;
	void buildKeyboard();

	std::vector<KeyWidget*>* keyWidgetsVector;

signals:
	void updateTimeout();

private slots:

	/// <summary>
	/// Metoda wywoływana gdy upłynie czas timera klawiatury. Odpowiada za przywrócenie domyślnego wyglądu 
	/// klawiszom.
	/// </summary>
	void updateKeysPixmaps();
};

