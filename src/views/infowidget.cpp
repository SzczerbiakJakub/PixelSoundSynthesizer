#include "infowidget.h"



InfoWidget::InfoWidget(QWidget* parent, int layoutOption) : QLabel(parent) {
	setStyleSheet("background-color: #1f1f1f;");
	menuInfoLayout = new QVBoxLayout(this);
	buildMainUi(layoutOption);
}


void InfoWidget::buildMainUi(int layoutOption) {
	switch (layoutOption) {
	case 0:
		setFixedSize(380, 250);
		menuInfoLayout->addWidget(new MenuLabelWidget(this, ESCAPE_TEXT), 0, Qt::AlignHCenter);
		menuInfoLayout->addWidget(new MenuLabelWidget(this, ENTER_TEXT), 0, Qt::AlignHCenter);
		menuInfoLayout->addWidget(new MenuLabelWidget(this, UP_DOWN_TEXT), 0, Qt::AlignHCenter);
		break;
	case 1:
		setFixedSize(380, 0);
		break;
	case 2:
		setFixedSize(380, 150);
		menuInfoLayout->addWidget(new MenuLabelWidget(this, ENTER_RECORD_TEXT), 0, Qt::AlignHCenter);
		menuInfoLayout->addWidget(new MenuLabelWidget(this, UP_DOWN_TEXT), 0, Qt::AlignHCenter);
		break;
	case 3:
		setFixedSize(380, 70);
		if (KeyboardData::changeSoundKeyValue)
			menuInfoLayout->addWidget(new MenuLabelWidget(this, CHANGE_KEY_TEXT), 0, Qt::AlignHCenter);
		else
			menuInfoLayout->addWidget(new MenuLabelWidget(this, SELECT_SOUND_TEXT), 0, Qt::AlignHCenter);
		break;
	}
}