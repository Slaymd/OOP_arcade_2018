/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "Nibbler.hpp"

void Nibbler::init(arcade::Engine engine)
{
	_engine = engine;
	_name = new ui::UIText({100, 100}, "TEST");
	_name->setColor({255, 255, 255});

	_input = new ui::UIText({100, 150}, "INPUT");
	_input->setColor({255, 100, 100});
}

void Nibbler::tick()
{
	printf("tick\n");
	_engine.Graphic().clear();
//	_engine.Graphic().render();
//	auto *g = new ui::SFMLApi;

//	g->drawText(*_name);
//	g->drawText(*_input);
}

void Nibbler::close()
{
	//TODO close ce qui a était open
}

extern "C" IGameApi *entryPoint()
{
	return new Nibbler();
}
