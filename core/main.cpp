/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Engine.hpp"
#include "../lib/IApi.hpp"
#include <dlfcn.h>

int main(int ac, char *av[])
{
	arcade::Engine::instance().start(ac, av);
}
