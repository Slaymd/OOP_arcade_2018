/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_SFMLGRAPHAPI_HPP
#define ARCADE_SFMLGRAPHAPI_HPP

#include "IGraphAPI.hpp"

class SFMLGraphAPI : public IGraphAPI {

	SFMLGraphAPI() = default;
	~SFMLGraphAPI() = default;

	void initDisplay() override;

	void addText() override;

	void abortDisplay() override;
};

#endif //ARCADE_SFMLGRAPHAPI_HPP
