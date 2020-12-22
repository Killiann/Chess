#include "Console.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

Console::Console(int nx, int ny, sf::Texture* t, sf::Font *f, std::string titleMessage) : consoleX(nx), consoleY(ny), spriteSheet(t), font(f){
	
	for (int j = 0; j < 2; ++j) {
		for (int i = 0; i < 6; ++i) {
			sf::Sprite tempSprite;

			tempSprite.setTexture(*spriteSheet);
			float textureW = (float)spriteSheet->getSize().x;
			float textureH = (float)spriteSheet->getSize().y;

			tempSprite.setTextureRect(sf::IntRect((textureW / 6) * i, (textureH / 2) * j, (textureW / 6), (textureH / 2)));

			float scaleX = (float)baseFontSize / (textureW / 6);
			float scaleY = (float)baseFontSize / (textureH / 2);
			
			tempSprite.setScale(sf::Vector2f(scaleX, scaleY));
			
			pieceSprites.push_back(tempSprite);
		}
	}

	sf::Text tm;
	tm.setFont(*font);
	tm.setCharacterSize(25);
	tm.setStyle(tm.Underlined);
	tm.setString(titleMessage);
	tm.setFillColor(baseColor);
	messages.push_back(tm);
}

void Console::WriteMessage(std::string message, bool underLined, bool italics, sf::Color color, int fontSize) {
	int fs = fontSize;
	if (fs == -1) fs = baseFontSize;

	sf::Color c = color;
	if (c == sf::Color::Transparent) c = baseColor;

	sf::Text textItem;
	textItem.setFont(*font);
	textItem.setCharacterSize(fs);
	textItem.setString(message);
	textItem.setFillColor(c);
	if (underLined) textItem.setStyle(textItem.Underlined);
	if (italics)	textItem.setStyle(textItem.Italic);
	
	messages.push_back(textItem);
}

void Console::Draw(sf::RenderWindow &window) {
	int yOffset = 0;
	for (sf::Text m : messages) {
		m.setPosition(consoleX + 5, consoleY + 5 + yOffset);
		yOffset += m.getCharacterSize() + 4;
		window.draw(m);
	}
}
