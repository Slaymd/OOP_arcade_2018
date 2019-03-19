/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_SFMLAPI_HPP
#define ARCADE_SFMLAPI_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "IApi.hpp"

namespace ui {
	class SFMLApi : public IApi {

		public:
		void init(void) override;

		void render(void) override;

		void clear(void) override;

		void close(void) override;

		int getEvent(void) override;

		void drawText(ui::UIText text) override;

		void drawRect(ui::UIRect rect) override;

		void drawFrame(ui::Frame frame) override;

		void playSound(const std::string &string) override;

		void setTitle(const std::string &string) override;

		bool isActive(void) override;

		private:
		sf::Texture *getSFMLTexture(const std::string &);
		sf::Color getSFMLColor(color);

		sf::RenderWindow *_win = nullptr;
		sf::Font *_font = nullptr;
		std::unordered_map<std::string, sf::Texture> _assets;
		int _lastEvent = 0;
	};
}

#endif //ARCADE_SFMLAPI_HPP
