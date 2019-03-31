/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_IELEMENT_HPP
#define ARCADE_IELEMENT_HPP

#include "UIExceptions.hpp"
#include <string>

namespace ui {

	struct position {
		int x;
		int y;
	};

	struct size {
		int width;
		int height;
	};

	struct color {
		int r;
		int g;
		int b;
	};

	class IElement {

		public:

		//POSITION
//		virtual ~IElement() = 0;

		virtual void setPosition(ui::position) = 0;
		virtual ui::position getPosition() const = 0;

		//SIZE

		virtual void setSize(ui::size) = 0;
		virtual ui::size getSize() const = 0;

		//BACKGROUND

		virtual void setBackgroundColor(ui::color) = 0;
		virtual ui::color getBackgroundColor() const = 0;
		virtual void setBackgroundImage(std::string) = 0;
		virtual std::string getBackgroundImage() const = 0;

		//BORDERS

		virtual void setBorders(int weight, ui::color) = 0;
		virtual void setBorderColor(ui::color) = 0;
		virtual ui::color getBorderColor() const = 0;
		virtual void setBorderWeight(int) = 0;
		virtual int getBorderWeight() const = 0;
	};

}

#endif //ARCADE_IELEMENT_HPP
