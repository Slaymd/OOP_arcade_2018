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
#include "SolarFox.hpp"

void SolarFox::init()
{
	_name = new ui::UIText({30, 0}, "SOLARFOX");
	_name->setColor({255, 255, 255});

	_scoreText = new ui::UIText({3, 0}, "SCORE : ");
	_scoreText->setColor({255, 255, 255});

	_score = new ui::UIText({9, 0}, "0");
	_score->setColor({255, 255, 255});

	_ship = new ui::UIRect({30, 30}, {1, 3});
	_ship->setBackgroundColor({124, 252, 0});

	//{29, 32}
	_wings = new ui::UIRect({_ship->getPosition().x - 1, _ship->getPosition().y + 2}, {3, 1});
	_wings->setBackgroundColor({124, 252, 128});

	_area = new ui::UIRect({10, 10}, {40, 40});
	_area->setBackgroundColor({155, 155, 155});
	_area->setBorders(7, {255, 255, 255});

	_shot = new ui::UIRect(_ship->getPosition(), {1, 1});
	_shot->setBackgroundColor({255, 255, 255});
}

void SolarFox::tick(int e)
{
	arcade::Engine::Graphic().clean();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	arcade::Engine::Graphic().drawRect(*_area);
	arcade::Engine::Graphic().drawText(*_name);
	arcade::Engine::Graphic().drawText(*_scoreText);
	arcade::Engine::Graphic().drawText(*_score);
	moveShip(e);
	handleShot();
	arcade::Engine::Graphic().drawRect(*_ship);
	arcade::Engine::Graphic().drawRect(*_wings);
	arcade::Engine::Graphic().drawRect(*_shot);
	arcade::Engine::Graphic().render();
}

void SolarFox::moveShip(int e)
{
	switch (e) {
	case arcade::event::D :
		_direction = 1;
		break;
	case arcade::event::Z :
		_direction = 2;
		break;
	case arcade::event::Q :
		_direction = 3;
		break;
	case arcade::event::S :
		_direction = 4;
		break;
	default:
		autoMove();
	}
}

//1 == droite
//2 == haut
//3 == gauche
//4 == bas
void SolarFox::autoMove()
{
	switch (_direction) {
	case 1:
		_ship->setPosition({_ship->getPosition().x + 1, _ship->getPosition().y});
		_wings->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y + 2});
		break;
	case 2 :
		_ship->setPosition({_ship->getPosition().x, _ship->getPosition().y + 1});
		_wings->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y + 2});
		break;
	case 3 :
		_ship->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y});
		_wings->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y + 2});
		break;
	case 4:
		_ship->setPosition({_ship->getPosition().x, _ship->getPosition().y - 1});
		_wings->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y + 2});
	default:
		break;
	}
}

void SolarFox::close()
{
}

void SolarFox::generateFood()
{
}


void SolarFox::checkDeath()
{

}

void SolarFox::handleScore()
{
	_score->setString(std::to_string(_scoreInt));
}

void SolarFox::handleShot()
{
	if (_shotRange > 2) {
		_shotRange = 0;
		_shot->setPosition(_ship->getPosition());
	}
	switch (_direction) {
	case 1 :
		_shotRange += 1;
		_shot->setPosition({_shot->getPosition().x + 1, _shot->getPosition().y});
		break;
	case 2 :
		_shotRange += 1;
		_shot->setPosition({_shot->getPosition().x, _shot->getPosition().y - 1});
		break;
	case 3 :
		_shotRange += 1;
		_shot->setPosition({_shot->getPosition().x - 1, _shot->getPosition().y});
		break;
	case 4 :
		_shotRange += 1;
		_shot->setPosition({_shot->getPosition().x, _shot->getPosition().y + 1});
		break;
	default:
		break;
	}
}

extern "C" IGameApi *entryPoint()
{
	return new SolarFox();
}
