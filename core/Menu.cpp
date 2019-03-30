/*
** EPITECH PROJECT, 2022
** arcade
** File description:
** Darius
*/

#include "Menu.hpp"

/*
 * BASE FUNCTIONS
 */

void Menu::init()
{
	_header = new ui::UIRect({0, 0}, {60, 3});
	_bg = new ui::UIRect({0, 3}, {60, 60});

	_header->setBackgroundColor({0, 0, 0});

	_lightColors = new std::vector<ui::color>({{116, 185, 255}, {255, 234, 167}, {162, 155, 254}, {85, 239, 196}, {250, 177, 160}});
	_darkColors = new std::vector<ui::color>({{0, 168, 255}, {140, 122, 230},{225, 177, 44}, {68, 189, 50}, {232, 65, 24}, {6, 82, 221}});
	_particles = new std::vector<ui::UIText>();

	_headerText = new ui::UIText({25, 1}, "Chargement ...");
	_headerText->setBackgroundColor({0, 0, 0});
	_headerText->setColor({255, 255, 255});

	_playerTab = new ui::UIRect({10, 10}, {40, 3});
	_playerTab->setBackgroundColor({0, 0, 0});
	_playerTab->setBorders(1, {255, 255, 255});

	_usernameText = new ui::UIText({12, 11}, "username:");
	_usernameText->setColor({255, 255, 255});
	_usernameText->setBackgroundColor({0, 0, 0});

	_usernameField = new ui::UIText({40, 11}, "_ _ _ _ _ _");
	_usernameField->setColor({255, 255, 255});
	_usernameField->setBackgroundColor({0, 0, 0});

	_gamesTab = new ui::UIRect({10, 18}, {40, 5});
	_gamesTab->setBackgroundColor({0, 0, 0});
	_gamesTab->setBorders(1, {0, 0, 0});

	_graphicsTab = new ui::UIRect({10, 27}, {40, 5});
	_graphicsTab->setBackgroundColor({0, 0, 0});
	_graphicsTab->setBorders(1, {0, 0, 0});

	_highscoresText = new ui::UIText({11, 36}, "highscores:");
	_highscoresText->setBackgroundColor(_bgColor);
	_highscoresText->setColor({0, 0, 0});

	_welcomeTicks = 25;
	_tabIndex = 0;
}

void Menu::tick(int i)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	generateBackground();
	arcade::Engine::Graphic().clean();
	//Background
	arcade::Engine::Graphic().drawRect(*_header);
	arcade::Engine::Graphic().drawRect(*_bg);
	for (const auto &particle : *_particles)
		arcade::Engine::Graphic().drawText(particle);
	//Header
	if (_welcomeTicks == 0) {
		_headerText->setString("Menu");
		_headerText->setPosition({28, 1});
	}
	arcade::Engine::Graphic().drawText(*_headerText);
	//Tabs
	if (_welcomeTicks <= 0) {
		dispUserTab();
		dispGamesTab();
		dispGraphicsTab();
		dispHighscoresSection();
	}
	arcade::Engine::Graphic().render();
	eventHandler((arcade::event::Key)i);
	if (_welcomeTicks >= 0)
		_welcomeTicks--;
}

void Menu::close()
{
}

/*
 * DISPLAY
 */

void Menu::generateBackground()
{
	static int state = 0;
	static int bgIndex = 0;
	static int fgIndex = -1;

	if (state == 0) {
		bgIndex = randomBetween(0, (int)_lightColors->size());
		state = 30;
	}
	_bgColor = (*_lightColors)[bgIndex];
	_bg->setBackgroundColor(_bgColor);
	if (state % 15 == 0 || fgIndex == -1) {
		_particles->clear();
		fgIndex = randomBetween(0, (int)_darkColors->size());
		for (int i = 0; i < 20; i++) {
			ui::position pos = {randomBetween(0, 60),
				randomBetween(3, 60)};
			int pcRd = randomBetween(0, 3);
			ui::UIText text(pos, pcRd == 0 ? "*" : pcRd == 1 ? "." : "#");

			text.setBackgroundColor(_bgColor);
			text.setColor((*_darkColors)[fgIndex]);
			_particles->emplace_back(text);
		}
	}
	state--;
}

void Menu::dispUserTab()
{
	std::string realPlayerName = arcade::Engine::instance().getPlayerName();
	std::string UIPlayerName;

	for (int i = 0, oi = 0; i < 6; i++) {
		if (6 - i > (int)realPlayerName.size())
			UIPlayerName += "_ ";
		else {
			UIPlayerName += realPlayerName[oi];
			UIPlayerName += " ";
			oi++;
		}
	}
	if (_usernameFieldError)
		_playerTab->setBorders(1, {231, 76, 60});
	else if (_tabIndex == 0)
		_playerTab->setBorders(1, {255, 255, 255});
	else if (_tabIndex != 0)
		_playerTab->setBorders(1, {0, 0, 0});
	arcade::Engine::Graphic().drawRect(*_playerTab);
	arcade::Engine::Graphic().drawText(*_usernameText);
	_usernameField->setString(UIPlayerName);
	arcade::Engine::Graphic().drawText(*_usernameField);
	_usernameFieldError = false;
}

