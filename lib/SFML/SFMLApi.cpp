/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "../SFMLApi.hpp"

void ui::SFMLApi::init()
{
	_win = new sf::RenderWindow(sf::VideoMode(1280, 720), "Arcade");
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
	sf::Event event;

	if (_win == nullptr)
		return;
	_win->clear(sf::Color::Black);
	while (_win->pollEvent(event)) //TODO: handle events here
		if (event.type == sf::Event::Closed) {
			printf("close\n");
			return;
		}

}

void ui::SFMLApi::close()
{
	if (_win == nullptr)
		return;
	_win->close();
	delete _win;
	_win = nullptr;
}

int ui::SFMLApi::getEvent()
{
	return 0;
}

void ui::SFMLApi::drawText(ui::UIText text)
{
	sf::Text sfText;
	position pos = text.getPosition();

	sfText.setFont(*_font);
	sfText.setPosition(pos.x, pos.y);
	sfText.setString(text.getString());
	if (_win == nullptr)
		return;
	_win->draw(sfText);
}

void ui::SFMLApi::drawRect(ui::UIRect rect)
{
	sf::RectangleShape sfRect;
	sf::Texture *sfTexture;
	position pos = rect.getPosition();
	size size = rect.getSize();
	color bgColor = rect.getBackgroundColor();
	color bdColor = rect.getBorderColor();

	sfRect.setPosition(pos.x, pos.y);
	sfRect.setSize(sf::Vector2f(size.width, size.height));
	if (rect.getBackgroundImage().length() > 0) {
		sfTexture = getSFMLTexture(rect.getBackgroundImage());

		sfRect.setTexture(sfTexture);
	} else
		sfRect.setFillColor(getSFMLColor(bgColor));
	sfRect.setOutlineThickness(rect.getBorderWeight());
	sfRect.setOutlineColor(getSFMLColor(bdColor));
	if (_win == nullptr)
		return;
	_win->draw(sfRect);
}

void ui::SFMLApi::drawFrame(ui::Frame frame)
{
	printf("SFML: drawFrame not implemented.\n");
}

void ui::SFMLApi::playSound(const std::string &string)
{
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

extern "C" ui::IApi *entryPoint()
{
	return new ui::SFMLApi();
}
