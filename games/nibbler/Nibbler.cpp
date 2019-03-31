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

	_winLose = new ui::UIText({27, 29}, "Game Over");
	_winLose->setColor({255, 255, 255});

	_endgame = new ui::UIRect({15, 15}, {30, 30});
	_endgame->setBackgroundColor({10, 10, 10});

	_isActive = true;

	_scoreInt = 0;
	_direction = 1;

	_snakePos = {{31, 29}, {31, 30}, {31, 31}};

	_head = new ui::UIRect({31, 28}, {1, 1});
	_head->setBackgroundColor({124, 252, 0});

	_snake = new ui::UIRect(_snakePos[0], {1, 1});
	_snake->setBackgroundColor({107, 142, 35});

	_food = new ui::UIRect({0, 0}, {1, 1});
	_food->setBackgroundColor({255, 0, 0});

	ui::UIRect bgRect({20, 20}, {1, 1});
	bgRect.setBackgroundColor({255, 145, 0});

	srand(time(nullptr));
	_food->setPosition({(int)rand() % 59, (int)rand() % 59});
}

void Nibbler::tick(int event)
{
	arcade::Engine::Graphic().clean();
	if (_isActive) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		arcade::Engine::Graphic().drawText(*_name);
		arcade::Engine::Graphic().drawText(*_scoreText);
		handleScore();
		generateFood();
		moveSnake(event);
		displaySnake();
		arcade::Engine::Graphic().drawText(*_score);
		arcade::Engine::Graphic().drawRect(*_food);
	} else {
		arcade::Engine::Graphic().drawRect(*_endgame);
		arcade::Engine::Graphic().drawText(*_score);
		arcade::Engine::Graphic().drawText(*_scoreText);
		arcade::Engine::Graphic().drawText(*_winLose);
		if (event == arcade::event::ENTER) {
			close();
			init();
		}
	}
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
	autoMove();
	checkDeath();


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
	delete _name;
	delete _score;
	delete _scoreText;
	delete _snake;
	_snakePos.clear();
	delete _head;
	delete _food;
	_scoreInt = 0;
	_direction = 1;
	_isActive = false;
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
	if (_head->getPosition().x < 0 || _head->getPosition().x >= 60 || _head->getPosition().y < 0 || _head->getPosition().y >= 60) {
		arcade::Engine::instance().addScore(_scoreInt);
		_isActive = false;
	}

	for (auto _snakePo : _snakePos)
		if (_head->getPosition().x == _snakePo.x && _head->getPosition().y == _snakePo.y) {
			arcade::Engine::instance().addScore(_scoreInt);
			_isActive = false;
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

void Nibbler::restart()
{
	close();
	init();
}

extern "C" IGameApi *entryPointGame()
{
	return new Nibbler();
}
