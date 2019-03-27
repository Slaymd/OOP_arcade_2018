/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "IApi.hpp"
#include "IElement.hpp"
#include "AElement.hpp"
#include "IGameApi.hpp"
#include "Engine.hpp"

class Menu : public IGameApi {

	public:
	Menu() = default;
	~Menu() = default;


	//functions
	void init() override;
	void tick(int) override;
	void close() override;

	void moveCursor(int e);
	void detectCursorPos();
	void chooseLib(int e);
	void setCursorColorTop(int);
	void setCursorColorDown(int);



	private:
	bool _menuIsActive;
	ui::UIText *_menu;
	ui::UIText *_textNcurses;
	ui::UIText *_textSfml;
	ui::UIText *_textQt;

	std::vector<ui::UIText *> _gameNames;

	arcade::Engine _engine;
	int _cursor = 9;
	std::string _nextGame;
	ui::UIRect *_rect;
};

#endif //ARCADE_MENU_HPP
