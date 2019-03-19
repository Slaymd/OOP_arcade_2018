/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "../../lib/IApi.hpp"
#include "../../lib/IElement.hpp"
#include "../../lib/AElement.hpp"
#include "../../lib/SFMLApi.hpp"
#include "../IGameApi.hpp"
#include "../../core/Engine.hpp"
#include "../../lib/UIRect.hpp"

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
};

#endif //ARCADE_NIBBLER_HPP
