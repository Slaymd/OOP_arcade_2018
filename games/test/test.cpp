/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Maxime
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <ctime>
#include <unistd.h>
#include "../../include/IGraphAPI.hpp"

extern "C" {
	void play(IGraphAPI *graphAPI)
	{
		int i = 0;
		sf::Event event;


		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive(event)) {
            graphAPI->clear();
			graphAPI->setTitle("iterator: " + std::to_string(i));
			graphAPI->drawSquare(100, 500, "Red");
            graphAPI->drawSquare(500, 100, "Green");
            graphAPI->display();
			i++;
		}
		graphAPI->abortDisplay();
	}
}
