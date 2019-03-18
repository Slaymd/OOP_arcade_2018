/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "../include/IGraphAPI.hpp"
#include "core.hpp"
#include <dlfcn.h>

int main(void)
{
	ui::IGraphAPI *graphAPI;
	core::Game *game;

	void *handleAPI = dlopen("./lib/lib_arcade_sfml.so", RTLD_LAZY);
	void *handleGame = dlopen("./games/lib_arcade_nibbler.so", RTLD_LAZY);

	ui::IGraphAPI *(*getGraphAPI)();

	void (*play)(ui::IGraphAPI *);

	if (!handleAPI || !handleGame)
		return (84);
	getGraphAPI = reinterpret_cast<ui::IGraphAPI *(*)()>(dlsym(handleAPI, "getGraphAPI"));
	play = reinterpret_cast<void (*)(ui::IGraphAPI *)>(dlsym(handleGame, "play"));
	graphAPI = getGraphAPI();


	dlclose(handleAPI);
	dlclose(handleGame);
	return (0);
}
