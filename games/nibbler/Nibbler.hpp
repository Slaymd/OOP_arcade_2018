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
	void tick(int) override;
	void close() override;
	void autoMove();
	void generateFood();
	void moveBody();
	void displaySnake();
	void moveSnake(int e);
	void handleScore();
	void checkDeath();


	private:
	ui::UIText *_name;
	ui::UIText *_scoreText;
	ui::UIText *_winLose;
	ui::UIRect *_snake;
	std::vector<ui::position> _snakePos;
	ui::UIRect *_head;
	ui::UIRect *_food;
	ui::UIText *_score;
	ui::UIRect *_endgame;
	int _scoreInt = 0;
	bool _isActive;
	int _direction = 1;
};

#endif //ARCADE_NIBBLER_HPP
