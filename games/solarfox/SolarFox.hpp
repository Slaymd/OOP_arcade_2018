/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_SOLARFOX_HPP
#define ARCADE_SOLARFOX_HPP

#include "IApi.hpp"
#include "IElement.hpp"
#include "AElement.hpp"
#include "IGameApi.hpp"
#include "Engine.hpp"

class SolarFox : public IGameApi {

	public:
	SolarFox() = default;
	~SolarFox() = default;

	//functions
	void init() override;
	void tick(int) override;
	void close() override;
	void handleShot();
	void autoMove();
	void moveShip(int e);
	void generateFood();
	void handleScore();
	void checkDeath();


	private:
	ui::Frame *_frame;
	ui::UIRect *_ship;
	ui::UIRect *_wings;
	ui::UIRect *_area;
	ui::UIRect *_shot;
//	std::vector<ui::UIRect *> _foods;
	ui::UIText *_name;
	ui::UIText *_scoreText;
	ui::UIText *_score;
	int _scoreInt = 0;
	int _shotRange = 0;
	int _direction = 2;
	arcade::Engine _engine;
};

#endif //ARCADE_SOLARFOX_HPP
