/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
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

std::vector<std::string> core::Loader::getSharedLibPaths(
	const std::string &pathToDirectory
) const
{
	std::vector<std::string> sharedLibs;
	DIR *dir = nullptr;
	struct dirent *ent = nullptr;

	if ((dir = opendir(pathToDirectory.c_str())) != nullptr) {
		while ((ent = readdir(dir)) != nullptr)
			sharedLibs.push_back(pathToDirectory + std::string(ent->d_name));
		closedir(dir);
	}
	return sharedLibs;
}