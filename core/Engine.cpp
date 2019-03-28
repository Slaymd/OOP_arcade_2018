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

void arcade::Engine::start(int ac, char *av[])
{
	int e = -1;

	if (ac != 2)
		return; //TODO: exception
	_menu = new Menu();
	arcade::Engine::instance().load(std::string(av[1]));
	arcade::Engine::instance().Graphic().init();
	arcade::Engine::instance().getCurrentGame()->init();

	while (_isActive) {
		e = arcade::Engine::instance().getCurrentGraphLib()->getEvent();
		eventHandler((arcade::event::Key)e);

		if (!_isActive)
			break;
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
		gameEntryPoint = (IGameApi *(*)())dlsym(handleGame, "entryPoint");
		IGameApi *game = gameEntryPoint();

		_gameLibs.emplace_back((game_t){findName(gamePath), game});
		_handlers.emplace_back(handleGame);
	}
	for (const std::string &libPath : tmpLib) {
		void *handleGraph = dlopen(libPath.c_str(), RTLD_LAZY);
		if (!handleGraph)
			//TODO throw an error
			return;
		graphEntryPoint = (ui::IApi *(*)())dlsym(handleGraph, "entryPoint");
		ui::IApi *api = graphEntryPoint();

		_graphLibs.emplace_back((graph_t){findName(libPath), api});
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
		getCurrentGame()->close();
		if (_gameIndex >= 0) {
			_gameIndex = -1;
			getCurrentGame()->init();
		} else {
			Graphic().close();
			_isActive = false;
		}
		break;
	case event::ARROW_UP:
		rotateGraphLibs(true);
		break;
	case event::ARROW_DOWN:
		rotateGraphLibs(false);
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
	getCurrentGame()->close();

	_gameIndex += reversed ? -1 : 1;

	if (_gameIndex < 0)
		_gameIndex = (int)_gameLibs.size() - 1;
	else if (_gameIndex >= (int)_gameLibs.size())
		_gameIndex = 0;

	getCurrentGame()->init();
}

void arcade::Engine::rotateGraphLibs(bool reversed)
{
	getCurrentGraphLib()->close();

	_graphLibIndex += reversed ? -1 : 1;

	if (_graphLibIndex < 0)
		_graphLibIndex = (int)_graphLibs.size() - 1;
	else if (_graphLibIndex >= (int)_graphLibs.size())
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

IGameApi *arcade::Engine::getCurrentGame() const
{
	if (_gameIndex == -1)
		return _menu;
	return (_gameLibs.empty() ? nullptr : _gameLibs[_gameIndex].instance);
}

ui::IApi *arcade::Engine::getCurrentGraphLib() const
{
	return (_graphLibs.empty() ? nullptr : _graphLibs[_graphLibIndex].instance);
}

std::vector<arcade::Engine::game_t> arcade::Engine::getGames()
{
	return (_gameLibs);
}

std::vector<arcade::Engine::graph_t> arcade::Engine::getGraphLibs()
{
	return (_graphLibs);
}

/*
 * LIB SETTERS
 */

void arcade::Engine::changeGame(std::string str)
{
	game_t game;

	for (std::size_t i = 0; i < _gameLibs.size(); i++) {
		game = _gameLibs[i];
		if (str != game.name)
			continue;
		std::cout << "Change game to " << game.name << "." << std::endl;
		getCurrentGame()->close();
		_gameIndex = (int)i;
		getCurrentGame()->init();
		return;
	}
	std::cout << str << " not found\n";
	//TODO: throw not found
}

void arcade::Engine::changeGraphLib(std::string str)
{
	graph_t lib;

	for (std::size_t i = 0; i < _graphLibs.size(); i++) {
		lib = _graphLibs[i];
		if (str != lib.name)
			continue;
		std::cout << "Change graph lib to " << lib.name << "." << std::endl;
		std::cout << "* " << (int)i << std::endl;
		getCurrentGraphLib()->close();
		_graphLibIndex = (int)i;
		getCurrentGraphLib()->init();
		return;
	}
	std::cout << str << " not found\n";
	//TODO: throw not found
}
