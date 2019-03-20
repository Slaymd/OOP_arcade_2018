/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "NcursesApi.hpp"

void ui::NcursesApi::init()
{
	initscr();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
}

void ui::NcursesApi::render()
{
	refresh();
}

void ui::NcursesApi::clear()
{
	//Doesnt exist in Ncurses
}

void ui::NcursesApi::close()
{
	init_color(COLOR_RED, 1000, 0, 0);
	init_color(COLOR_GREEN, 0, 1000, 0);
	endwin();
}

int ui::NcursesApi::getEvent()
{
	int lastEvent = _lastEvent;
	_lastEvent = 0;
	return lastEvent;
}

void ui::NcursesApi::drawText(ui::UIText text)
{
	(void)text;
//	printf("ncurses: drawText not implemented.\n");
}

//changeColor()
//{
//	can_change_color();
//}

void ui::NcursesApi::drawRect(ui::UIRect rect)
{
	size scaledSize = {rect.getSize().width / 10, rect.getSize().height / 20};
	color bgcolor = rect.getBackgroundColor();
	color bdcolor = rect.getBorderColor();
	init_color(COLOR_RED,
		static_cast<short>((1000/255) * bgcolor.r),
		static_cast<short>((1000/255) * bgcolor.g),
		static_cast<short>((1000/255) * bgcolor.b));
	init_color(COLOR_GREEN,
		static_cast<short>((1000/255) * bdcolor.r),
		static_cast<short>((1000/255) * bdcolor.g),
		static_cast<short>((1000/255) * bdcolor.b));

	for (int y = rect.getPosition().y; y < scaledSize.height; y++) {
		for (int x = rect.getPosition().x; x < scaledSize.width; x += 2) {
			attron(COLOR_PAIR(y < rect.getBorderWeight() || y >= scaledSize.height - rect.getBorderWeight() ? 2 : x < rect.getBorderWeight() || x >= scaledSize.width - rect.getBorderWeight() * 2 ? 2 : 1));
			mvprintw(y, x, " ");
			mvprintw(y, x+1, " ");
			attroff(COLOR_PAIR(1));
			attroff(COLOR_PAIR(2));
		}
	}
}

void ui::NcursesApi::drawFrame(ui::Frame frame)
{
	(void)frame;
	printf("ncurses: drawFrame not implemented.\n");
}

void ui::NcursesApi::playSound(const std::string &string)
{
	(void)string;
	printf("ncurses: playSound not implemented.\n");
}

void ui::NcursesApi::setTitle(const std::string &string)
{
	(void)string;
	printf("ncurses: setTitle not implemented.\n");
}

bool ui::NcursesApi::isActive()
{
	return false;
}

extern "C" ui::IApi *entryPoint()
{
	return new ui::NcursesApi();
}
