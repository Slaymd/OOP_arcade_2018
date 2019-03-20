/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_NCURSESAPI_HPP
#define ARCADE_NCURSESAPI_HPP

#include "IApi.hpp"
#include <ncurses.h>

namespace ui {

	class NcursesApi : public IApi {

		public:
		void init(void) override;

		void render(void) override;

		void clear(void) override;

		void close(void) override;

		int getEvent(void) override;

		void drawText(ui::UIText text) override;

		void drawRect(ui::UIRect rect) override;

		void drawFrame(ui::Frame frame) override;

		void playSound(const std::string &string) override;

		void setTitle(const std::string &string) override;

		bool isActive(void) override;

		private:
		int _lastEvent = 0;
	};

}

#endif //ARCADE_NCURSESAPI_HPP
