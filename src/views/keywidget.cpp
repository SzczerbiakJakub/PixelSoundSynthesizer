#include "keywidget.h"



KeyWidget::KeyWidget(QWidget* parent, std::string& keySymbol, int id) : QLabel(parent) {

	viewModel = new	KeyViewModel(keySymbol, id);
	QObject::connect(viewModel, &KeyViewModel::sendPixmap, this, &KeyWidget::updatePixmap);

	emit viewModel->sendPixmap(viewModel->getReleasedKeyPixmap());
}


KeyWidget::KeyWidget(const KeyWidget& otherKeyWidget) : QLabel(otherKeyWidget.parentWidget()) {

}


KeyWidget::~KeyWidget() {
	delete viewModel;
}


void KeyWidget::updatePixmap(QPixmap* pixmap) {
	setPixmap(*pixmap);
}