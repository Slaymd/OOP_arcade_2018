/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Core.hpp"
#include <dlfcn.h>

int main(int ac, char **av)
{
	core::Loader loader;

	if (ac != 2)
		return (84);
	//loader.load(av[1]);
	loader.load();
}

//int main(void)
//{
//	ui::IGraphAPI *graphAPI;
//	core::Game *game;
//
//	void *handleAPI = dlopen("./lib/lib_arcade_sfml.so", RTLD_LAZY);
//	void *handleGame = dlopen("./games/lib_arcade_nibbler.so", RTLD_LAZY);
//
//	ui::IGraphAPI *(*getGraphAPI)();
//
//	void (*play)(ui::IGraphAPI *);
//
//	if (!handleAPI || !handleGame)
//		return (84);
//	getGraphAPI = reinterpret_cast<ui::IGraphAPI *(*)()>(dlsym(handleAPI, "getGraphAPI"));
//	play = reinterpret_cast<void (*)(ui::IGraphAPI *)>(dlsym(handleGame, "play"));
//	graphAPI = getGraphAPI();
//
//
//	dlclose(handleAPI);
//	dlclose(handleGame);
//	return (0);
//}
