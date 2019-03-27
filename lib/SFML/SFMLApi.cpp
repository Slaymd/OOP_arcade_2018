/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "SFMLApi.hpp"

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
	{arcade::event::Key::ARROW_DOWN, 74},
	{arcade::event::Key::ARROW_UP, 73},
	{arcade::event::Key::ARROW_LEFT, 71},
	{arcade::event::Key::ARROW_RIGHT, 72},
	{arcade::event::Key::ENTER, sf::Keyboard::Key::Return},
	{arcade::event::Key::SPACE, 32},
	{arcade::event::Key::BACKSPACE, 8},
	{arcade::event::Key::ESCAPE, 27},
	{arcade::event::Key::UNKNOWN, -1}
};

/*
 * MAIN FUNCTIONS
 */

void ui::SFMLApi::init()
{
	_win = new sf::RenderWindow(sf::VideoMode(FRAMEWIDTH * _scale, FRAMEHEIGHT * _scale), "Arcade");
	_win->setFramerateLimit(60);
	_font = new sf::Font();
	_font->loadFromFile("assets/UbuntuMono-B.ttf");
}

void ui::SFMLApi::render()
{
	if (_win == nullptr)
		return;
	_win->display();
}

void ui::SFMLApi::clear()
{
	if (_win == nullptr)
		return;
	_win->clear(sf::Color::Black);
}

void ui::SFMLApi::close()
{
	if (_win == nullptr)
		return;
	delete _font;
	_font = nullptr;
	_win->close();
	delete _win;
	_win = nullptr;
}

int ui::SFMLApi::getEvent()
{
	sf::Event event{};

	while (_win->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			return arcade::event::ESCAPE;
		if (event.type == sf::Event::KeyPressed)
			return getEventKey(event.key.code);
		if (event.type == sf::Event::TextEntered && event.text.unicode < 128)
			return getEventKey(event.text.unicode);
	}
	return arcade::event::UNKNOWN;
}

void ui::SFMLApi::drawText(ui::UIText text)
{
	sf::Text sfText;
	position pos = text.getPosition();

	sfText.setFont(*_font);
	sfText.setPosition(pos.x * _scale, pos.y * _scale);
	sfText.setString(text.getString());
	sfText.setFillColor(getSFMLColor(text.getColor()));
	if (_win == nullptr)
		return;
	_win->draw(sfText);
}

void ui::SFMLApi::drawRect(ui::UIRect rect)
{
	sf::RectangleShape sfRect;
	sf::Texture *sfTexture;
	position pos = { rect.getPosition().x * _scale, rect.getPosition().y * _scale };
	size size = { rect.getSize().width * _scale, rect.getSize().height * _scale };
	color bgColor = rect.getBackgroundColor();
	color bdColor = rect.getBorderColor();

	sfRect.setPosition(pos.x, pos.y);
	sfRect.setSize(sf::Vector2f(size.width, size.height));
	if (rect.getBackgroundImage().length() > 0) {
		sfTexture = getSFMLTexture(rect.getBackgroundImage());

		sfRect.setTexture(sfTexture);
	}
	else
		sfRect.setFillColor(getSFMLColor(bgColor));
	sfRect.setOutlineThickness(rect.getBorderWeight() * _scale);
	sfRect.setOutlineColor(getSFMLColor(bdColor));
	if (_win == nullptr)
		return;
	_win->draw(sfRect);
}

void ui::SFMLApi::drawFrame(ui::Frame frame)
{
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

void ui::SFMLApi::playSound(const std::string &string)
{
	(void)string;
	printf("SFML: playSound not implemented.\n");
}

void ui::SFMLApi::setTitle(const std::string &string)
{
	_win->setTitle(string);
}

bool ui::SFMLApi::isActive()
{
	return false;
}

/*
 *      UTILS
 */

sf::Texture *ui::SFMLApi::getSFMLTexture(const std::string &path)
{
	if (_assets.find(path) == _assets.end()) {
		sf::Texture texture;

		if (!texture.loadFromFile(path))
			return nullptr;
		_assets[path] = texture;
	}
	return &_assets[path];
}

sf::Color ui::SFMLApi::getSFMLColor(ui::color color)
{
	return {static_cast<sf::Uint8>(color.r),
		static_cast<sf::Uint8>(color.g),
		static_cast<sf::Uint8>(color.b)};
}

arcade::event::Key ui::SFMLApi::getEventKey(int sfmlEventCode)
{
	for (int i = 0; _events[i].base != -1; i++) {
		if (_events[i].base == sfmlEventCode)
			return (_events[i].key);
	}
	return (arcade::event::UNKNOWN);
}

extern "C" ui::IApi *entryPoint()
{
	return new ui::SFMLApi();
}
