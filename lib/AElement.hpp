/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_AELEMENT_HPP
#define ARCADE_AELEMENT_HPP

#include "IElement.hpp"

namespace ui {

	class AElement : public IElement {

		public:
		AElement(position pos, size size) : _pos(pos), _size(size), _borderWeight(0)
		{
		}
		~AElement() = default;

		void setPosition(position pos) override { _pos = pos; }
		position getPosition() override { return _pos; }

		void setSize(size size) override { _size = size; }
		size getSize() override { return _size; }

		void setBackgroundColor(color color) override { _backgroundColor = color; }
		color getBackgroundColor() override { return _backgroundColor; }
		void setBackgroundImage(std::string string) override { _backgroundImage = string; }
		std::string getBackgroundImage() override { return _backgroundImage; }

		void setBorders(int weight, color color) override { _borderWeight = weight; _borderColor = color; }
		void setBorderColor(color color) override { _borderColor = color; }
		color getBorderColor() override { return _borderColor; }
		void setBorderWeight(int weight) override { _borderWeight = weight; }
		int getBorderWeight() override { return _borderWeight; }

		private:
		position _pos;
		size _size;
		color _backgroundColor = {0, 0, 0};
		std::string _backgroundImage = "";
		int _borderWeight;
		color _borderColor = {0, 0, 0};
	};

}

#endif //ARCADE_AELEMENT_HPP
