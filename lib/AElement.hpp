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
		AElement(position pos, size size) : _pos(pos), _size(size)
		{}
		~AElement() = default;

		void setPosition(position pos) override { _pos = pos; }
		position getPosition() const override { return _pos; }

		void setSize(size size) override { _size = size; }
		size getSize() const override { return _size; }

		void setBackgroundColor(color color) override { _backgroundColor = color; }
		color getBackgroundColor() const override { return _backgroundColor; }
		void setBackgroundImage(std::string string) override { _backgroundImage = string; }
		std::string getBackgroundImage() const override { return _backgroundImage; }

		void setBorders(int weight, color color) override { _borderWeight = weight; _borderColor = color; }
		void setBorderColor(color color) override { _borderColor = color; }
		color getBorderColor() const override { return _borderColor; }
		void setBorderWeight(int weight) override { _borderWeight = weight; }
		int getBorderWeight() const override { return _borderWeight; }

		private:
		position _pos = {0, 0};
		size _size = {0, 0};
		color _backgroundColor = {0, 0, 0};
		std::string _backgroundImage = "";
		int _borderWeight = 0;
		color _borderColor = {0, 0, 0};
	};

}

#endif //ARCADE_AELEMENT_HPP
