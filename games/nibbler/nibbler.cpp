/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#include "nibbler.hpp"

void drawSnake(ui::IGraphAPI *graphAPI, nibbler *snake)
{
	int array[3][3] = {{0, 0, 0}, {1, 1, 1}, {2, 2, 2}};

	for (int i = 0; i < snake->getSize(); i += 3) {
		graphAPI->drawRect(snake->getPos(), {20 + i, 20},
		{ui::color::GREEN, ""});
//		graphAPI->drawFrame(array, {ui::color::WHITE, ""});
	}
}

void moveSnake(ui::IGraphAPI *graphAPI, nibbler *snake)
{

	if (graphAPI->getKeyboard() == 1) {
		snake->setPos({snake->getPos().x - 5, snake->getPos().y});
		snake->setSize(snake->getSize() + 3);
	} if (graphAPI->getKeyboard() == 2)
		snake->setPos({snake->getPos().x + 5, snake->getPos().y});
}

extern "C" {
	void play(ui::IGraphAPI *graphAPI) {
		nibbler *snake = new nibbler();
		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive()) {
			graphAPI->clear();
			drawSnake(graphAPI, snake);
			moveSnake(graphAPI, snake);
			graphAPI->display();
		}
	}
}
