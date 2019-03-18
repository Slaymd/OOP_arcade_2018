/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include <iostream>
#include "Core.hpp"

std::string findName(std::string path)
{
	std::string name;
	size_t i = 0;

	i = path.size();
	for(; i > 0 && path[i - 1] != '_'; i--);
	if (i == 0)
		//TODO throw an error
		return nullptr;
	for (size_t j = 0; path[i] != '.' && path[i]; i++, j++) {
		name.insert(j, 1, path[i]);
	}
	if (!path[i])
		//TODO throw an error
		return nullptr;
	std::cout << name << std::endl;
	return name;
}

void core::Loader::load(std::string defaultLib)
{
	std::vector<std::string> tmpGame = getSharedLibPaths("./games/");
	std::vector<std::string> tmpLib = getSharedLibPaths("./lib/", defaultLib);

	for (std::string tmp : tmpLib) {
		std::cout << "> " << tmp << std::endl;
	}

	void *handleGame;
	void *handleGraph;

	for(size_t i = 0; i < _pathGame.size(); i++) {
		handleGame = dlopen(_pathGame[i].c_str(), RTLD_LAZY);
		if (!handleGame)
			//TODO throw an error
			return;
		_gameLib.emplace_back(reinterpret_cast<IGameApi *>(dlsym(handleGame, findName(_pathGame[i]).c_str())));
	}
	for(size_t i = 0; i < _pathGraph.size(); i++) {
		handleGraph = dlopen(_pathGraph[i].c_str(), RTLD_LAZY);
		if (!handleGame)
			//TODO throw an error
			return;
		_graphLib.emplace_back(reinterpret_cast<ui::IApi *>(dlsym(handleGraph, findName(_pathGraph[i]).c_str())));
	}

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

std::vector<std::string> core::Loader::getSharedLibPaths(
	const std::string &pathToDirectory, std::string defaultPath
) const
{
	std::vector<std::string> sharedLibs;
	DIR *dir = nullptr;
	struct dirent *ent = nullptr;
	bool defaultExist = false;

	if ((dir = opendir(pathToDirectory.c_str())) != nullptr) {
		while ((ent = readdir(dir)) != nullptr) {
			char *ext = strrchr(ent->d_name, '.');
			std::string path = pathToDirectory +
				std::string(ent->d_name);
			const char *defslash = strrchr(defaultPath.c_str(), '/');
			const char *patslash = strrchr(path.c_str(), '/');


			if (ext == nullptr || strcmp(ext, ".so") != 0)
				continue;
			if (defslash && patslash && strcmp(defslash, patslash) == 0) {
				sharedLibs.insert(sharedLibs.begin(), path);
				defaultExist = true;
			} else
				sharedLibs.push_back(path);
		}
		closedir(dir);
	}
	defaultExist = defaultPath.length() == 0 ? true : defaultExist;
	if (!defaultExist)
		throw std::exception();
	return sharedLibs;
}
