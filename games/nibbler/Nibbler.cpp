/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "Nibbler.hpp"

void Nibbler::init()
{
	_name = new ui::UIText({100, 100}, "TEST");
	_name->setColor({255, 255, 255});

	_input = new ui::UIText({100, 150}, "INPUT");
	_input->setColor({255, 100, 100});

	_rect = new ui::UIRect({0, 0}, {250, 250});
	_rect->setBackgroundColor({255, 160, 134});
	_rect->setBorders(1, {255, 255, 255});
}

void Nibbler::tick()
{
	arcade::Engine::Graphic().clear();
	arcade::Engine::Graphic().drawText(*_name);
	arcade::Engine::Graphic().drawText(*_input);
	arcade::Engine::Graphic().drawRect(*_rect);
	arcade::Engine::Graphic().render();
}

void Nibbler::close()
{
	//TODO close ce qui a était open
}

extern "C" IGameApi *entryPoint()
{
	return new Nibbler();
}
