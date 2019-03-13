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
	void play(ui::IGraphAPI *graphAPI)
	{
		int i = 0;
		int **map = new int*[4];
		int mapcontent[][5] = {{0, 0, 1, 0, -1}, {0, 0, 1, 0, -1}, {0, 0, 1, 1, -1}}; //TODO: ???? this is dirty... how to do?
		for (int y = 0; y < 3; y++) {
			map[y] = new int[5];
			for (int x = 0; mapcontent[y][x] != -1; x++) {
				map[y][x] = mapcontent[y][x];
				map[y][x+1] = -1;
			}
			map[y+1] = nullptr;
		}


		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive()) {
			graphAPI->clear();
			graphAPI->setTitle("iterator: " + std::to_string(i));
//			graphAPI->drawFrame(map, {{ui::color::BLUE, ""}});
//			graphAPI->drawRect({0, 0}, {100, 100}, {ui::color::WHITE, ""});
//			graphAPI->drawRect({100, 100}, {100, 100}, {ui::color::BLUE,            "/assets/viatransit_180x180.png"});
//			graphAPI->drawSquare(100, 500, "Red");
//                      graphAPI->drawSquare(500, 100, "Green");
                        graphAPI->display();
			i++;
		}
	}
}
