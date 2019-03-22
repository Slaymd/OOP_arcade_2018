/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "NcursesApi.hpp"

/*
 * EVENTS
 */

static const arcade::event::event_t _events[] = {
	{arcade::event::Key::A, 97},
	{arcade::event::Key::B, 98},
	{arcade::event::Key::C, 99},
	{arcade::event::Key::D, 100},
	{arcade::event::Key::E, 101},
	{arcade::event::Key::F, 102},
	{arcade::event::Key::G, 103},
	{arcade::event::Key::H, 104},
	{arcade::event::Key::I, 105},
	{arcade::event::Key::J, 106},
	{arcade::event::Key::K, 107},
	{arcade::event::Key::L, 108},
	{arcade::event::Key::M, 109},
	{arcade::event::Key::N, 110},
	{arcade::event::Key::O, 111},
	{arcade::event::Key::P, 112},
	{arcade::event::Key::Q, 113},
	{arcade::event::Key::R, 114},
	{arcade::event::Key::S, 115},
	{arcade::event::Key::T, 116},
	{arcade::event::Key::U, 117},
	{arcade::event::Key::V, 118},
	{arcade::event::Key::W, 119},
	{arcade::event::Key::X, 120},
	{arcade::event::Key::Y, 121},
	{arcade::event::Key::Z, 122},
	{arcade::event::Key::ARROW_DOWN, KEY_DOWN},
	{arcade::event::Key::ARROW_UP, KEY_UP},
	{arcade::event::Key::ARROW_LEFT, KEY_LEFT},
	{arcade::event::Key::ARROW_RIGHT, KEY_RIGHT},
	{arcade::event::Key::ENTER, KEY_ENTER},
	{arcade::event::Key::SPACE, ' '},
	{arcade::event::Key::BACKSPACE, KEY_BACKSPACE},
	{arcade::event::Key::ESCAPE, 27},
	{arcade::event::Key::UNKNOWN, -1}
};

/*
 *      MAIN FUNCTIONS
 */

void ui::NcursesApi::init()
{
	initscr();
	if (!can_change_color() || !has_colors())
		throw std::exception();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	noecho();
	cbreak();
	curs_set(0);
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
	endwin();
}

int ui::NcursesApi::getEvent()
{
	return getEventKey(getch());
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

/*
 *      UTILS
 */

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

arcade::event::Key ui::NcursesApi::getEventKey(int ncursesEventCode)
{
	for (int i = 0; _events[i].base != -1; i++) {
		if (_events[i].base == ncursesEventCode)
			return (_events[i].key);
	}
	return (arcade::event::UNKNOWN);
}

extern "C" ui::IApi *entryPoint()
{
	return new ui::NcursesApi();
}
