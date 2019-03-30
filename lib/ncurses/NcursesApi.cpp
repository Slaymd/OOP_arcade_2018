/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include <unistd.h>
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
	{arcade::event::Key::TAB, '\t'},
	{arcade::event::Key::ENTER, 10},
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
	_isActive = true;
	if (!can_change_color() || !has_colors())
		throw std::exception();
	nodelay(stdscr, TRUE);
	keypad(stdscr, TRUE);
	start_color();
	noecho();
	cbreak();
	curs_set(0);
	refresh();
}

void ui::NcursesApi::render()
{
	if (!_isActive)
		return;
	refresh();
	usleep(50000);
}

void ui::NcursesApi::clean()
{
	clear();
}

void ui::NcursesApi::close()
{
	_isActive = false;
	curs_set(1);
	clear();
	endwin();
}

int ui::NcursesApi::getEvent()
{	if (!_isActive)
		return (-1);
	return getEventKey(getch());
}

void ui::NcursesApi::drawText(ui::UIText text)
{
	if (!_isActive)
		return;
	short colorId = getColorPair(text.getColor(), text.getBackgroundColor());

	attron(COLOR_PAIR(colorId));
	mvprintw(text.getPosition().y, text.getPosition().x * 2, text.getString().c_str());
	attroff(COLOR_PAIR(colorId));
}

void ui::NcursesApi::drawRect(ui::UIRect rect)
{
	if (!_isActive)
		return;
	short bgColorId = getColorPair(rect.getBackgroundColor(), rect.getBackgroundColor());
	short bdColorId = getColorPair(rect.getBorderColor(), rect.getBorderColor());
	position cursesPosition = {rect.getPosition().x * 2, rect.getPosition().y};
	size cursesSize = {rect.getSize().width * 2, rect.getSize().height};
	bool isBorder = false;

	for (int y = cursesPosition.y; y < cursesPosition.y + cursesSize.height; y++) {
		for (int x = cursesPosition.x; x < cursesPosition.x + cursesSize.width; x += 2) {
			isBorder = !(y >= cursesPosition.y + rect.getBorderWeight() && y < cursesPosition.y + cursesSize.height - rect.getBorderWeight()
							&& x >= cursesPosition.x + rect.getBorderWeight() * 2 && x < cursesPosition.x + cursesSize.width - rect.getBorderWeight() * 2);
			attron(COLOR_PAIR(isBorder ? bdColorId : bgColorId));
			mvprintw(y, x, " ");
			mvprintw(y, x+1, " ");
			attroff(COLOR_PAIR(isBorder ? bdColorId : bgColorId));
		}
	}
}

void ui::NcursesApi::drawFrame(ui::Frame frame)
{
	if (!_isActive)
		return;
	for (int y = 0; y < FRAMEHEIGHT; y++) {
		for (int x = 0; x < FRAMEWIDTH; x++) {
			if (frame.getPixel({x, y}) == 0)
				continue;
			UIRect rect = frame.getElement(frame.getPixel({x, y}));
			rect.setPosition({x, y});
			rect.setSize({1, 1});

			drawRect(rect);
		}
	}
}

void ui::NcursesApi::playSound(const std::string &string)
{
	(void)string;
}

void ui::NcursesApi::setTitle(const std::string &string)
{
	(void)string;
}

bool ui::NcursesApi::isActive()
{
	return _isActive;
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

	if (lastPairId == 256) {
		lastPairId = 0;
		lastColorId = 9;
	}
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
