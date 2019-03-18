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
#include <dirent.h>
#include <dlfcn.h>

namespace core {

	class EventHandler {
		public:

		private:
	};

	class Menu : public IGameApi {

	};

	class Loader {
		public:
		Loader() = default;
		~Loader() = default;

		void load(std::string);
		void rotateGames();
		void rotateGraph();
		IGameApi* getGameLib() { return _gameLib[0]; };
		ui::IApi* getGraphLib() { return _graphLib[0]; };

		private:
		std::vector<std::string> getSharedLibPaths(
			const std::string &pathToDirectory, std::string defaultPath = "") const;

		std::vector <IGameApi*> _gameLib;
		std::vector <std::string> _pathGame;
		std::vector <ui::IApi*> _graphLib;
		std::vector <std::string> _pathGraph;
	};
}

#endif //ARCADE_CORE_HPP
