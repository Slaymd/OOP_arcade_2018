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

		void setPosition(position pos) override;
		position getPosition() override;

		void setSize(size size) override;
		size getSize() override;

		void setBackgroundColor(color color) override;
		color getBackgroundColor() override;
		void setBackgroundImage(std::string string) override;
		std::string getBackgroundImage() override;

		void setBorders(int weight, color color) override;
		void setBorderColor(color color) override;
		color getBorderColor() override;
		void setBorderWeight(int weight) override;
		int getBorderWeight() override;

		private:
		position _pos;
		size _size;
		color _backgroundColor;
		std::string _backgroundImage;
		int _borderWeight;
		color _borderColor;
	};

}

#endif //ARCADE_AELEMENT_HPP
