/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "../../include/SFMLGraphAPI.hpp"

extern "C" {
	IGraphAPI *getGraphAPI() {
		return (new SFMLGraphAPI());
	}
}

void SFMLGraphAPI::initDisplay()
{

}

void SFMLGraphAPI::addText()
{
}

void SFMLGraphAPI::abortDisplay()
{
}
