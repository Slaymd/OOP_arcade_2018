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

		public:
		Engine() = default;
		~Engine() = default;

		static Engine &instance();

		static ui::IApi &Graphic();

		void start(int ac, char **av);

		private:
		IGameApi *getCurrentGame();
		ui::IApi *getCurrentGraphLib();

		void load(std::string);
		void rotateGames(bool = false);
		void rotateGraphLibs(bool = false);
		void closeHandlers();

		private:
		std::vector<std::string> getSharedLibPaths(const std::string &pathToDirectory, std::string defaultPath = "") const;
		std::string findName(std::string);

		//Lists

		std::vector<IGameApi *> _gameLibs;
		std::vector<ui::IApi *> _graphLibs;
		std::vector<void *> _handlers;

		//Indexes

		int _gameIndex = 0;
		int _graphLibIndex = 0;


	};

}

#endif //ARCADE_CORE_HPP
