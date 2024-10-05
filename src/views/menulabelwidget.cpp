#include "menulabelwidget.h"



MenuLabelWidget::MenuLabelWidget(QWidget* parent, std::string text) : QLabel(parent) {
	setStyleSheet("border: none; color: white;");
	setText(QString::fromStdString(text));
	adjustSize();
	setFont(FONT);
}


KeyOptionLabel::KeyOptionLabel(QWidget* parent) : QLabel(parent) {

}


void KeyOptionLabel::paintEvent(QPaintEvent* paintEvent) {

	if (selectionPointX != NULL && selectionPointY != NULL)
	{
		QPainter painter(this);
		painter.setPen(QPen(Qt::black, 3));
		painter.setBrush(QBrush(Qt::white));

		painter.drawEllipse(QPoint(selectionPointX, selectionPointY), 8, 8);
	}
}


void KeyOptionLabel::moveSelectionPoint(MenuLabelWidget* option) {
	selectionPointX = option->x() - 20;
	selectionPointY = option->y() + option->height() / 2;
	repaint();
};



void KeyOptionLabel::repaintKeyOptions(int pointX, int pointY) {

	selectionPointX = pointX;
	selectionPointY = pointY;
	repaint();
}