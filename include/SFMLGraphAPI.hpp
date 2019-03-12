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
#include <unordered_map>
#include <iostream>
#include <string>

class SFMLGraphAPI : public IGraphAPI {

    public :

	SFMLGraphAPI() = default;
	~SFMLGraphAPI() = default;

	void initDisplay(const std::string &) override;
	void display() override;
	void abortDisplay() override;
	void drawSquare(int x, int y, std::string color) override;
	void clear() override;


	void setTitle(const std::string &) override;
	bool isActive(sf::Event event) override;

	private:
	sf::RenderWindow *_win;
	bool _active;
    std::unordered_map<std::string, sf::Color> colorList = {
        {"Black", sf::Color::Black},
        {"Blue", sf::Color::Blue},
        {"Red", sf::Color::Red},
        {"Blue", sf::Color::Blue},
        {"Yellow", sf::Color::Yellow},
        {"White", sf::Color::White},
        {"Magenta", sf::Color::Magenta},
        {"Cyan", sf::Color::Cyan},
        {"Transparent", sf::Color::Transparent}
    };
};

#endif //ARCADE_SFMLGRAPHAPI_HPP
