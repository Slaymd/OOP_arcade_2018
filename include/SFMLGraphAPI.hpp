/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_SFMLGRAPHAPI_HPP
#define ARCADE_SFMLGRAPHAPI_HPP

#include <SFML/Graphics.hpp>
#include "IGraphAPI.hpp"

class SFMLGraphAPI : public IGraphAPI {

	public:
	SFMLGraphAPI() = default;
	~SFMLGraphAPI() = default;

	void initDisplay(const std::string &) override;
	void addText() override;
	void abortDisplay() override;

	private:
	sf::RenderWindow *_win;

};

#endif //ARCADE_SFMLGRAPHAPI_HPP
