/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "Nibbler.hpp"

void Nibbler::init()
{
	_name = new ui::UIText({2, 8}, "TEST");
	_name->setColor({255, 255, 255});

	_input = new ui::UIText({2, 7}, " viatransit.fr ");
	_input->setColor({255, 255, 255});
	_input->setBackgroundColor({26, 186, 254});

	_rect = new ui::UIRect({0, 0}, {6, 6});
	_rect->setBackgroundColor({255, 160, 134});
	_rect->setBorders(1, {255, 255, 255});
}

void Nibbler::tick(int event)
{
	arcade::Engine::Graphic().clear();
	arcade::Engine::Graphic().drawRect(*_rect);
	arcade::Engine::Graphic().drawText(*_name);
	arcade::Engine::Graphic().drawText(*_input);
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
