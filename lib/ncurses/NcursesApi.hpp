/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_NCURSESAPI_HPP
#define ARCADE_NCURSESAPI_HPP

#include "IApi.hpp"
#include <ncurses.h>

namespace ui {

	class NcursesApi : public IApi {

		struct color_asset {
			color fgColor;
			color bgColor;
			short pairNb;
		};

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
		arcade::event::Key getEventKey(int);
		short getColorPair(color fgColor, color bgColor);
		void initColor(short, color);

		std::vector<color_asset> _colorAssets;
	};

}

#endif //ARCADE_NCURSESAPI_HPP
