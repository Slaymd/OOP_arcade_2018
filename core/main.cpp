/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Engine.hpp"
#include <cstdlib>
#include <iostream>
#include <ctime>

int main(int ac, char *av[])
{
	std::srand(std::time(nullptr));
	arcade::Engine::instance().start(ac, av);
}
