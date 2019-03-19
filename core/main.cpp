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
	arcade::Engine engine;
	ui::IApi *graphAPI = nullptr;

	if (ac != 2)
		return 84;
	printf("[A] Max tu me casses les couilles putain de merde connard jvais t'enculer je le sais\n");
	engine.load(av[1]);
	printf("[B] Max tu me casses les couilles putain de merde connard jvais t'enculer je le sais\n");
	graphAPI = engine.getGraphLib();
	printf("[C] Max tu me casses les couilles putain de merde connard jvais t'enculer je le sais\n");
	graphAPI->init();
	printf("[D] Max tu me casses les couilles putain de merde connard jvais t'enculer je le sais\n");
	while (graphAPI) {
		graphAPI->clear();
		graphAPI->render();
	}
	engine.closeHandlers();
	return (0);
}
