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
	ui::IApi *graphAPI = nullptr;

	if (ac != 2)
		return 84;
	arcade::Engine::instance().load(av[1]);
	graphAPI = arcade::Engine::instance().getGraphLib();
	graphAPI->init();
	arcade::Engine::instance().getGameLib()->init();
	while (true) {
		arcade::Engine::instance().getGameLib()->tick();
	}
	arcade::Engine::instance().closeHandlers();
	return (0);
}
