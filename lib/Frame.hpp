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

		Frame() : _pixels(FRAMEWIDTH, std::vector<int>(FRAMEHEIGHT))
		{};

		~Frame() = default;

		void setElement(int key, UIRect rect)
		{
			_elements.insert({key, rect});
		}

		UIRect getElement(int key)
		{
			return (_elements.find(key)->second);
		}

		void setPixel(position pos, int key)
		{
			if (pos.x < 0 || pos.y < 0 || pos.x >= FRAMEWIDTH ||
			pos.y >= FRAMEHEIGHT)
				return; // TODO: throw an error
			_pixels[pos.x][pos.y] = key;
		}

		int getPixel(position pos)
		{
			if (pos.x < 0 || pos.y < 0 || pos.x >= FRAMEWIDTH ||
				pos.y >= FRAMEHEIGHT)
				return (-1); //TODO: throw an error
			return _pixels[pos.x][pos.y];
		}

		private:
		std::vector<std::vector<int>> _pixels;
		std::unordered_map<int, UIRect> _elements;
	};
}

#endif //ARCADE_FRAME_HPP
