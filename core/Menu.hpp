/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_MENU_HPP
#define ARCADE_MENU_HPP

#include "IGameApi.hpp"
#include "Engine.hpp"
#include "UIRect.hpp"
#include "UIText.hpp"
#include <thread>
#include <vector>

class Menu : public IGameApi {

	public:

	/* BASE FUNCTIONS */

	void init() override;
	void tick(int i) override;
	void close() override;
	void restart() override;

	private:

	/* DISPLAY */

	void generateBackground();
	void dispUserTab();
	void dispGamesTab();
	void dispGraphicsTab();
	void dispHighscoresSection();

	/* ACTIONS */

	void eventHandler(arcade::event::Key);
	void selectsEventHandler(arcade::event::Key);

	/* UTILS */

	int randomBetween(int a, int b);

	/* VARS */
	ui::UIRect *_header = nullptr;
	ui::UIRect *_bg = nullptr;
	std::vector<ui::UIText> *_particles = nullptr;
	ui::UIText *_headerText = nullptr;
	ui::color _bgColor = {0, 0, 0};

	//Player tab
	ui::UIRect *_playerTab = nullptr;
	ui::UIText *_usernameText = nullptr;
	ui::UIText *_usernameField = nullptr;
	bool _usernameFieldError = false;

	//Games tab
	ui::UIRect *_gamesTab = nullptr;
	int _gameIndex = 0;

	//Graphic tab
	ui::UIRect *_graphicsTab = nullptr;
	int _graphicIndex = 0;

	//Highscores section
	ui::UIText *_highscoresText = nullptr;

	int _welcomeTicks = 25;

	int _tabIndex = 0;

	std::vector<ui::color> *_darkColors = nullptr;
	std::vector<ui::color> *_lightColors = nullptr;
};

#endif //ARCADE_MENU_HPP
