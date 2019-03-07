/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "../include/IGraphAPI.hpp"
#include <dlfcn.h>

int main(void)
{
	IGraphAPI *graphAPI;
	void *handleAPI = dlopen("/Users/slaymd/Epitech/B4-OOP/OOP_arcade_2018/lib/lib_arcade_sfml.so", RTLD_LAZY);
	void *handleGame = dlopen("/Users/slaymd/Epitech/B4-OOP/OOP_arcade_2018/lib/lib_arcade_test.so", RTLD_LAZY);
	IGraphAPI *(*getGraphAPI)();
	void (*play)(IGraphAPI *);

	if (!handleAPI || !handleGame)
		return (0);
	getGraphAPI = reinterpret_cast<IGraphAPI *(*)()>(dlsym(handleAPI, "getGraphAPI"));
	play = reinterpret_cast<void (*)(IGraphAPI *)>(dlsym(handleGame, "play"));
	graphAPI = (*getGraphAPI)();

	play(graphAPI);

	dlclose(handleAPI);
	dlclose(handleGame);
	return (0);
}