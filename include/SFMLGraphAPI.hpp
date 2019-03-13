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

namespace ui {
	class SFMLGraphAPI : public IGraphAPI {

		public :
		SFMLGraphAPI() = default;
		~SFMLGraphAPI() = default;

		/*
		 * BASIC
		 */

		void initDisplay(const std::string &) override;
		void display() override;
		void abortDisplay() override;
		void clear() override;

		/*
		 * DRAW
		 */

		void drawRect(position position1, size size1,
			rect_attributes attributes
		) override;
		void drawText(position position1, std::string string,
			ui::color color1, ui::color color2
		) override;
		void drawFrame(int map[3][3], std::vector<rect_attributes> vector
		) override;

		/*
		 * MISC
		 */

		void playSound(const std::string &string) override;
		void setTitle(const std::string &) override;
		bool isActive() override;

		private:

		sf::Color getSFMLColor(const ui::color &);
		sf::Texture *getSFMLTexture(const std::string &);

		/*
		 * VALUES
		 */

		sf::RenderWindow *_win = nullptr;
		sf::Font *_font = nullptr;
		bool _active = false;

//		std::unordered_map<color, sf::Color> _colors = {
//			{BLACK, sf::Color::Black},
//			{BLUE, sf::Color::Blue},
//			{RED, sf::Color::Red},
//			{YELLOW, sf::Color::Yellow},
//			{WHITE, sf::Color::White},
//			{MAGENTA, sf::Color::Magenta},
//			{CYAN, sf::Color::Cyan},
//			{GREEN, sf::Color::Green}
//		};
		std::unordered_map<std::string, sf::Texture> _assets;
	};
}

#endif //ARCADE_SFMLGRAPHAPI_HPP
