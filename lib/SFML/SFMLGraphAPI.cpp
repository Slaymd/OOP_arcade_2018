/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Maxime
*/

#include "../../include/SFMLGraphAPI.hpp"

extern "C" {
	IGraphAPI *getGraphAPI() {
		return (new SFMLGraphAPI());
	}
}

void SFMLGraphAPI::initDisplay(const std::string &title)
{
	_win = new sf::RenderWindow(sf::VideoMode(1280, 720), title);
	_win->setFramerateLimit(60);
	_active = true;
}

void SFMLGraphAPI::clear()
{
	_win->clear(sf::Color::White);
}

void SFMLGraphAPI::display()
{
	_win->display();
}

void SFMLGraphAPI::abortDisplay()
{
	printf("cc\n");
	_win->close();
	delete _win;
	_active = false;
	printf("abort disp\n");
}

void SFMLGraphAPI::drawSquare(int x, int y, std::string color)
{
	sf::Color colorSfml = colorList[color];
	sf::RectangleShape rectangle(sf::Vector2f(x, y));
	rectangle.setFillColor(colorSfml);
	_win->draw(rectangle);
}

bool SFMLGraphAPI::isActive(sf::Event event)
{
	while (_win->pollEvent(event))
	    if (event.type == sf::Event::Closed)
		    return !_active;
	return _active;
}

void SFMLGraphAPI::setTitle(const std::string &title)
{
	_win->setTitle(title);
}
