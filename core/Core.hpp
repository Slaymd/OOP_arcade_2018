/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#ifndef ARCADE_CORE_HPP
#define ARCADE_CORE_HPP

#include "../include/IGraphAPI.hpp"
#include "../games/IGameApi.hpp"
#include "../lib/IApi.hpp"

namespace core {

	class Event {
		public:

		private:
	};

	class Menu {

	};

	class Game {
		public:
	};

	class Loader {
		public:
		void loadLib();
		void initLib(); //with frame

		private:
		std::vector <IGameApi*> _gameLib;
		std::vector <ui::IApi*> _graphLib;
	};
}

#endif //ARCADE_CORE_HPP
