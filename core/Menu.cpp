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
	ui::position pos = {31, 9};
	lib_t lib;

	_menu = new ui::UIText({31, 5}, "MENU");
	_menu->setColor({255, 255, 255});
	_menu->setBackgroundColor({255, 160, 134});

	_rect = new ui::UIRect({18, 3}, {30, 30});
	_rect->setBackgroundColor({255, 160, 134});
	_rect->setBorders(1, {255, 255, 255});

	for (size_t i = 0; i < engine.getGames().size(); i++) {
		lib._name = new ui::UIText(pos, engine.getGames()[i].name);
		lib.instanceGame = arcade::Engine::instance().getGames()[i].instance;
		lib.isGame = true;
		lib._nameString = engine.getGames()[i].name;
		std::cout << i << lib._nameString << std::endl;
		_libs.push_back(lib);
		_libs[_libs.size() - 1]._name->setColor({0, 0, 0});
		_libs[_libs.size() - 1]._name->setBackgroundColor({255, 160, 134});
		pos.y += 4;
	}
	for (size_t i = 0; i < engine.getGraphLibs().size(); i++) {
		lib._name = new ui::UIText(pos, engine.getGraphLibs()[i].name);
		lib.instanceLib = arcade::Engine::instance().getGraphLibs()[i].instance;
		lib.isGame = false;
		lib._nameString = engine.getGraphLibs()[i].name;
		std::cout << i << lib._nameString << std::endl;
		_libs.push_back(lib);
		_libs[_libs.size() - 1]._name->setColor({0, 0, 0});
		_libs[_libs.size() - 1]._name->setBackgroundColor({255, 160, 134});
		pos.y += 4;
	}
	
	_libs[0]._name->setColor({255, 255, 0});

	_menuIsActive = true;
}


void Menu::tick(int e)
{
	arcade::Engine::Graphic().clean();
	ui::UIText text({0, 0}, "bonjour");

	arcade::Engine::Graphic().drawText(text);


	arcade::Engine::Graphic().drawRect(*_rect);
	arcade::Engine::Graphic().drawText(*_menu);
	for (auto &_gameName : _libs)
		arcade::Engine::Graphic().drawText(*_gameName._name);
	arcade::Engine::Graphic().render();
	moveCursor(e);
}

void Menu::close()
{
//	_menu = nullptr;
//	_libs.clear();
//	_rect = nullptr;
	_cursor = 0;
}

void Menu::moveCursor(int e)
{
	if (e == arcade::event::Z && _cursor > 0)
		setCursorColorUp();
	else if (e == arcade::event::S && _cursor + 1 < (int) _libs.size())
		setCursorColorDown();
	else if (e == arcade::event::Key::ENTER)
		detectCursorPos();
}

void Menu::detectCursorPos()
{
	_menuIsActive = false;
	if (_libs[_cursor].isGame) {
		std::cout << "$ changeGame()" << std::endl;
		arcade::Engine::instance().changeGame(_libs[_cursor]._nameString);
//		close();
	} else {

		std::cout << "$ changeGraphLib()" << std::endl;
		arcade::Engine::instance().changeGraphLib(_libs[_cursor]._nameString);
//		close();
	}

}

void Menu::setCursorColorUp()
{
	arcade::Engine::Graphic().playSound("assets/mc_hit.wav");
	_libs[_cursor - 1]._name->setColor({255, 255, 0});
	_libs[_cursor]._name->setColor({0, 0, 0});
	_cursor -= 1;
}

void Menu::setCursorColorDown()
{
	arcade::Engine::Graphic().playSound("assets/mc_hit.wav");
	_libs[_cursor + 1]._name->setColor({255, 255, 0});
	_libs[_cursor]._name->setColor({0, 0, 0});
	_cursor += 1;
}

extern "C" IGameApi *entryPoint()
{
	return new Menu;
}
