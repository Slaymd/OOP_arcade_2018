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
	~Menu();


	//functions
	void init() override;
	void tick(int) override;
	void close() override;

	void moveCursor(int e);
	void detectCursorPos();


	private:
	bool _menuIsActive;
	ui::UIText *_menu;
	std::vector<ui::UIText *> _gameNames;
	ui::UIRect *_cursor;
	std::string _nextGame;
	ui::UIRect *_rect;
};

#endif //ARCADE_MENU_HPP
