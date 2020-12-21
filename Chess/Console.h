#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Console {
	std::vector<sf::Sprite> pieceSprites;
	std::vector<sf::Text> messages;

	const int baseFontSize = 22;
	const sf::Color baseColor = sf::Color(117, 36, 219);
	int consoleX, consoleY;

	sf::Font* font;
	sf::Texture* spriteSheet;

public:
	Console(int x, int y, sf::Texture *t, sf::Font *f, std::string titleMessage);
	void WriteMessage(std::string, bool, bool, sf::Color = sf::Color::Transparent ,int = -1);
	void Draw(sf::RenderWindow &window);

};

