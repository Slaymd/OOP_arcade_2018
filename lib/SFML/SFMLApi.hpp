/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_SFMLAPI_HPP
#define ARCADE_SFMLAPI_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include "IApi.hpp"

namespace ui {
	class SFMLApi : public IApi {

		public:
		void init(void) override;

		void render(void) override;

		void clean(void) override;

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
		arcade::event::Key getEventKey(int);

		sf::RenderWindow *_win = nullptr;
		sf::Font *_font = nullptr;
		// sf::SoundBuffer *_soundBuffer = nullptr;
		// sf::Sound *_sound = nullptr;
		std::unordered_map<std::string, sf::Texture> _assets;
		int _scale = 20;
		bool _isActive = true;
	};
}

#endif //ARCADE_SFMLAPI_HPP
