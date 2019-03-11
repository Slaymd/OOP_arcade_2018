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
		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive()) {
			graphAPI->setTitle("iterator: " + std::to_string(i));
			graphAPI->display();
			i++;
		}
		sleep(5);
	}
}
