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

	ui::position tmpFood = {static_cast<int>(random()) % 50 + 10, static_cast<int>(random()) % 50 + 10};
	//Init text
	_name = new ui::UIText({30, 0}, "SOLARFOX");
	_name->setColor({155, 155, 155});

	_winLose = new ui::UIText({27, 29}, "Press Enter");
	_winLose->setColor({255, 255, 255});

	_endGame = new ui::UIRect({15, 15}, {30, 30});
	_endGame->setBackgroundColor({10, 10, 10});

	_scoreText = new ui::UIText({3, 0}, "SCORE : ");
	_scoreText->setColor({155, 155, 155});


	_score = new ui::UIText({9, 0}, "0");
	_score->setColor({155, 155, 155});

	_direction = 2; //haut
	_isActive = true;

	//set rect
	_ship = new ui::UIRect({30, 30}, {1, 1});
	_ship->setBackgroundColor({124, 252, 5});
	_canon = {30, 32};
	_shipUp = {{0, 0}, {0, -1}, {0, -2}, {-1, 0}, {1, 0}, {-1, 1}, {-1, 2}, {1, 1}, {1, 2}};
	_shipRight = {{0, 0}, {1, 0}, {2, 0}, {0, -1}, {0, 1}, {-1, 1}, {-2, 1}, {-1, -1}, {-2, -1}};
	_shipLeft = {{0, 0}, {-1, 0}, {-2, 0}, {0, -1}, {0, 1}, {1, -1}, {2, -1}, {1, 1}, {2, 1}};
	_shipDown = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, 2}, {-1, -1}, {-1, -2}, {1, -1}, {1, -2}};

	_enemyLeft.push_back(ui::UIRect({1, 30}, {1, 3}));
	_enemyLeft.push_back(ui::UIRect({2, 31}, {1, 1}));

	_enemyRight.push_back(ui::UIRect({58, 30}, {1, 3}));
	_enemyRight.push_back(ui::UIRect({57, 31}, {1, 1}));

	_enemyUp.push_back(ui::UIRect({30, 1}, {3, 1}));
	_enemyUp.push_back(ui::UIRect({31, 2}, {1, 1}));

	_enemyDown.push_back(ui::UIRect({30, 58}, {3, 1}));
	_enemyDown.push_back(ui::UIRect({31, 57}, {1, 1}));

	for (int i = 0; i < 20; i++) {
		ui::UIRect food = ui::UIRect(tmpFood, {1, 1});
		food.setBackgroundColor({120, 56, 31});
		_foods.push_back(food);
		tmpFood = {static_cast<int>(random()) % 35 + 6, static_cast<int>(random()) % 35 + 6};
	}
	//set ennemy color
	_enemyLeft[0].setBackgroundColor({220, 20, 60});
	_enemyLeft[1].setBackgroundColor({220, 20, 60});
	_enemyRight[0].setBackgroundColor({220, 20, 60});
	_enemyRight[1].setBackgroundColor({220, 20, 60});
	_enemyUp[0].setBackgroundColor({220, 20, 60});
	_enemyUp[1].setBackgroundColor({220, 20, 60});
	_enemyDown[0].setBackgroundColor({220, 20, 60});
	_enemyDown[1].setBackgroundColor({220, 20, 60});


	_area = new ui::UIRect({2, 2}, {56, 56});
	_area->setBackgroundColor({155, 155, 155});
	_area->setBorders(2, {255, 255, 255});

	_shot = new ui::UIRect(_canon, {1, 1});
	_shot->setBackgroundColor({255, 255, 255});

	_isActive = true;
}

