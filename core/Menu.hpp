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
#include <tuple>

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
	void setCursorColorUp();
	void setCursorColorDown();

	typedef struct lib_s {
		ui::UIText *_name;
		ui::IApi *instanceLib;
		IGameApi *instanceGame;
		std::string _nameString;
		bool isGame;
	} lib_t;


	private:
	bool _menuIsActive;
	ui::UIText *_menu;
	std::vector<lib_t> _libs;
	int _cursor = 0;
	ui::UIRect *_rect;
};

#endif //ARCADE_MENU_HPP
