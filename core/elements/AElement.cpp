/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "AElement.hpp"

void ui::AElement::setPosition(ui::position pos)
{
	_pos = pos;
}

ui::position ui::AElement::getPosition()
{
	return _pos;
}

void ui::AElement::setSize(ui::size size)
{
	_size = size;
}

ui::size ui::AElement::getSize()
{
	return _size;
}

void ui::AElement::setBackgroundColor(ui::color color)
{
	_backgroundColor = color;
}

ui::color ui::AElement::getBackgroundColor()
{
	return _backgroundColor;
}

void ui::AElement::setBackgroundImage(std::string string)
{
	_backgroundImage = string;
}

std::string ui::AElement::getBackgroundImage()
{
	return _backgroundImage;
}

void ui::AElement::setBorders(int weight, ui::color color)
{
	_borderWeight = weight;
	_borderColor = color;
}

void ui::AElement::setBorderColor(ui::color color)
{
	_borderColor = color;
}

ui::color ui::AElement::getBorderColor()
{
	return _borderColor;
}

void ui::AElement::setBorderWeight(int weight)
{
	_borderWeight = weight;
}

int ui::AElement::getBorderWeight()
{
	return _borderWeight;
}