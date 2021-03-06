/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "IGameApi.hpp"
#include "EngineExceptions.hpp"
#include "IApi.hpp"
#include "Menu.hpp"
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <algorithm>
#include <cstring>
#include <map>
#include <vector>
#include <fstream>

namespace arcade {

	class Engine {

		typedef struct player {
			std::string name;
			int score;

			bool operator < (const struct player &otherPlayer) const
			{
				return (score < otherPlayer.score);
			}
		} player_t;

		struct game_t {
			std::string name;
			IGameApi *instance;
		};

		struct graph_t {
			std::string name;
			ui::IApi *instance;
		};

		public:
		Engine() = default;
		~Engine() = default;

		static Engine &instance();

		static ui::IApi &Graphic();

		void start(int ac, char *av[]);

		void addScore(int);

		std::string &getPlayerName();
		std::map<std::string, std::vector<player_t>> &getRanking();

		void saveScores();
		void loadScores();


		std::vector<arcade::Engine::game_t> getGames();
		std::vector<arcade::Engine::graph_t> getGraphLibs();

		void changeGame(std::string);
		void changeGraphLib(std::string);


		private:

		IGameApi *getCurrentGame() const;
		ui::IApi *getCurrentGraphLib() const;

		void load(std::string);

		void rotateGames(bool reversed);

		void rotateGraphLibs(bool reversed);

		void closeHandlers();

		void eventHandler(arcade::event::Key);

		std::vector<std::string> getSharedLibPaths(const std::string &pathToDirectory,  std::string defaultPath = "") const;
		std::string findName(std::string) const;

		std::vector<game_t> _gameLibs;
		std::vector<graph_t> _graphLibs;
		std::vector<void *> _handlers;
		IGameApi *_menu = nullptr;

		std::map<std::string, std::vector<player_t>> _ranking;
		std::string _playerName = "";
		//Indexes

		int _gameIndex = -1;
		int _graphLibIndex = 0;
		bool _isActive = true;


	};
}

#endif //ARCADE_CORE_HPP