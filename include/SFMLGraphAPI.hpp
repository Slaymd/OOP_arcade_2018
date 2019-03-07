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
	void display() override;
	void abortDisplay() override;

	void setTitle(const std::string &) override;
	bool isActive() override;

	private:
	sf::RenderWindow *_win;
	bool _active;

};

#endif //ARCADE_SFMLGRAPHAPI_HPP
