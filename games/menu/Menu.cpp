/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "Menu.hpp"

static size_t i = 0;

void Menu::init()
{
	_menu = new ui::UIText({600, 100}, "MENU");
	_menu->setColor({255, 255, 0});

	int xy[2] = {580, 300};

	for (; i < arcade::Engine::instance().getGameName().size(); i++) {
		_gameName.push_back(new ui::UIText({xy[0], xy[1]},
			arcade::Engine::instance().getGameName()[0]));
		arcade::Engine::instance().rotateGames();
		_gameName[i]->setColor({255, 255, 200});
		xy[1] += 100;
	}
}

void Menu::tick()
{
	arcade::Engine::Graphic().clear();
	arcade::Engine::Graphic().drawText(*_menu);
	for (size_t j = 0; j < i; j++) {
		arcade::Engine::Graphic().drawText(*_gameName[j]);
	}
	arcade::Engine::Graphic().render();
}

void Menu::close()
{
	//TODO close ce qui a était open
}

extern "C" IGameApi *entryPoint()
{
	return new Menu();
}
