/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include <chrono>
#include <thread>
#include "Nibbler.hpp"

void Nibbler::init()
{
	_name = new ui::UIText({30, 0}, "NIBBLER");
	_name->setColor({255, 255, 255});

	_snakePos = {{31, 17}, {31, 18}, {31, 19}};

	_head = new ui::UIRect({31, 16}, {1, 1});
	_head->setBackgroundColor({124, 252, 0});
//	_head->setBorders(1, {107, 142, 35});

	_snake = new ui::UIRect(_snakePos[0], {1, 1});
	_snake->setBackgroundColor({107, 142, 35});

	_food = new ui::UIRect({0, 0}, {1, 1});
	_food->setBackgroundColor({255, 0, 0});
	_food->setPosition({(int)random() % 30, (int)random() % 30});
}

void Nibbler::tick(int event)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
	arcade::Engine::Graphic().clear();

	arcade::Engine::Graphic().drawText(*_name);
	generateFood();
	moveSnake(event);
	displaySnake();
	arcade::Engine::Graphic().drawRect(*_food);
	arcade::Engine::Graphic().render();
}

void Nibbler::moveSnake(int e)
{
	if (e == arcade::event::D && _direction != 3)
		_direction = 1;
	if (e == arcade::event::W && _direction != 2)
		_direction = 4;
	if (e == arcade::event::A && _direction != 1)
		_direction = 3;
	if (e == arcade::event::S && _direction != 4)
		_direction = 2;
	autoMove();


}

void Nibbler::close()
{
	//TODO close ce qui a était open
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

void Nibbler::generateFood()
{
	if ((_head->getPosition().x == _food->getPosition().x && _head->getPosition().y == _food->getPosition().y) || (_head->getPosition().x - 1  == _food->getPosition().x && _head->getPosition().y - 1 == _food->getPosition().y) || (_head->getPosition().x   == _food->getPosition().x && _head->getPosition().y - 1 == _food->getPosition().y) ||
(_head->getPosition().x - 1  == _food->getPosition().x && _head->getPosition().y == _food->getPosition().y)) {
		_food->setPosition({(int)random() % 30, (int)random() % 30});
		_snakePos.push_back({_snakePos[_snakePos.size() - 1]});
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

void Nibbler::moveBody()
{
	for (size_t i = _snakePos.size(); i > 0 ; i--) {
		_snakePos[i] = _snakePos[i - 1];
	}
	_snakePos[0] = _head->getPosition();
}

extern "C" IGameApi *entryPoint()
{
	return new Nibbler();
}