void SolarFox::tick(int e)
{
	arcade::Engine::Graphic().clean();
	if (_isActive) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		arcade::Engine::Graphic().drawRect(*_area);
		arcade::Engine::Graphic().drawText(*_name);
		handleScore();
		handleCollision();
		arcade::Engine::Graphic().drawText(*_scoreText);
		arcade::Engine::Graphic().drawText(*_score);
		handleFood();
		moveShip(e);
		moveEnemy();
		handleEnnemyShot();
		drawShip();
		handleShot();
		arcade::Engine::Graphic().drawRect(*_shot);
		handleWin();
	} else {
		arcade::Engine::Graphic().drawRect(*_endGame);
		arcade::Engine::Graphic().drawText(*_winLose);
		arcade::Engine::Graphic().drawText(*_scoreText);
		arcade::Engine::Graphic().drawText(*_score);
		if (e == arcade::event::ENTER) {
			_isActive = true;
			close();
			init();
		}
	}
	arcade::Engine::Graphic().render();
}

//1 == droite
//2 == haut
//3 == gauche
//4 == bas
void SolarFox::handleCollision()
{
	if (_canon.x >= 56 || _canon.y >= 56 || _canon.x <= 3 || _canon.y <= 3)
		handleLose();
	switch (_direction) {
	case 1 :
		handleCollisionRight();
		break;
	case 2 :
		handleCollisionUp();
		break;
	case 3 :
		handleCollisionLeft();
		break;
	case 4 :
		handleCollisionDown();
		break;
	default:
		break;
	}
}


void SolarFox::handleFood()
{
	for (auto &_food : _foods) {
		if ((_food.getPosition().x == _shot->getPosition().x && _food.getPosition().y == _shot->getPosition().y) || (_food.getPosition().x == _canon.x && _food.getPosition().y == _canon.y)) {
			_food.setPosition({-1, -1});
			_scoreInt += 1;
		}
	}
	for (const auto &_food : _foods) {
		arcade::Engine::Graphic().drawRect(_food);
	}
}


void SolarFox::handleEnnemyShot()
{
	//FAIRE UN VRAI RAND
	if ((_enemyLeftShot.empty() || _enemyLeftShot[_enemyLeftShot.size() - 1].x > random() % 2000))
		_enemyLeftShot.push_back({_enemyLeft[1].getPosition().x + 1, _enemyLeft[1].getPosition().y});
	for (int i = 0; i < (int)_enemyLeftShot.size(); i++) {
		_enemyLeftShot[i].x += 1;
		ui::position tmp = _shot->getPosition();
		_shot->setPosition(_enemyLeftShot[i]);
		arcade::Engine::Graphic().drawRect(*_shot);
		_shot->setPosition(tmp);
		if (_enemyLeftShot[i].x > 56)
			_enemyLeftShot.erase(_enemyLeftShot.begin() + i);
	}

	if ((_enemyRightShot.empty() || _enemyRightShot[_enemyRightShot.size() - 1].x > random() % 2000))
		_enemyRightShot.push_back({_enemyRight[1].getPosition().x - 1, _enemyRight[1].getPosition().y});
	for (int i = 0; i < (int)_enemyRightShot.size(); i++) {
		_enemyRightShot[i].x -= 1;
		ui::position tmp = _shot->getPosition();
		_shot->setPosition(_enemyRightShot[i]);
		arcade::Engine::Graphic().drawRect(*_shot);
		_shot->setPosition(tmp);
		if (_enemyRightShot[i].x < 2)
			_enemyRightShot.erase(_enemyRightShot.begin() + i);
	}
	if ((_enemyUpShot.empty() || _enemyUpShot[_enemyUpShot.size() - 1].y > random() % 2000))
		_enemyUpShot.push_back({_enemyUp[1].getPosition().x, _enemyUp[1].getPosition().y + 1});
	for (int i = 0; i < (int)_enemyUpShot.size(); i++) {
		_enemyUpShot[i].y += 1;
		ui::position tmp = _shot->getPosition();
		_shot->setPosition(_enemyUpShot[i]);
		arcade::Engine::Graphic().drawRect(*_shot);
		_shot->setPosition(tmp);
		if (_enemyUpShot[i].y > 56)
			_enemyUpShot.erase(_enemyUpShot.begin() + i);
	}

	if ((_enemyDownShot.empty() || _enemyDownShot[_enemyDownShot.size() - 1].y > random() % 2000))
		_enemyDownShot.push_back({_enemyDown[1].getPosition().x, _enemyDown[1].getPosition().y - 1});
	for (int i = 0; i < (int)_enemyDownShot.size(); i++) {
		_enemyDownShot[i].y -= 1;
		ui::position tmp = _shot->getPosition();
		_shot->setPosition(_enemyDownShot[i]);
		arcade::Engine::Graphic().drawRect(*_shot);
		_shot->setPosition(tmp);
		if (_enemyDownShot[i].y < 2)
			_enemyDownShot.erase(_enemyDownShot.begin() + i);
	}
}