void Menu::dispGamesTab()
{
	if (_tabIndex == 1)
		_gamesTab->setBorders(1, {255, 255, 255});
	else
		_gamesTab->setBorders(1, {0, 0, 0});
	arcade::Engine::Graphic().drawRect(*_gamesTab);
	ui::UIText gameText({4, 20}, "");
	gameText.setBackgroundColor({0, 0, 0});
	int i = 0;
	for (auto const &game : arcade::Engine::instance().getGames()) {
		gameText.setPosition({gameText.getPosition().x + 8,
			gameText.getPosition().y});
		gameText.setString(game.name);
		if (_gameIndex == i)
			gameText.setColor({241, 196, 15});
		else
			gameText.setColor({189, 195, 199});
		arcade::Engine::Graphic().drawText(gameText);
		i++;
	}
}

void Menu::dispGraphicsTab()
{
	if (_tabIndex == 2)
		_graphicsTab->setBorders(1, {255, 255, 255});
	else
		_graphicsTab->setBorders(1, {0, 0, 0});
	arcade::Engine::Graphic().drawRect(*_graphicsTab);
	ui::UIText graphicText({4, 29}, "");
	graphicText.setBackgroundColor({0, 0, 0});
	int i = 0;
	for (auto const &lib : arcade::Engine::instance().getGraphLibs()) {
		graphicText.setPosition({graphicText.getPosition().x + 8,
			graphicText.getPosition().y});
		graphicText.setString(lib.name);
		if (_graphicIndex == i)
			graphicText.setColor({241, 196, 15});
		else
			graphicText.setColor({189, 195, 199});
		arcade::Engine::Graphic().drawText(graphicText);
		i++;
	}
}

void Menu::dispHighscoresSection()
{
	std::string gameName = arcade::Engine::instance()
		.getGames()[_gameIndex].name;
	ui::UIText text({12, 39}, "");
	int i = 0;

	text.setColor({0, 0, 0});
	text.setBackgroundColor(_bgColor);
	_highscoresText->setString(gameName + " highscores:");
	_highscoresText->setBackgroundColor(_bgColor);
	arcade::Engine::Graphic().drawText(*_highscoresText);
	for (const auto &player : arcade::Engine::instance()
	.getRanking()[gameName]) {
		if (i == 0)
			text.setColor({183, 21, 64});
		else
			text.setColor({52, 73, 94});
		text.setString(std::to_string(i + 1) + ". " + player.name +
		" : " + std::to_string(player.score));
		arcade::Engine::Graphic().drawText(text);
		text.setPosition({text.getPosition().x,
			text.getPosition().y + 2});
		i++;
		if (i == 4)
			break;
	}
}

/*
 * ACTIONS
 */

void Menu::eventHandler(arcade::event::Key key)
{
	std::string &playerName = arcade::Engine::instance().getPlayerName();
	if (key >= 'A' && key <= 'Z' && _tabIndex == 0 && _welcomeTicks <= 0) {
		if (playerName.size() < 6)
			playerName += (char)key;
		else
			_usernameFieldError = true;
	} else if (key == arcade::event::Key::BACKSPACE && !playerName.empty()
	&& _tabIndex == 0 && _welcomeTicks <= 0)
		playerName = playerName.substr(0, playerName.size() - 1);
	else if (key == arcade::event::Key::TAB) {
		if (!(_tabIndex == 0 && playerName.empty()))
			_tabIndex = _tabIndex == 2 ? 0 : _tabIndex + 1;
		else
			_usernameFieldError = true;
	} else
		selectsEventHandler(key);
}

void Menu::selectsEventHandler(arcade::event::Key key)
{
	if (key == arcade::event::Key::D && _tabIndex > 0) {
		_gameIndex = _tabIndex == 1 ? _gameIndex ==
			(int)arcade::Engine::instance().getGames().size() - 1
			? 0 : _gameIndex + 1 : _gameIndex;
		_graphicIndex = _tabIndex == 2 ? _graphicIndex ==
			(int)arcade::Engine::instance().getGraphLibs().size()
				- 1 ? 0 : _graphicIndex + 1 : _graphicIndex;
		arcade::Engine::Graphic().playSound("assets/mc_hit.wav");
	} else if (key == arcade::event::Key::Q && _tabIndex > 0) {
		_gameIndex = _tabIndex == 1 ? _gameIndex == 0
			? (int)arcade::Engine::instance().getGames().size()
			- 1 : _gameIndex - 1 : _gameIndex;
		_graphicIndex = _tabIndex == 2 ? _graphicIndex == 0
			? (int)arcade::Engine::instance().getGraphLibs().size()
			- 1 : _graphicIndex - 1 : _graphicIndex;
		arcade::Engine::Graphic().playSound("assets/mc_hit.wav");
	} else if (key == arcade::event::Key::ENTER && _tabIndex > 0) {
		if (_tabIndex == 1)
			arcade::Engine::instance().changeGame(arcade::Engine::
			instance().getGames()[_gameIndex].name);
		else if (_tabIndex == 2)
			arcade::Engine::instance().changeGraphLib(arcade::
			Engine::instance().getGraphLibs()[_graphicIndex].name);
	}
}

/*
 * UTILS
 */

int Menu::randomBetween(int a, int b)
{
	if (a + b == 0)
		throw arcade::EngineException("randomBetween: a + b = 0.");

	return (std::rand() % b + a);
}

void Menu::restart()
{
	init();
	close();
}
