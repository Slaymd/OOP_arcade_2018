/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_IGRAPHAPI_HPP
#define ARCADE_IGRAPHAPI_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <string>

namespace ui {

	enum color {
		BLACK = 0,
		RED = 1,
		GREEN = 2,
		YELLOW = 3,
		BLUE = 4,
		MAGENTA = 5,
		CYAN = 6,
		WHITE = 7
	};

	struct position {
		int x;
		int y;
	};

	struct size {
		int width;
		int height;
	};

	struct rect_attributes {
		ui::color backgroundColor;
		std::string imagePath;
	};

	class IGraphAPI {
		public:

		/*
		 * BASIC
		 */

		virtual void initDisplay(const std::string &) = 0;
		virtual void clear() = 0;
		virtual void display() = 0;
		virtual void abortDisplay() = 0;
		virtual int getKeyboard() = 0;

		/*
		 * DRAW
		 */

		virtual void drawText(ui::position, std::string, ui::color = WHITE, ui::color = BLACK) = 0;
		virtual void drawRect(ui::position, ui::size, ui::rect_attributes) = 0;
		virtual void drawFrame(int [3][3], std::vector<rect_attributes>) = 0;

		/*
		 * MISC
		 */

		virtual void playSound(const std::string &) = 0;
		virtual void setTitle(const std::string &) = 0;
		virtual bool isActive() = 0;
	};
}

extern "C" ui::IGraphAPI *getGraphAPI();

#endif //ARCADE_IGRAPHAPI_HPP
