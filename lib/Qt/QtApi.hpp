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
#include <QWidget>
#include <QKeyEvent>

namespace ui {

	class QtApi;

	class QtApiWindow : public QWidget {

		Q_OBJECT

		public:
		explicit QtApiWindow(QtApi *);

		protected:
		void closeEvent(QCloseEvent *event) override;

		void keyPressEvent(QKeyEvent *event) override;

		private:
		QtApi *_apiRef;
	};

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

		void setLastEvent(int);

		private:
		arcade::event::Key getEventKey(int qtEventCode);

		QtApiWindow *_win = nullptr;
		QApplication *_app = nullptr;
		int _lastEvent = -1;
	};
}

#endif //ARCADE_QTAPI_HPP
