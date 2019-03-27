/*
** EPITECH PROJECT, 2018
** OOP_arcade_2018
** File description:
** src/core/IApi.hpp
*/

#ifndef IAPI_HPP_
#define IAPI_HPP_

#include "IElement.hpp"
#include "UIText.hpp"
#include "UIRect.hpp"
#include "Frame.hpp"
#include "Events.hpp"

namespace ui {
	class IApi {

		public:
		~IApi() = default;

		virtual void init() = 0;

		virtual void render() = 0;

		virtual void clean() = 0;

		virtual void close() = 0;

		virtual int getEvent() = 0;

		virtual void drawText(ui::UIText text) = 0;

		virtual void drawRect(ui::UIRect rect) = 0;

		virtual void drawFrame(ui::Frame frame) = 0;

		virtual void playSound(const std::string &) = 0;

		virtual void setTitle(const std::string &) = 0;

		virtual bool isActive() = 0;
	};
}

#endif
