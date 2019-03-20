/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Engine.hpp"
#include "../lib/IApi.hpp"
#include <dlfcn.h>

int main(int ac, char **av)
{
	arcade::Engine engine = arcade::Engine::instance();
	ui::IApi *graphAPI = nullptr;

	if (ac != 2)
		return 84;
	printf("main1\n");
	engine.load(av[1]);
	printf("main2\n");
	graphAPI = engine.getGraphLib();
	printf("main3\n");
	graphAPI->init();
	printf("main4\n");
	while (true) {
		printf("wesh\n");
		engine.getGameLib()->tick();
	}
	engine.closeHandlers();
	return (0);
}
