/*
** EPITECH PROJECT, 2018
** Aiguier Maxime
** File description:
** .cpp
*/

#ifndef ARCADE_NIBBLER_HPP
#define ARCADE_NIBBLER_HPP

#include "../../include/IGraphAPI.hpp"
#include "../../include/SFMLGraphAPI.hpp"

class nibbler {

	public:
	nibbler() = default;

	//functions

	//getters
	ui::position getPos() { return _pos; };
	int getSize() { return _size; };

	//setters
	void setPos(ui::position pos) { _pos = pos; };
	void setSize(int size) { _size = size; };


	private:
	ui::position _pos = {0, 0};
	int _size = 1;
};

#endif //ARCADE_NIBBLER_HPP
