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
	void tick() override;
	void close() override;

	private:
	ui::UIText *_menu;
	ui::UIText *_option;
	std::vector<ui::UIText *> _gameName;
	arcade::Engine _engine;
};

#endif //ARCADE_MENU_HPP
