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
	noecho();
	cbreak();
	curs_set(0);
	init_pair(1, COLOR_RED, COLOR_RED);
	init_pair(2, COLOR_GREEN, COLOR_GREEN);
	init_pair(3, 9, COLOR_BLACK);
	init_pair(4, 9, COLOR_GREEN);
}

void ui::NcursesApi::render()
{
	_lastEvent = getch();
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
	short colorId = getColorPair(text.getColor(), text.getBackgroundColor());

	attron(COLOR_PAIR(colorId));
	mvprintw(text.getPosition().y, text.getPosition().x * 2, text.getString().c_str());
	attroff(COLOR_PAIR(colorId));
}

void ui::NcursesApi::drawRect(ui::UIRect rect)
{
	short bgColorId = getColorPair(rect.getBackgroundColor(), rect.getBackgroundColor());
	short bdColorId = getColorPair(rect.getBorderColor(), rect.getBorderColor());

	for (int y = rect.getPosition().y; y < rect.getSize().height; y++) {
		for (int x = rect.getPosition().x; x < rect.getSize().width * 2; x += 2) {
			attron(COLOR_PAIR(y < rect.getBorderWeight() || y >= rect.getSize().height - rect.getBorderWeight() ? bdColorId : x < rect.getBorderWeight() * 2 || x >= rect.getSize().width * 2 - rect.getBorderWeight() * 2 ? bdColorId : bgColorId));
			mvprintw(y, x, " ");
			mvprintw(y, x+1, " ");
			attroff(COLOR_PAIR(y < rect.getBorderWeight() || y >= rect.getSize().height - rect.getBorderWeight() ? bdColorId : x < rect.getBorderWeight() * 2 || x >= rect.getSize().width * 2 - rect.getBorderWeight() * 2 ? bdColorId : bgColorId));
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

void ui::NcursesApi::initColor(short id, ui::color color)
{
	init_color(id,
		static_cast<short>((1000/255) * color.r),
		static_cast<short>((1000/255) * color.g),
		static_cast<short>((1000/255) * color.b));
}

short ui::NcursesApi::getColorPair(ui::color fgColor, ui::color bgColor)
{
	static short lastColorId = 9;
	static short lastPairId = 0;

	for (color_asset asset : _colorAssets) {
		if (asset.fgColor.b == fgColor.b && asset.fgColor.g == fgColor.g && asset.fgColor.r == fgColor.r &&
		asset.bgColor.b == bgColor.b && asset.bgColor.g == bgColor.g && asset.bgColor.r == bgColor.r)
			return asset.pairNb;
	}
	lastColorId++;
	initColor(lastColorId, fgColor);
	lastColorId++;
	initColor(lastColorId, bgColor);
	lastPairId++;
	init_pair(lastPairId, lastColorId - (short)1, lastColorId);
	_colorAssets.emplace_back((color_asset){fgColor, bgColor, lastPairId});
	return lastPairId;
}

extern "C" ui::IApi *entryPoint()
{
	return new ui::NcursesApi();
}
