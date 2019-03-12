/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_IGRAPHAPI_HPP
#define ARCADE_IGRAPHAPI_HPP

#include <SFML/Graphics.hpp>
#include <string>

class IGraphAPI
{
	public:
	virtual void initDisplay(const std::string &) = 0;
	virtual void display() = 0;
	virtual void abortDisplay() = 0;
	virtual void drawSquare(int x, int y, std::string color) = 0;
	virtual void clear()= 0;

	virtual void setTitle(const std::string &) = 0;
	virtual bool isActive(sf::Event event) = 0;

};

extern "C" IGraphAPI *getGraphAPI();

#endif //ARCADE_IGRAPHAPI_HPP
