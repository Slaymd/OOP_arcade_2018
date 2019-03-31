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
	int e;

	if (ac != 2) {
		std::cout << "Usage:" << std::endl;
		std::cout << "\t" << av[0] << " <path_to_graph_lib.so>"
		<< std::endl;
		exit(84);
	}
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
	saveScores();
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
			throw EngineException("load: dlopen of " + gamePath + " failed: " + dlerror());
		gameEntryPoint = (IGameApi *(*)())dlsym(handleGame, "entryPointGame");
		if (!gameEntryPoint)
			throw EngineException("load: dlsym of " + gamePath + " failed: " + dlerror());
		IGameApi *game = gameEntryPoint();

		_gameLibs.emplace_back((game_t){findName(gamePath), game});
		_handlers.emplace_back(handleGame);
	}
	for (const std::string &libPath : tmpLib) {
		void *handleGraph = dlopen(libPath.c_str(), RTLD_LAZY);
		if (!handleGraph)
			throw EngineException("load: dlopen of " + libPath + " failed: " + dlerror());
		graphEntryPoint = (ui::IApi *(*)())dlsym(handleGraph, "entryPoint");
		if (!graphEntryPoint)
			throw EngineException("load: dlsym of " + libPath + " failed: " + dlerror());
		ui::IApi *api = graphEntryPoint();

		_graphLibs.emplace_back((graph_t){findName(libPath), api});
		_handlers.emplace_back(handleGraph);
	}
	loadScores();
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
		Graphic().close();
		_isActive = false;
		break;
	case event::M:
		if (_gameIndex == -1)
			break;
		getCurrentGame()->close();
		_gameIndex = -1;
		getCurrentGame()->init();
		break;
	case event::ARROW_LEFT:
		rotateGames(true);
		break;
	case event::ARROW_RIGHT:
		rotateGames(false);
		break;
	case event::ARROW_UP:
		rotateGraphLibs(true);
		break;
	case event::ARROW_DOWN:
		rotateGraphLibs(false);
		break;
	case event::SPACE:
		if (_gameIndex != -1)
			getCurrentGame()->restart();
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
		exit(84);
	return sharedLibs;
}

std::string arcade::Engine::findName(std::string path) const
{
	std::string name;
	size_t i = 0;

	i = path.size();
	for(; i > 0 && path[i - 1] != '_'; i--);
	if (i == 0)
		throw EngineException("findName: failed.");
	for (size_t j = 0; path[i] != '.' && path[i]; i++, j++) {
		name.insert(j, 1, path[i]);
	}
	if (!path[i])
		throw EngineException("findName: failed.");
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
		if (_gameIndex == (int)i)
			return;
		getCurrentGame()->close();
		_gameIndex = (int)i;
		getCurrentGame()->init();
		return;
	}
	throw EngineException("changeGame: not found.");
}

void arcade::Engine::changeGraphLib(std::string str)
{
	graph_t lib;

	for (std::size_t i = 0; i < _graphLibs.size(); i++) {
		lib = _graphLibs[i];
		if (str != lib.name)
			continue;
		if (_graphLibIndex == (int)i)
			return;
		getCurrentGraphLib()->close();
		_graphLibIndex = (int)i;
		getCurrentGraphLib()->init();
		return;
	}
	throw EngineException("changeGame: not found.");
}

/*
 * SCORES
 */

std::string &arcade::Engine::getPlayerName()
{
	return _playerName;
}


std::map<std::string, std::vector<arcade::Engine::player_t>> &arcade::Engine::getRanking()
{
	return _ranking;
}

void arcade::Engine::addScore(int val)
{
	if (_playerName.size() == 0)
		return;
	std::vector<player_t> players = _ranking[getGames()[_gameIndex].name];
	players.emplace_back((player_t){_playerName, val});
	std::sort(players.begin(), players.end());
	std::reverse(players.begin(), players.end());

	_ranking[getGames()[_gameIndex].name] = players;
}

void arcade::Engine::saveScores()
{
	for (auto const &score : _ranking) {
		std::ofstream scoreFile("games/" + score.first + ".score");

		for (auto const &player : score.second) {
			if (player.name.size() > 0)
				scoreFile << player.name << ":" << player.score
				<< std::endl;
		}
	}
}

void arcade::Engine::loadScores()
{
	int lastGameIndex = _gameIndex;
	int gameIndex = -1;

	for (auto const &game : getGames()) {
		gameIndex++;
		_gameIndex = gameIndex;
		std::ifstream scoreFile("games/" + game.name + ".score");
		std::string line;
		size_t sep;

		_ranking.insert({game.name, std::vector<player_t>()});

		if (scoreFile.fail())
			continue;
		while (std::getline(scoreFile, line)) {
			if (line.empty())
				continue;
			sep = line.find(':');
			if (sep == std::string::npos)
				continue;
			try {
				_playerName = line.substr(0, sep);
				if (_playerName.size() > 0)
					addScore(std::atoi(
					line.substr(sep + 1).c_str()));
			} catch (std::exception ex) {
				continue;
			}
		}
	}
	_gameIndex = lastGameIndex;
	_playerName = "";
}
