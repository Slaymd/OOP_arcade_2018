/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "IApi.hpp"
#include "IElement.hpp"
#include "AElement.hpp"
#include "IGameApi.hpp"
#include "Engine.hpp"

class Nibbler : public IGameApi {

	public:
	Nibbler() = default;
	~Nibbler() = default;

	//functions
	void init() override;
	void tick() override;
	void close() override;

	private:
	ui::UIText *_name;
	ui::UIText *_input;
	ui::UIRect *_rect;
	arcade::Engine _engine;
};

#endif //ARCADE_NIBBLER_HPP
