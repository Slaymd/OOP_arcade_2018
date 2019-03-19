/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_FRAME_HPP
#define ARCADE_FRAME_HPP

#include <vector>
#include "IElement.hpp"

namespace ui {

	class Frame {

		public:
		Frame() = default;
		~Frame() = default;

		private:
//		int _pixels[500][500]; //TODO: decide size
		std::vector<IElement *> _elements;
	};

}

#endif //ARCADE_FRAME_HPP
