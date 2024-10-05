#pragma once

#include <QObject>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include "menulabelwidget.h"
#include "data.h"


class OptionsViewModel : public QObject
{
	Q_OBJECT

public:
	OptionsViewModel(QObject* parent = nullptr);
	~OptionsViewModel();

private:

	/// <summary>
	/// Wskaźnik na wektor wskaźników na opcje menu.
	/// </summary>
	std::vector<MenuLabelWidget*>* optionsPtrVector;


	void setSelectionPoint(MenuLabelWidget* option);
	void setSelectionPoint(KeyOptionLabel* optionLabel, MenuLabelWidget* option);
	void setSelectionPoint(int x, int y);

	void resetSelectionPoint(KeyOptionLabel* optionLabel);


signals:
	void repaintOptionsSignal(int pointX, int pointY);
	void addNewLabelSignal(std::string labelText, int labelHeight, QVBoxLayout* layout);


public slots:
	void pushbackMenuLabel(MenuLabelWidget* menuLabel, QVBoxLayout* layout=nullptr, int optionHeight = NULL);

	void moveSelectionPoint(int option, QHBoxLayout* hLayout,
		KeyOptionLabel* firstHalf, KeyOptionLabel* secondHalf);

	void buildRecordsLabels(QVBoxLayout* layout);
	void buildSoundKeyLabels(QVBoxLayout* firstLayout, QVBoxLayout* secondLayout);
	void setInitialSelectionPoint();
};

