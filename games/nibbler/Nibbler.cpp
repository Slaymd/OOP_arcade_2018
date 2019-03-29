/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include <chrono>
#include <random>
#include <ctime>
#include <thread>
#include <sstream>
#include "Nibbler.hpp"

void Nibbler::init()
{
	_name = new ui::UIText({30, 0}, "NIBBLER");
	_name->setColor({255, 255, 255});

	_scoreText = new ui::UIText({3, 0}, "SCORE : ");
	_scoreText->setColor({255, 255, 255});

	_score = new ui::UIText({9, 0}, "0");
	_score->setColor({255, 255, 255});

	_snakePos = {{31, 17}, {31, 18}, {31, 19}};

	_head = new ui::UIRect({31, 16}, {1, 1});
	_head->setBackgroundColor({124, 252, 0});

	_snake = new ui::UIRect(_snakePos[0], {1, 1});
	_snake->setBackgroundColor({107, 142, 35});

	_food = new ui::UIRect({0, 0}, {1, 1});
	_food->setBackgroundColor({255, 0, 0});

	ui::UIRect bgRect({20, 20}, {1, 1});
	bgRect.setBackgroundColor({255, 145, 0});

	_frame = new ui::Frame();
	_frame->setElement(1, bgRect);
	for (int i = 0; i < 10; i++) {
		_frame->setPixel({20 -1, 20 + i}, 1);
		_frame->setPixel({20, 20 + i}, 1);
		_frame->setPixel({20 + 1, 20 + i}, 1);
	}

	_head->setBackgroundImage("assets/viatransit_180x180.png");

	srand(time(nullptr));
	_food->setPosition({(int)rand() % 60, (int)rand() % 60});
}

void Nibbler::tick(int event)
{
	arcade::Engine::Graphic().clean();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	arcade::Engine::Graphic().drawFrame(*_frame);
	arcade::Engine::Graphic().drawText(*_name);
	arcade::Engine::Graphic().drawText(*_scoreText);
	handleScore();
	generateFood();
	moveSnake(event);
	displaySnake();
	arcade::Engine::Graphic().drawText(*_score);
	arcade::Engine::Graphic().drawRect(*_food);
	arcade::Engine::Graphic().render();
}

void Nibbler::moveSnake(int e)
{
	if (e == arcade::event::Q && _direction == 1)
		_direction = 4;
	else if (e == arcade::event::Q && _direction == 4)
		_direction = 3;
	else if (e == arcade::event::Q && _direction == 3)
		_direction = 2;
	else if (e == arcade::event::Q && _direction == 2)
		_direction = 1;
	else if (e == arcade::event::D && _direction == 1)
		_direction = 2;
	else if (e == arcade::event::D && _direction == 2)
		_direction = 3;
	else if (e == arcade::event::D && _direction == 3)
		_direction = 4;
	else if (e == arcade::event::D && _direction == 4)
		_direction = 1;
	checkDeath();
	autoMove();


}

void Nibbler::autoMove()
{
	switch (_direction) {
	//droite
	case 1:
		moveBody();
		_head->setPosition({_head->getPosition().x + 1, _head->getPosition().y});
		break;
	//bas
	case 2:
		moveBody();
		_head->setPosition({_head->getPosition().x, _head->getPosition().y + 1});
		break;
	//gauche
	case 3:
		moveBody();
		_head->setPosition({_head->getPosition().x - 1, _head->getPosition().y});
		break;

	//haut
	case 4:
		moveBody();
		_head->setPosition({_head->getPosition().x, _head->getPosition().y - 1});
		break;

	}
}

void Nibbler::close()
{
	//TODO: free that
	delete _frame;
	delete _name;
	delete _score;
	delete _scoreText;
	delete _snake;
	_snakePos.clear();
	delete _head;
	delete _food;
	_scoreInt = 0;
	_direction = 1;
}

void Nibbler::generateFood()
{
	if (_head->getPosition().x == _food->getPosition().x && _head->getPosition().y == _food->getPosition().y) {
		arcade::Engine::Graphic().playSound("assets/mc_eat.wav");
		_food->setPosition({(int)random() % 60, (int)random() % 60});
		_snakePos.push_back({_snakePos[_snakePos.size() - 1]});
		_scoreInt += 1;
	}
}

void Nibbler::displaySnake()
{
	ui::position tmp = _snake->getPosition();

	arcade::Engine::Graphic().drawRect(*_head);
	for (auto _snakePo : _snakePos) {
		_snake->setPosition(_snakePo);
		arcade::Engine::Graphic().drawRect(*_snake);
	}
	_snake->setPosition(tmp);
}

void Nibbler::checkDeath()
{
	if (_head->getPosition().x < 0 || _head->getPosition().x > 60 || _head->getPosition().y < 0 || _head->getPosition().y > 60) {
		close();
		init();
	}

	for (auto _snakePo : _snakePos)
		if (_head->getPosition().x == _snakePo.x && _head->getPosition().y == _snakePo.y) {
			close();
			init();
		}
}

void Nibbler::moveBody()
{
	for (size_t i = _snakePos.size(); i > 0 ; i--) {
		_snakePos[i] = _snakePos[i - 1];
	}
	_snakePos[0] = _head->getPosition();
}

void Nibbler::handleScore()
{
	_score->setString(std::to_string(_scoreInt));
}

extern "C" IGameApi *entryPoint()
{
	return new Nibbler();
}
