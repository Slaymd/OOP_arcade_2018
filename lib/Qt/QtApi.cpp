/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include <QMainWindow>
#include "QtApi.hpp"

/*
 * EVENTS
 */

static const arcade::event::event_t _events[] = {
	{arcade::event::Key::A, Qt::Key::Key_A},
	{arcade::event::Key::B, Qt::Key::Key_B},
	{arcade::event::Key::C, Qt::Key::Key_C},
	{arcade::event::Key::D, Qt::Key::Key_D},
	{arcade::event::Key::E, Qt::Key::Key_E},
	{arcade::event::Key::F, Qt::Key::Key_F},
	{arcade::event::Key::G, Qt::Key::Key_G},
	{arcade::event::Key::H, Qt::Key::Key_H},
	{arcade::event::Key::I, Qt::Key::Key_I},
	{arcade::event::Key::J, Qt::Key::Key_J},
	{arcade::event::Key::K, Qt::Key::Key_K},
	{arcade::event::Key::L, Qt::Key::Key_L},
	{arcade::event::Key::M, Qt::Key::Key_M},
	{arcade::event::Key::N, Qt::Key::Key_N},
	{arcade::event::Key::O, Qt::Key::Key_O},
	{arcade::event::Key::P, Qt::Key::Key_P},
	{arcade::event::Key::Q, Qt::Key::Key_Q},
	{arcade::event::Key::R, Qt::Key::Key_R},
	{arcade::event::Key::S, Qt::Key::Key_S},
	{arcade::event::Key::T, Qt::Key::Key_T},
	{arcade::event::Key::U, Qt::Key::Key_U},
	{arcade::event::Key::V, Qt::Key::Key_V},
	{arcade::event::Key::W, Qt::Key::Key_W},
	{arcade::event::Key::X, Qt::Key::Key_X},
	{arcade::event::Key::Y, Qt::Key::Key_Y},
	{arcade::event::Key::Z, Qt::Key::Key_Z},
	{arcade::event::Key::ARROW_DOWN, Qt::Key::Key_Down},
	{arcade::event::Key::ARROW_UP, Qt::Key::Key_Up},
	{arcade::event::Key::ARROW_LEFT, Qt::Key::Key_Left},
	{arcade::event::Key::ARROW_RIGHT, Qt::Key::Key_Right},
	{arcade::event::Key::TAB, Qt::Key::Key_Tab},
	{arcade::event::Key::ENTER, Qt::Key::Key_Return},
	{arcade::event::Key::SPACE, Qt::Key::Key_Space},
	{arcade::event::Key::BACKSPACE, Qt::Key::Key_Backspace},
	{arcade::event::Key::ESCAPE, Qt::Key::Key_Escape},
	{arcade::event::Key::UNKNOWN, -1}
};

/*
 * MAIN FUNCTIONS
 */

void ui::QtApi::init()
{
	int argc = 0;
	char *argv[] = {};

	_isActive = true;

	printf("Qt init\n");

	if (_app == nullptr)
		_app = new QApplication(argc, argv);

	_win = new QtApiWindow(this);
	_win->show();
}

void ui::QtApi::render()
{
	if (!_isActive)
		return;
	_win->update();
	try {
		qApp->processEvents();
	} catch (...) {
		//bad alloc
	}
}

void ui::QtApi::clean()
{
}

void ui::QtApi::close()
{
	if (!_isActive)
		return;
	printf("Qt close\n");
	_isActive = false;
	_win->close();
	qApp->closingDown();
	delete _app;
	delete _win;
	_app = nullptr;
	_win = nullptr;
	_lastEvent = -1;
}

int ui::QtApi::getEvent()
{
	int lastEvent = _lastEvent;
	_lastEvent = -1;
	return lastEvent;
}

void ui::QtApi::drawText(ui::UIText text)
{
	if (!_isActive)
		return;
	_win->addText(text);
}

void ui::QtApi::drawRect(ui::UIRect rect)
{
	if (!_isActive)
		return;
	_win->addRect(rect);
}

void ui::QtApi::drawFrame(ui::Frame frame)
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

void ui::QtApi::playSound(const std::string &string)
{
	(void)string;
	//QSound::play(string.c_str());
}

void ui::QtApi::setTitle(const std::string &string)
{
	if (!_isActive)
		return;
	_win->setWindowTitle(string.c_str());
}

bool ui::QtApi::isActive()
{
	return _isActive;
}

/*
 * UTILS
 */

void ui::QtApi::setLastEvent(int e)
{
	if (_lastEvent != -1)
		return;
	_lastEvent = getEventKey(e);
}

arcade::event::Key ui::QtApi::getEventKey(int qtEventCode)
{
	for (int i = 0; _events[i].base != -1; i++) {
		if (_events[i].base == qtEventCode)
			return (_events[i].key);
	}
	return (arcade::event::UNKNOWN);
}

extern "C" ui::QtApi *entryPoint()
{
	return new ui::QtApi();
}
