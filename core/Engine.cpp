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
	return (*arcade::Engine::instance().getCurrentGraphLib());
}


/*
 *      ENGINE MAIN
 */

void arcade::Engine::start(int ac, char **av)
{
	int e;

	if (ac != 2)
		return; //TODO: exception
	arcade::Engine::instance().load(av[1]);
	arcade::Engine::instance().Graphic().init();
	arcade::Engine::instance().rotateGames(false);
	_gameIndex = 1;
	arcade::Engine::instance().getCurrentGame()->init();
//	_menu = arcade::Engine::instance().getCurrentGame();
//	_menu->init();
	while (_isActive) {
		e = arcade::Engine::instance().getCurrentGraphLib()->getEvent();
		eventHandler((arcade::event::Key)e);
		arcade::Engine::instance().getCurrentGame()->tick(e);
	}
	arcade::Engine::instance().closeHandlers();
}

/*
 *      LOADER
 */

void arcade::Engine::load(std::string defaultLib)
{
	std::vector<std::string> tmpGame = getSharedLibPaths("./games/");
	std::vector<std::string> tmpLib = getSharedLibPaths("./lib/", std::move(defaultLib));
	ui::IApi *(*graphEntryPoint)();
	IGameApi *(*gameEntryPoint)();

	for (const std::string &gamePath : tmpGame) {
		void *handleGame = dlopen(gamePath.c_str(), RTLD_LAZY);
		if (!handleGame)
			//TODO throw an error
			return;
		auto gameStruct = new game_t;
		gameStruct->name = arcade::Engine::findName(gamePath);
		_games.push_back(gameStruct);

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

void arcade::Engine::closeHandlers()
{
	for (void *handler : _handlers) {
		dlclose(handler);
	}
}

/*
 *      EVENTS
 */

void arcade::Engine::eventHandler(arcade::event::Key e)
{
	switch (e) {
	case event::ESCAPE:
		Graphic().close();
//		getCurrentGraphLib()->close();
		_isActive = false;
		break;
	case event::ARROW_UP:
		rotateGraphLibs(true);
		break;
	case event::ARROW_DOWN:
		rotateGraphLibs(true);
		break;
	default:
		break;
	}
}

/*
 *      LIB/GAME SWITCHER
 */

void arcade::Engine::rotateGames(bool reversed)
{
	_gameIndex += reversed ? -1 : 1;

	if (_gameIndex < 0)
		_gameIndex = (int)_gameLib.size() - 1;
	else if (_gameIndex >= (int)_gameLib.size())
		_gameIndex = 0;
}

void arcade::Engine::rotateGraphLibs(bool reversed)
{
	getCurrentGraphLib()->close();

	_graphLibIndex += reversed ? -1 : 1;

	if (_graphLibIndex < 0)
		_graphLibIndex = (int)_graphLib.size() - 1;
	else if (_graphLibIndex >= (int)_graphLib.size())
		_graphLibIndex = 0;

	getCurrentGraphLib()->init();
}

/*
 *      UTILS
 */

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
			if (ext == nullptr || strcmp(ext, ".so") != 0) {
				continue;
			}
			if (defslash && patslash && strcmp(defslash, patslash) == 0) {
				sharedLibs.insert(sharedLibs.begin(), path);
				defaultExist = true;
			} else {
				sharedLibs.push_back(path);
			}
		}

		closedir(dir);
	}
	defaultExist = defaultPath.length() == 0 ? true : defaultExist;
	if (!defaultExist)
		throw std::exception();
	return sharedLibs;
}

std::string arcade::Engine::findName(std::string path) const
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

/*
 *      LIB GETTERS
 */

IGameApi *arcade::Engine::getCurrentGame()
{
	return _gameLib.empty() ? nullptr : _gameLib[_gameIndex];
}

ui::IApi *arcade::Engine::getCurrentGraphLib()
{
	return _graphLib.empty() ? nullptr : _graphLib[_graphLibIndex];
}

void arcade::Engine::changeGame(std::string str)
{
	if (str == "nibbler")
		_gameIndex = 1;
	if (str == "menu")
		_gameIndex = 0;
	arcade::Engine::instance().getCurrentGame()->close();
	arcade::Engine::instance().rotateGames(true);
	arcade::Engine::instance().getCurrentGame()->init();
}
