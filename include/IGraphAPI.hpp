/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_IGRAPHAPI_HPP
#define ARCADE_IGRAPHAPI_HPP

class IGraphAPI {

	virtual void initDisplay(const std::string &) = 0;
	virtual void display() = 0;
	virtual void abortDisplay() = 0;

	virtual void setTitle(const std::string &) = 0;
	virtual bool isActive() = 0;

};

extern "C" IGraphAPI *getGraphAPI();

#endif //ARCADE_IGRAPHAPI_HPP
