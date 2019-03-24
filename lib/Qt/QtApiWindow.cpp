/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "QtApi.hpp"

ui::QtApiWindow::QtApiWindow(QtApi *apiRef) : QWidget(), _apiRef(apiRef)
{
	setFixedSize(1280, 720);
	setWindowTitle("Arcade");
}

void ui::QtApiWindow::closeEvent(QCloseEvent *event)
{
	QWidget::closeEvent(event);
	_apiRef->setLastEvent(Qt::Key::Key_Escape);
}

void ui::QtApiWindow::keyPressEvent(QKeyEvent *event)
{
	QWidget::keyPressEvent(event);
	_apiRef->setLastEvent(event->key());
}
