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
#include <QPainter>
#include <unordered_map>

namespace ui {

	class QtApi;

	class QtApiWindow : public QWidget {

		Q_OBJECT

		public:
		explicit QtApiWindow(QtApi *);

		void addRect(UIRect);
		void addText(UIText);

		protected:
		void closeEvent(QCloseEvent *event) override;

		void paintEvent(QPaintEvent *event) override;

		void keyPressEvent(QKeyEvent *event) override;

		private:
		QColor getQtColor(ui::color);
		void displayRect(QPainter &, UIRect);
		void displayText(QPainter &, UIText);

		std::unordered_map<int, UIRect> _rects;
		std::unordered_map<int, UIText> _texts;
		int _lastIndex = 0;
		QtApi *_apiRef = nullptr;
		int _scale = 10;
	};

	class QtApi : public IApi {

		public:
		void init() override;

		void render() override;

		void clean() override;

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
		arcade::event::Key getEventKey(int);

		QtApiWindow *_win = nullptr;
		QApplication *_app = nullptr;
		int _lastEvent = -1;
		bool _isActive = false;
	};
}

#endif //ARCADE_QTAPI_HPP
