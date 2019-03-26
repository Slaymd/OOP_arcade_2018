/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "Menu.hpp"

void Menu::init()
{
	auto engine = arcade::Engine::instance();
	ui::position pos = {31, 10};

	_menu = new ui::UIText({31, 6}, "MENU");
	_menu->setColor({255, 255, 255});
	_rect = new ui::UIRect({18, 3}, {30, 30});
	_rect->setBackgroundColor({255, 160, 134});
	_rect->setBorders(1, {255, 255, 255});
	_cursor = new ui::UIRect({37, 11}, {1, 1});
	_cursor->setBackgroundColor({0, 0, 0});

	for (size_t i = 0; i < engine.getGames().size(); i++) {
		_gameNames.push_back(new ui::UIText(pos,
			engine.getGames()[i]->name));
		_gameNames[_gameNames.size() - 1]->setColor({0, 0, 0});
		pos.y += 4;
	}
	_menuIsActive = true;
}


void Menu::tick(int e)
{
	auto arcade = arcade::Engine::instance();
	arcade::Engine::Graphic().clear();
	arcade::Engine::Graphic().drawRect(*_rect);
	arcade::Engine::Graphic().drawText(*_menu);
	for (auto &_gameName : _gameNames) {
		arcade::Engine::Graphic().drawText(*_gameName);
	}
	moveCursor(e);
	if (!_menuIsActive) {
		return;
	}
	arcade::Engine::Graphic().drawRect(*_cursor);
	arcade::Engine::Graphic().render();
}

void Menu::close()
{
	_menu = nullptr;
	_gameNames.clear();
	_rect = nullptr;
	_cursor = nullptr;
}

void Menu::moveCursor(int e)
{
	ui::position pos = _cursor->getPosition();
	if (e == arcade::event::W) {
		if (_cursor->getPosition().y > 14)
			_cursor->setPosition({pos.x, pos.y - 4});
	} else if (e == arcade::event::S) {
		if (_cursor->getPosition().y < 14)
			_cursor->setPosition({pos.x, pos.y + 4});
	} else if (e == arcade::event::L)
		detectCursorPos();
}

void Menu::detectCursorPos()
{
	if (_cursor->getPosition().y == 11) {
		_menuIsActive = false;
		arcade::Engine::instance().changeGame("nibbler");
	}
	else if (_cursor->getPosition().y == 15) {
		_menuIsActive = false;
		arcade::Engine::instance().changeGame("menu");
	}
}

Menu::~Menu()
{
}

extern "C" IGameApi *entryPoint()
{
	return new Menu;
}