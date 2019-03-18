/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include <iostream>
#include "core.hpp"

void core::Loader::init()
{
	_pathGame.emplace_back("./games/lib_arcade_nibbler.so");
	_pathLib.emplace_back("./lib/lib_arcade_sfml.so");
}

void core::Loader::load()
{

	init();
	std::vector<std::string> tmpGame = _pathGame;
	std::vector<std::string> tmpLib = _pathLib;

	void *handleGame = dlopen(_pathGame[0].c_str(), RTLD_LAZY);
	void *handleGraph = dlopen(_pathLib[0].c_str(), RTLD_LAZY);

	if (!handleGraph || !handleGame)
		return;
	_gameLib.emplace_back(reinterpret_cast<IGameApi *>(dlsym(handleGame, "nibbler")));
	_graphLib.emplace_back(reinterpret_cast<ui::IApi *>(dlsym(handleGraph, "sfml")));

	dlclose(handleGame);
	dlclose(handleGraph);
}

void core::Loader::rotateGames()
{
	std::rotate(_gameLib.begin(), _gameLib.begin()+1, _gameLib.end());

}

void core::Loader::rotateGraph()
{
	std::rotate(_graphLib.begin(), _graphLib.begin()+1, _graphLib.end());
}
