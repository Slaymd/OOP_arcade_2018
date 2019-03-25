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
	_name->setColor({0, 168, 255});

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
	if (!_reversed) {
		_rect->setPosition({_rect->getPosition().x + 1, _rect->getPosition().y});
		if (_rect->getPosition().x >= 59)
			_reversed = true;
	} else {
		_rect->setPosition({_rect->getPosition().x - 1, _rect->getPosition().y});
		if (_rect->getPosition().x <= 0)
			_reversed = false;
	}
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
