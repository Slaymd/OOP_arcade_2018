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
#include "../../include/IGraphAPI.hpp"

extern "C" {
	void play(IGraphAPI *graphAPI)
	{
		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive()) {
			graphAPI->display();
		}
	}
}
