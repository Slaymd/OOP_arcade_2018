/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_UIRECT_HPP
#define ARCADE_UIRECT_HPP

#include "AElement.hpp"

namespace ui {
	class UIRect : public AElement {

		public:
		UIRect(position pos, size size) : AElement(pos, size)
		{
			setBackgroundColor({200, 200, 200});
		}

		~UIRect() = default;
	};
}

#endif //ARCADE_UIRECT_HPP
