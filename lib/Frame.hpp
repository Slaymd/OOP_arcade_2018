/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#ifndef ARCADE_FRAME_HPP
#define ARCADE_FRAME_HPP

#include "UIRect.hpp"
#include <vector>
#include <unordered_map>

#define FRAMEWIDTH 60
#define FRAMEHEIGHT 60

namespace ui {
	class Frame {
		public:

		Frame() : _pixels(FRAMEWIDTH, std::vector<int>(FRAMEHEIGHT, 0))
		{
			UIRect noRect({0, 0}, {20, 20});
			noRect.setBackgroundColor({0, 0, 0});
			setElement(0, noRect);
		};

		~Frame() = default;

		void setElement(int key, UIRect rect)
		{
			_elements.insert({key, rect});
		}

		UIRect getElement(int key)
		{
			if (_elements.find(key) == _elements.end())
				throw ui::UIException("Frame::getElement: "
			  "Element with key " + std::to_string(key)
			  + " not found.");

			return (_elements.find(key)->second);
		}

		void setPixel(position pos, int key)
		{
			if (pos.x < 0 || pos.y < 0 || pos.x >= FRAMEWIDTH ||
			pos.y >= FRAMEHEIGHT)
				throw ui::UIException("Frame::setPixel: "
			  "<position x=" + std::to_string(pos.x) + " y=" +
			  std::to_string(pos.y) + "> out of frame.");

			_pixels[pos.x][pos.y] = key;
		}

		int getPixel(position pos)
		{
			if (pos.x < 0 || pos.y < 0 || pos.x >= FRAMEWIDTH ||
				pos.y >= FRAMEHEIGHT)
				throw ui::UIException("Frame::getPixel: "
			  "<position x=" + std::to_string(pos.x) + " y=" +
			  std::to_string(pos.y) + "> out of frame.");
			return _pixels[pos.x][pos.y];
		}

		private:
		std::vector<std::vector<int>> _pixels;
		std::unordered_map<int, UIRect> _elements;
	};
}

#endif //ARCADE_FRAME_HPP
