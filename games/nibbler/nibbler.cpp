/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/
#include "Nibbler.hpp"

void Nibbler::init()
{
	_name = new ui::UIText({100, 100}, "TEST");
	_name->setColor({255, 255, 255});

	_input = new ui::UIText({100, 150}, "INPUT");
	_input->setColor({255, 100, 100});
}

void Nibbler::tick()
{
	auto *g = new ui::SFMLApi;

	g->drawText(*_name);
	g->drawText(*_input);
}

void Nibbler::close()
{
	//TODO close ce qui a était open
}

extern "C" Nibbler *entryPoint()
{
	return new Nibbler();
}
