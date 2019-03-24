/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/
#ifndef ARCADE_QTAPI_HPP
#define ARCADE_QTAPI_HPP

#include "IApi.hpp"
#include <QApplication>

namespace ui {

	class QtApi : public IApi {

		public:
		void init() override;

		void render() override;

		void clear() override;

		void close() override;

		int getEvent() override;

		void drawText(ui::UIText text) override;

		void drawRect(ui::UIRect rect) override;

		void drawFrame(ui::Frame frame) override;

		void playSound(const std::string &string) override;

		void setTitle(const std::string &string) override;

		bool isActive() override;

		private:
//		QApplication *_app = nullptr;
	};

}

#endif //ARCADE_QTAPI_HPP
