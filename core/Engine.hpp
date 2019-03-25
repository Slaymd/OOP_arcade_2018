/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "IGameApi.hpp"
#include "IApi.hpp"
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>
#include <algorithm>
#include <cstring>

namespace arcade {

	class Engine {

		class EventHandler {
			public:

			private:
		};


		public:
		Engine() = default;
		~Engine() = default;

		static Engine &instance();

		static ui::IApi &Graphic();

		void start(int ac, char **av);

		struct game_t {
			std::string name;
		};

		std::vector<arcade::Engine::game_t *> getGames() {
			return _games; };
		void changeGame(std::string);


		private:

		IGameApi *getCurrentGame();
		ui::IApi *getCurrentGraphLib();

		void load(std::string);


		void rotateGames(bool reversed);

		void rotateGraphLibs(bool reversed);


		IGameApi *getGameLib()
		{
			return _gameLib[0];
		};

		ui::IApi *getGraphLib()
		{
			return _graphLib[0];
		};

		void closeHandlers();

		void eventHandler(arcade::event::Key);

		std::vector<std::string> getSharedLibPaths(const std::string &pathToDirectory,  std::string defaultPath = "") const;
		std::string findName(std::string) const;

		std::vector<IGameApi *> _gameLib;
		std::vector<ui::IApi *> _graphLib;
		std::vector<arcade::Engine::game_t *> _games;
		std::vector<void *> _handlers;
		IGameApi *_menu;
		//Indexes

		int _gameIndex = 0;
		int _graphLibIndex = 0;
		bool _isActive = true;


	};
}

#endif //ARCADE_CORE_HPP
