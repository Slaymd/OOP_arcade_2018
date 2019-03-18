/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#include "core.hpp"

void core::Loader::loadLib()
{

	dlopen("./lib/lib_arcade_sfml.so", RTLD_LAZY);
}

void core::Loader::initLib()
{

}
