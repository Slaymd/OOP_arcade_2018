/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_UITEXT_HPP
#define ARCADE_UITEXT_HPP

#include "AElement.hpp"

namespace ui {
	class UIText : public AElement {

		public:
		UIText(position pos, std::string string) : AElement(pos, {0, 0}), _string(string)
		{
		}
		~UIText() = default;

		void setString(std::string string) { _string = string; }
		std::string getString() { return _string; }

		void setColor(color color) { _color = color; }
		color getColor() { return _color; }

		private:
		std::string _string;
		color _color;
	};
}

#endif //ARCADE_UITEXT_HPP
