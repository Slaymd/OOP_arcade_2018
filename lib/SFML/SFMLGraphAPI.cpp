/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Maxime
*/

#include "../../include/SFMLGraphAPI.hpp"

extern "C" {
	ui::IGraphAPI *getGraphAPI() {
		return (new ui::SFMLGraphAPI());
	}
}

void ui::SFMLGraphAPI::initDisplay(const std::string &title)
{
	printf("initDisplay\n");
	_win = new sf::RenderWindow(sf::VideoMode(1280, 720), title);
	_win->setFramerateLimit(60);
	_win->setTitle("test");
	_active = true;
}

void ui::SFMLGraphAPI::clear()
{
	sf::Event event;

	if (!_active)
		return;
	while (_win->pollEvent(event)) //TODO: handle events here
		if (event.type == sf::Event::Closed) {
			abortDisplay();
			return;
		}
	_win->clear(sf::Color::Black);
}

void ui::SFMLGraphAPI::display()
{
	if (!_active)
		return;
	_win->display();
}

void ui::SFMLGraphAPI::abortDisplay()
{
	if (!_active)
		return;
	_win->close();
	delete _win;
	_active = false;
}

//void ui::SFMLGraphAPI::drawSquare(int x, int y, std::string color)
//{
//	sf::Color colorSfml = colorList[color];
//	sf::RectangleShape rectangle(sf::Vector2f(x, y));
//	rectangle.setFillColor(colorSfml);
//	_win->draw(rectangle);
//}

bool ui::SFMLGraphAPI::isActive()
{
	return _active;
}

void ui::SFMLGraphAPI::setTitle(const std::string &title)
{
	if (!_active)
		return;
	_win->setTitle(title);
}

void ui::SFMLGraphAPI::drawRect(ui::position position, ui::size size,
	ui::rect_attributes attributes
)
{
	sf::Texture *texture = nullptr;
	sf::RectangleShape rectangle = sf::RectangleShape(sf::Vector2f((float)
		size.width, (float)size.height));

	if (!_active)
		return;
	rectangle.setPosition(position.x, position.y);
	if (!attributes.imagePath.empty()) {
		texture = getSFMLTexture(attributes.imagePath);
		if (texture == nullptr) {
			rectangle.setFillColor(getSFMLColor(attributes.backgroundColor));
		} else
			rectangle.setTexture(texture, true);
	} else
		rectangle.setFillColor(getSFMLColor(attributes.backgroundColor));
	_win->draw(rectangle);
}

void ui::SFMLGraphAPI::drawText(ui::position position1, std::string string,
	ui::color color1, ui::color color2
)
{
	if (!_active)
		return;
	(void)position1;
	(void)string;
	(void)color1;
	(void)color2;
}

void ui::SFMLGraphAPI::drawFrame(int **frame,
	std::vector<ui::rect_attributes> attributes
)
{
	if (!_active)
		return;
	printf("drawFrame\n");
	for (int y = 0; frame[y] != nullptr; y++) {
		printf("y: %d\n", y);
		for (int x = 0; frame[y][x] != -1; x++) { //TODO: NEEDS TO GIVE SIZE OF EACH !!
			printf("x: %d\n", frame[y][x]);
			if (frame[y][x] != 0)
				drawRect({x * 50, y * 50}, {50, 50}, attributes[frame[y][x] - 1]);
		}
	}
}

void ui::SFMLGraphAPI::playSound(const std::string &string)
{
	if (!_active)
		return;
	printf("WARN! playSound: not implemented but used !\n");
	(void)string;
}

sf::Color ui::SFMLGraphAPI::getSFMLColor(const ui::color &color)
{
//	return _colors[color];
	switch (color) {
	case WHITE:
		return sf::Color::White;
	case BLUE:
		return sf::Color::Blue;
	case RED:
		return sf::Color::Red;
	default:
		return sf::Color::Black;
	}
}

sf::Texture *ui::SFMLGraphAPI::getSFMLTexture(const std::string &path)
{
	if (_assets.find(path) == _assets.end()) {
		sf::Texture texture;

		if (!texture.loadFromFile(path))
			return nullptr;
		_assets[path] = texture;
	}
	return &_assets[path];
}
