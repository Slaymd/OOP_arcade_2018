/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
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

void SFMLGraphAPI::display()
{
	sf::Event event;

	while (_win->pollEvent(event))
		if (event.type == sf::Event::Closed)
			abortDisplay();
	_win->clear(sf::Color::Red);
	//TODO: display elements
	_win->display();
}

void SFMLGraphAPI::abortDisplay()
{
	_win->close();
	delete _win;
	_active = false;
}

bool SFMLGraphAPI::isActive()
{
	return _active;
}

void SFMLGraphAPI::setTitle(const std::string &title)
{
	_win->setTitle(title);
}
