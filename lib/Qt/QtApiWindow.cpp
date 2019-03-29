/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "QtApi.hpp"

ui::QtApiWindow::QtApiWindow(QtApi *apiRef) : QWidget(), _apiRef(apiRef)
{
	setFixedSize(60 * _scale, 60 * _scale);
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

void ui::QtApiWindow::paintEvent(QPaintEvent *event)
{
	(void)event;
	QPainter painter(this);

	painter.setRenderHint(QPainter::Antialiasing);
	painter.setRenderHint(QPainter::HighQualityAntialiasing);
	painter.setPen(Qt::NoPen);

	for (int i = 0; i < _lastIndex; i++) {
		if (_rects.find(i) != _rects.end())
			displayRect(painter, _rects.find(i)->second);
		else if (_texts.find(i) != _texts.end())
			displayText(painter, _texts.find(i)->second);
	}

	_lastIndex = 0;
	_rects.clear();
	_texts.clear();
}

QColor ui::QtApiWindow::getQtColor(ui::color color)
{
	return {color.r, color.g, color.b};
}

void ui::QtApiWindow::displayRect(QPainter &painter, ui::UIRect rect)
{
	QRect qRect;
	QImage qImage;
	QPen pen;

	qRect.setRect(rect.getPosition().x * _scale, rect.getPosition().y * _scale,
		rect.getSize().width * _scale, rect.getSize().height * _scale);
	if (rect.getBorderWeight() != 0) {
		pen.setWidth(rect.getBorderWeight() * _scale);
		pen.setColor(getQtColor(rect.getBorderColor()));
		pen.setStyle(Qt::SolidLine);
		pen.setJoinStyle(Qt::MiterJoin);
	} else
		pen = Qt::NoPen;
	painter.setPen(pen);
	if (rect.getBackgroundImage().size() > 0) {
		if (qImage.load(rect.getBackgroundImage().c_str())) {
			painter.drawImage(qRect, qImage);
			painter.setPen(Qt::NoPen);
			return;
		}
	}
	painter.fillRect(qRect, getQtColor(rect.getBackgroundColor()));
	painter.drawRect(qRect);
	painter.setPen(Qt::NoPen);
}

void ui::QtApiWindow::displayText(QPainter &painter, ui::UIText text)
{
	painter.setPen(getQtColor(text.getColor()));
	painter.drawText(text.getPosition().x * _scale, text.getPosition().y * _scale, text.getString().c_str());
}

void ui::QtApiWindow::addRect(ui::UIRect rect)
{
	_rects.insert({_lastIndex, rect});
	_lastIndex += 1;
}

void ui::QtApiWindow::addText(ui::UIText text)
{
	_texts.insert({_lastIndex, text});
	_lastIndex += 1;

}
