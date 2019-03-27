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
	ui::position pos = {31, 8};

	_menu = new ui::UIText({31, 4}, "MENU");
	_menu->setColor({255, 255, 255});
	_menu->setBackgroundColor({255, 160, 134});

	_textNcurses = new ui::UIText({31, 16}, "NCURSES");
	_textNcurses->setColor({0, 0, 0});
	_textNcurses->setBackgroundColor({255, 160, 134});

	_textSfml = new ui::UIText({31, 20}, "SFML");
	_textSfml->setColor({0, 0, 0});
	_textSfml->setBackgroundColor({255, 160, 134});

	_textQt = new ui::UIText({31, 24}, "QT");
	_textQt->setColor({0, 0, 0});
	_textQt->setBackgroundColor({255, 160, 134});


	_rect = new ui::UIRect({18, 3}, {30, 30});
	_rect->setBackgroundColor({255, 160, 134});
	_rect->setBorders(1, {255, 255, 255});

	for (size_t i = 0; i < engine.getGames().size(); i++) {
		_gameNames.push_back(new ui::UIText(pos,
			engine.getGames()[i]->name));
		_gameNames[_gameNames.size() - 1]->setColor({0, 0, 0});
		_gameNames[_gameNames.size() - 1]->setBackgroundColor({255, 160, 134});

		pos.y += 4;
	}
	_gameNames[0]->setColor({255, 255, 0});

	_menuIsActive = true;
}


void Menu::tick(int e)
{
	arcade::Engine::Graphic().clean();
	arcade::Engine::Graphic().drawRect(*_rect);
	arcade::Engine::Graphic().drawText(*_menu);
	arcade::Engine::Graphic().drawText(*_textNcurses);
	arcade::Engine::Graphic().drawText(*_textQt);
	arcade::Engine::Graphic().drawText(*_textSfml);

	for (auto &_gameName : _gameNames) {
		arcade::Engine::Graphic().drawText(*_gameName);
	}
	moveCursor(e);
	if (!_menuIsActive) {
		return;
	}
//	arcade::Engine::Graphic().drawRect(*_cursor);
	arcade::Engine::Graphic().render();
}

void Menu::close()
{
//	_menu = nullptr;
	_gameNames.clear();
//	_rect = nullptr;
	_cursor = 9;
}

void Menu::moveCursor(int e)
{
	if (e == arcade::event::Z && _cursor >= 13) {
		switch (_cursor) {
			case 13 :
				setCursorColorTop(1);
				break;
			case 17 :
				setCursorColorTop(8);
				break;
			case 21 :
				setCursorColorTop(9);
				break;
			case 25 :
				setCursorColorTop(10);
				break;
			default:
				break;
		}
		_cursor -= 4;
	} else if (e == arcade::event::S && _cursor <= 21) {
		switch (_cursor) {
		case 9 :
			setCursorColorDown(0);
			break;
		case 13 :
			setCursorColorDown(1);
			break;
		case 17 :
			setCursorColorDown(8);
			break;
		case 21 :
			setCursorColorDown(9);
			break;
		default:
			break;
		}
		_cursor += 4;
	}
	else if (e == arcade::event::L)
		detectCursorPos();
}

void Menu::detectCursorPos()
{
	if (_cursor == 9) {
		close();
		_menuIsActive = false;
		arcade::Engine::instance().changeGame("nibbler");
	} else if (_cursor == 13) {
		_menuIsActive = false;
		close();
		arcade::Engine::instance().changeGame("menu");
	} else if (_cursor == 17) {
			arcade::Engine::instance().changeLib("ncurses");
	}
}

void Menu::setCursorColorTop(int index)
{
	if (index == 1) {
		_gameNames[1]->setColor({0, 0, 0});
		_gameNames[0]->setColor({255, 255, 0});
	} else if (index == 8) {
		_textNcurses->setColor({0, 0, 0});
		_gameNames[1]->setColor({255, 255, 0});
	} else if (index == 9) {
		_textSfml->setColor({0, 0, 0});
		_textNcurses->setColor({255, 255, 0});
	} else if (index == 10) {
		_textQt->setColor({0, 0, 0});
		_textSfml->setColor({255, 255, 0});
	}
}

void Menu::setCursorColorDown(int index)
{
	if (index == 0) {
		_gameNames[0]->setColor({0, 0, 0});
		_gameNames[1]->setColor({255, 255, 0});
	} else if (index == 1) {
		_gameNames[1]->setColor({0, 0, 0});
		_textNcurses->setColor({255, 255, 0});
	} else if (index == 8) {
		_textNcurses->setColor({0, 0, 0});
		_textSfml->setColor({255, 255, 0});
	} else if (index == 9) {
		_textSfml->setColor({0, 0, 0});
		_textQt->setColor({255, 255, 0});
	}
}

extern "C" IGameApi *entryPoint()
{
	return new Menu;
}
