/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "../games/IGameApi.hpp"
#include "../lib/IApi.hpp"
#include <iostream>
#include <dirent.h>
#include <dlfcn.h>

namespace arcade {

	class Engine {

		class EventHandler {
			public:

			private:
		};

		class Menu : public IGameApi {
		};

		public:
		Engine() = default;
		~Engine() = default;

		static Engine &instance();
		static ui::IApi &Graphic();

		void load(std::string);

		void rotateGames();

		void rotateGraph();

		IGameApi *getGameLib()
		{
			return _gameLib[0];
		};

		ui::IApi *getGraphLib()
		{

			return _graphLib[0];
		};

		void closeHandlers();

		private:
		std::vector<std::string> getSharedLibPaths(
			const std::string &pathToDirectory,
			std::string defaultPath = ""
		) const;
		std::string findName(std::string);

		std::vector<IGameApi *> _gameLib;
		std::vector<std::string> _pathGame;
		std::vector<ui::IApi *> _graphLib;
		std::vector<std::string> _pathGraph;
		std::vector<void *> _handlers;

	};
}

#endif //ARCADE_CORE_HPP