void SolarFox::moveShip(int e)
{
	switch (e) {
	case arcade::event::D :
		_lastDirection = _direction;
		_direction = 1;
		break;
	case arcade::event::Z :
		_lastDirection = _direction;
		_direction = 2;
		break;
	case arcade::event::Q :
		_lastDirection = _direction;
		_direction = 3;
		break;
	case arcade::event::S :
		_lastDirection = _direction;
		_direction = 4;
		break;
	}
	_lastDirection == 1 && _direction == 3 ? _direction = 1 : 0;
	_lastDirection == 2 && _direction == 4 ? _direction = 2 : 0;
	_lastDirection == 3 && _direction == 1 ? _direction = 3 : 0;
	_lastDirection == 4 && _direction == 2 ? _direction = 4 : 0;
	autoMove();
}

void SolarFox::drawShip()
{
	arcade::Engine::Graphic().drawRect(_enemyLeft[0]);
	arcade::Engine::Graphic().drawRect(_enemyLeft[1]);
	arcade::Engine::Graphic().drawRect(_enemyRight[0]);
	arcade::Engine::Graphic().drawRect(_enemyRight[1]);
	arcade::Engine::Graphic().drawRect(_enemyUp[0]);
	arcade::Engine::Graphic().drawRect(_enemyUp[1]);
	arcade::Engine::Graphic().drawRect(_enemyDown[0]);
	arcade::Engine::Graphic().drawRect(_enemyDown[1]);
}

void SolarFox::moveEnemy()
{

	_enemyLeft[0].getPosition().y <= 10 && _moveLeft == -1 ? _moveLeft = 1 : 0;
	_enemyLeft[0].getPosition().y >= 48 && _moveLeft == 1 ? _moveLeft = -1 : 0;
	_enemyLeft[0].setPosition({_enemyLeft[0].getPosition().x, _enemyLeft[0].getPosition().y + (1 * _moveLeft)});
	_enemyLeft[1].setPosition({_enemyLeft[1].getPosition().x, _enemyLeft[1].getPosition().y + (1 * _moveLeft)});

	_enemyRight[0].getPosition().y <= 10 && _moveRight == -1 ? _moveRight = 1 : 0;
	_enemyRight[0].getPosition().y >= 48 && _moveRight == 1 ? _moveRight = -1 : 0;
	_enemyRight[0].setPosition({_enemyRight[0].getPosition().x, _enemyRight[0].getPosition().y + (1 * _moveRight)});
	_enemyRight[1].setPosition({_enemyRight[1].getPosition().x, _enemyRight[1].getPosition().y + (1 * _moveRight)});

	_enemyUp[0].getPosition().x <= 10 && _moveUp == -1 ? _moveUp = 1 : 0;
	_enemyUp[0].getPosition().x >= 48 && _moveUp == 1 ? _moveUp = -1 : 0;
	_enemyUp[0].setPosition({_enemyUp[0].getPosition().x+ (1 * _moveUp), _enemyUp[0].getPosition().y});
	_enemyUp[1].setPosition({_enemyUp[1].getPosition().x+ (1 * _moveUp), _enemyUp[1].getPosition().y});

	_enemyDown[0].getPosition().x <= 10 && _moveDown == -1 ? _moveDown = 1 : 0;
	_enemyDown[0].getPosition().x >= 48 && _moveDown == 1 ? _moveDown = -1 : 0;
	_enemyDown[0].setPosition({_enemyDown[0].getPosition().x+ (1 * _moveDown), _enemyDown[0].getPosition().y});
	_enemyDown[1].setPosition({_enemyDown[1].getPosition().x+ (1 * _moveDown), _enemyDown[1].getPosition().y});


}

