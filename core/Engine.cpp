/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Engine.hpp"

arcade::Engine &arcade::Engine::instance()
{
	static arcade::Engine instance;

	return instance;
}

ui::IApi &arcade::Engine::Graphic()
{
	return (*arcade::Engine::instance().getGraphLib());
}

std::string arcade::Engine::findName(std::string path)
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
	return name;
}

void arcade::Engine::load(std::string defaultLib)
{
	std::vector<std::string> tmpGame = getSharedLibPaths("./games/");
	std::vector<std::string> tmpLib = getSharedLibPaths("./lib/", std::move(defaultLib));
	ui::IApi *(*graphEntryPoint)();
	IGameApi *(*gameEntryPoint)();

	for (const std::string &gamePath : tmpGame) {
		continue;
		void *handleGame = dlopen(gamePath.c_str(), RTLD_LAZY);
		if (!handleGame)
			//TODO throw an error
			return;
		gameEntryPoint = reinterpret_cast<IGameApi *(*)()>(dlsym(handleGame, "entryPoint"));
		IGameApi *game = gameEntryPoint();
		_gameLib.emplace_back(game);
		_handlers.emplace_back(handleGame);
	}
	for (const std::string &libPath : tmpLib) {
		void *handleGraph = dlopen(libPath.c_str(), RTLD_LAZY);
		if (!handleGraph)
			//TODO throw an error
			return;
		graphEntryPoint = reinterpret_cast<ui::IApi *(*)()>(dlsym(handleGraph, "entryPoint"));
		ui::IApi *api = graphEntryPoint();
		_graphLib.emplace_back(api);
		_handlers.emplace_back(handleGraph);
	}
}

void arcade::Engine::rotateGames()
{
	std::rotate(_gameLib.begin(), _gameLib.begin()+1, _gameLib.end());

}

void arcade::Engine::rotateGraph()
{
	std::rotate(_graphLib.begin(), _graphLib.begin()+1, _graphLib.end());
}

std::vector<std::string> arcade::Engine::getSharedLibPaths(
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

void arcade::Engine::closeHandlers()
{
	for (void *handler : _handlers) {
		dlclose(handler);
	}
}
