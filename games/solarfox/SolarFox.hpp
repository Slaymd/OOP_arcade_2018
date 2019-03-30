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
	void handleEnnemyShot();
	void handleFood();
	void handleScore();
	void handleCollisionLeft();
	void handleCollisionRight();
	void handleCollisionUp();
	void handleCollisionDown();
	void handleCollision();
	void drawShip();
	void moveEnemy();
	void handleWin();
	void handleLose();


	private:
	std::vector<ui::position> _shipRight;
	std::vector<ui::position> _shipLeft;
	std::vector<ui::position> _shipUp;
	std::vector<ui::position> _shipDown;
	ui::UIRect *_ship;

	ui::position _canon;
	ui::UIRect *_area;
	ui::UIRect *_endGame;
	ui::UIRect *_shot;

	std::vector<ui::UIRect> _enemyRight;
	std::vector<ui::UIRect> _enemyLeft;
	std::vector<ui::UIRect> _enemyUp;
	std::vector<ui::UIRect> _enemyDown;
	std::vector<ui::position> _enemyRightShot;
	std::vector<ui::position> _enemyLeftShot;
	std::vector<ui::position> _enemyUpShot;
	std::vector<ui::position> _enemyDownShot;

	std::vector<ui::UIRect> _foods;
	ui::UIText *_name;
	ui::UIText *_scoreText;
	ui::UIText *_score;
	ui::UIText *_winLose;
	int _scoreInt = 0;
	int _moveRight = 1;
	int _moveLeft = -1;
	int _moveUp = -1;
	int _moveDown = 1;
	bool _isActive;

	int _shotRange = 0;
	int _direction;

	int _lastDirection = 2;
};

#endif //ARCADE_SOLARFOX_HPP