void SolarFox::close()
{
	_shipRight.clear();
	_shipLeft.clear();
	_shipUp.clear();
	_shipDown.clear();
	_enemyRight.clear();
	_enemyLeft.clear();
	_enemyUp.clear();
	_enemyDown.clear();
	_enemyRightShot.clear();
	_enemyLeftShot.clear();
	_enemyUpShot.clear();
	_enemyDownShot.clear();
	_foods.clear();
	_scoreInt = 0;
	_moveRight = 1;
	_moveLeft = -1;
	_moveUp = -1;
	_moveDown = 1;
	_shotRange = 0;
	_direction = 2;
	_lastDirection = 2;
	_isActive = false;
}

void SolarFox::handleScore()
{
	_score->setString(std::to_string(_scoreInt));
}

void SolarFox::handleShot()
{
	if (_shotRange > 2) {
		_shotRange = 0;
		_shot->setPosition({_canon.x, _canon.y});
	}
	switch (_direction) {
	case 1 :
		_shotRange += 1;
		_shot->setPosition({_canon.x + _shotRange, _canon.y});
		break;
	case 2 :
		_shotRange += 1;
		_shot->setPosition({_canon.x, _canon.y - _shotRange});
		break;
	case 3 :
		_shotRange += 1;
		_shot->setPosition({_canon.x - _shotRange, _canon.y});
		break;
	case 4 :
		_shotRange += 1;
		_shot->setPosition({_canon.x, _canon.y + _shotRange});
		break;
	default:
		break;
	}
}


//1 == droite
//2 == haut
//3 == gauche
//4 == bas
void SolarFox::autoMove()
{
	if (_direction == 1) {
		_ship->setPosition({_ship->getPosition().x + 1, _ship->getPosition().y});
		ui::position tmpPos = _ship->getPosition();
		for (auto shipRight : _shipRight) {
			_ship->setPosition({_ship->getPosition().x + shipRight.x, _ship->getPosition().y + shipRight.y});
			arcade::Engine::Graphic().drawRect(*_ship);
			_ship->setPosition(tmpPos);
		}
		_canon = {tmpPos.x + 2, tmpPos.y};
	}
	if (_direction == 2) {
		_ship->setPosition({_ship->getPosition().x, _ship->getPosition().y - 1});
		ui::position tmpPos = _ship->getPosition();
		for (auto shipUp : _shipUp) {
			_ship->setPosition({_ship->getPosition().x + shipUp.x, _ship->getPosition().y + shipUp.y});
			arcade::Engine::Graphic().drawRect(*_ship);
			_ship->setPosition(tmpPos);
		}
		_canon = {tmpPos.x, tmpPos.y - 2};

	}
	if (_direction == 3) {
		_ship->setPosition({_ship->getPosition().x - 1, _ship->getPosition().y});
		ui::position tmpPos = _ship->getPosition();
		for (auto shipLeft : _shipLeft) {
			_ship->setPosition({_ship->getPosition().x + shipLeft.x, _ship->getPosition().y + shipLeft.y});
			arcade::Engine::Graphic().drawRect(*_ship);
			_ship->setPosition(tmpPos);
		}
		_canon = {tmpPos.x - 2, tmpPos.y};

	} if (_direction == 4) {
		_ship->setPosition({_ship->getPosition().x, _ship->getPosition().y + 1});
		ui::position tmpPos = _ship->getPosition();
		for (auto shipDown : _shipDown) {
			_ship->setPosition({_ship->getPosition().x + shipDown.x, _ship->getPosition().y + shipDown.y});
			arcade::Engine::Graphic().drawRect(*_ship);
			_ship->setPosition(tmpPos);
		}
		_canon = {tmpPos.x, tmpPos.y + 2};

	}
}

