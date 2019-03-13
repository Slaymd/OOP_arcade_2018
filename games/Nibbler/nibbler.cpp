/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#include "nibbler.hpp"
#include "../../include/IGraphAPI.hpp"

extern "C" {
	void play(ui::IGraphAPI *graphAPI) {
		graphAPI->initDisplay("It's work !");
		while (graphAPI->isActive()) {
			graphAPI->clear();
			graphAPI->drawRect({0, 0}, {100, 100}, {ui::color::WHITE, ""});
			graphAPI->display();
		}
	}
}
