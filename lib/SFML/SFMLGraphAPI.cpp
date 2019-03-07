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
}

void SFMLGraphAPI::addText()
{

}

void SFMLGraphAPI::abortDisplay()
{
	_win->close();
	delete _win;
}