void SolarFox::handleCollisionLeft()
{
	for (auto &shot : _enemyLeftShot) {
		if ((_canon.x - 2 == shot.x && _canon.y == shot.y) || (_canon.x - 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipLeft)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyRightShot) {
		if ((_canon.x - 2 == shot.x && _canon.y == shot.y) || (_canon.x - 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipLeft)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyUpShot) {
		if ((_canon.x - 2 == shot.x && _canon.y == shot.y) || (_canon.x - 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipLeft)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyDownShot) {
		if ((_canon.x - 2 == shot.x && _canon.y == shot.y) || (_canon.x - 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipLeft)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
}

void SolarFox::handleCollisionRight()
{
	for (auto &shot : _enemyRightShot) {
		if ((_canon.x + 2 == shot.x && _canon.y == shot.y) || (_canon.x + 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipRight)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyLeftShot) {
		if ((_canon.x + 2 == shot.x && _canon.y == shot.y) || (_canon.x + 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipRight)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyUpShot) {
		if ((_canon.x + 2 == shot.x && _canon.y == shot.y) || (_canon.x + 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipRight)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyDownShot) {
		if ((_canon.x + 2 == shot.x && _canon.y == shot.y) || (_canon.x + 1 == shot.x && _canon.y == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipRight)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
}

void SolarFox::handleCollisionUp()
{
	for (auto &shot : _enemyUpShot) {
		if ((_canon.x == shot.x && _canon.y - 1 == shot.y) || (_canon.x == shot.x && _canon.y - 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipUp)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyRightShot) {
		if ((_canon.x == shot.x && _canon.y - 1 == shot.y) || (_canon.x == shot.x && _canon.y - 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipUp)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyLeftShot) {
		if ((_canon.x == shot.x && _canon.y - 1 == shot.y) || (_canon.x == shot.x && _canon.y - 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipUp)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyDownShot) {
		if ((_canon.x == shot.x && _canon.y - 1 == shot.y) || (_canon.x == shot.x && _canon.y - 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipUp)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
}

void SolarFox::handleCollisionDown()
{
	for (auto &shot : _enemyDownShot) {
		if ((_canon.x == shot.x && _canon.y + 1 == shot.y) || (_canon.x == shot.x && _canon.y + 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipDown)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyUpShot) {
		if ((_canon.x == shot.x && _canon.y + 1 == shot.y) || (_canon.x == shot.x && _canon.y + 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipDown)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyLeftShot) {
		if ((_canon.x == shot.x && _canon.y + 1 == shot.y) || (_canon.x == shot.x && _canon.y + 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipDown)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
	for (auto &shot : _enemyRightShot) {
		if ((_canon.x == shot.x && _canon.y + 1 == shot.y) || (_canon.x == shot.x && _canon.y + 2 == shot.y) || (_shot->getPosition().x == shot.x && _shot->getPosition().y == shot.y) || (_canon.x == shot.x && _canon.y == shot.y))
			shot = {-1, -1};
		for (const auto &ship : _shipDown)
			if (ship.x + _ship->getPosition().x == shot.x && ship.y + _ship->getPosition().y == shot.y)
				handleLose();
	}
}

void SolarFox::handleWin()
{
	int i = 0;
	arcade::Engine::instance().addScore(_scoreInt);

	for (; i < (int)_foods.size() && _foods[i].getPosition().x == -1 && _foods[i].getPosition().y == -1; i++);
	if (i == (int)_foods.size()) {
		_isActive = false;
		_winLose->setString("YOU WIN");
	}
}

void SolarFox::handleLose()
{
	arcade::Engine::instance().addScore(_scoreInt);
	_winLose->setString("YOU LOSE");
	_isActive = false;
}

void SolarFox::restart()
{
	init();
	close();
}

extern "C" IGameApi *entryPoint()
{
	return new SolarFox();
}
