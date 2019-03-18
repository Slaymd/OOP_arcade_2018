/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Core.hpp"
#include "../lib/IApi.hpp"
#include <dlfcn.h>

int main(int ac, char **av)
{
	core::Loader loader;
	ui::IApi *graphAPI = nullptr;

	if (ac != 2)
		return 84;
	loader.load(av[1]);
	printf("1\n");
	graphAPI = loader.getGraphLib();
	printf("2\n");
	graphAPI->init();
	printf("3\n");
	while (graphAPI) {
		printf("cc\n");
	}
	return (0);
}
