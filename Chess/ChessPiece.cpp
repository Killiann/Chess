#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

//constructors
ChessPiece::ChessPiece(int pieceId, int nx, int ny, bool white, sf::Texture *t, Console* c) : id(pieceId), x(nx), y(ny), isWhite(white), texture(t), console(c) {
	sprite.setTexture(*texture);	
	float scaleX = tileWidth / ((float)texture->getSize().x / 6);
	float scaleY = tileWidth / ((float)texture->getSize().y / 2);	
	sprite.setScale(sf::Vector2f(scaleX, scaleY));
	sprite.setPosition(sf::Vector2f(x * tileWidth, y * tileWidth));
}

Pawn::Pawn(int pieceId, int nx, int ny, bool white, sf::Texture *t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "Pawn";
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 5, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 5, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Rook::Rook(int pieceId, int nx, int ny, bool white, sf::Texture* t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "Rook";
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 4, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 4, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Knight::Knight(int pieceId, int nx, int ny, bool white, sf::Texture* t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "Knight";
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 3, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 3, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Bishop::Bishop(int pieceId, int nx, int ny, bool white, sf::Texture* t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "Bishop";
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 2, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 2, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Queen::Queen(int pieceId, int nx, int ny, bool white, sf::Texture* t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "Queen";
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6), 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6), t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

King::King(int pieceId, int nx, int ny, bool white, sf::Texture* t, Console* c) : ChessPiece(pieceId, nx, ny, white, t, c) {
	pieceName = "King";
	if (isWhite)sprite.setTextureRect(sf::IntRect(0, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect(0, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

void ChessPiece::draw(sf::RenderWindow &window) {
	if(isAlive) window.draw(sprite);
}

void ChessPiece::kill() {
	isAlive = false;
	x = -1;
	y = -1;
}

void ChessPiece::move(int nx, int ny, int (&pieceGrid)[8][8], std::vector<ChessPiece*> &pieces) {
	//remove old position
	pieceGrid[y][x] = -1;
	if (pieceGrid[ny][nx] != -1)
		pieces[pieceGrid[ny][nx]]->kill();

	std::string output;
	if (this->isWhite) output += "White "; else output += "Black ";
	output += (pieceName + " " + (char)('a' + x) + std::to_string(1 + y) + " -> ");

	x = nx;
	y = ny;
	pieceGrid[y][x] = id;

	output += (char)('a' + x) + std::to_string(1 + y);
	console->WriteMessage(output, false, false);

	sprite.setPosition(sf::Vector2f(x * tileWidth, y * tileWidth));
	++moveCount;	
}

//show moves
void Pawn::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	int moves[8][8] = {};
	if (moveCount == 0) {		
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else 
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y-1 != -1) availableMoves[y - 1][x] = 1; else if(!isWhite && y+1 != 8) availableMoves[y+1][x] = 1;
}

void Rook::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	for (int c = 0; c < 8; ++c) {
		if(c != this->y)availableMoves[c][this->x] = 1;
		if(c != this->x)availableMoves[this->y][c] = 1;
	}
}


void Knight::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	for (int i = -1; i <= 1; i+=2) {
		if (this->y + i >= 0 && this->y + i < 8 && this->x + 2 < 8)availableMoves[this->y + i][this->x + 2] = 1;
		if (this->y + i >= 0 && this->y + i < 8 && this->x - 2 >= 0)availableMoves[this->y + i][this->x - 2] = 1;
		if (this->x + i >= 0 && this->x + i < 8 && this->y + 2 < 8)availableMoves[this->y + 2][this->x + i] = 1;
		if (this->x + i >= 0 && this->x + i < 8 && this->y - 2 >= 0)availableMoves[this->y - 2][this->x + i] = 1;
	}
}

void Bishop::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	for (int i = 1; i < 8; ++i) {
		if (this->y + i < 8 && this->x + i < 8)availableMoves[this->y + i][this->x + i] = 1;
		if (this->y - i >= 0 && this->x - i >= 0)availableMoves[this->y - i][this->x - i] = 1;
		if (this->y - i >= 0 && this->x + i < 8) availableMoves[this->y - i][this->x + i] = 1;
		if (this->y + i < 8 && this->x - i >= 0)availableMoves[this->y + i][this->x - i] = 1;
	}
}

void Queen::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {	
	for (int i = 0; i < 8; ++i) {
		availableMoves[i][this->x] = 1;
		availableMoves[this->y][i] = 1;
		if (this->y + i < 8 && this->x + i < 8)availableMoves[this->y + i][this->x + i] = 1;
		if (this->y - i >= 0 && this->x - i >= 0)availableMoves[this->y - i][this->x - i] = 1;
		if (this->y - i >= 0 && this->x + i < 8) availableMoves[this->y - i][this->x + i] = 1;
		if (this->y + i < 8 && this->x - i >= 0)availableMoves[this->y + i][this->x - i] = 1;
		availableMoves[this->y][this->x] = 0;
	}
}

void King::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			int newX = this->x - 1 + i;
			int newY = this->y - 1 + j;
			if(newX != this->x || newY != this->y)
				if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8)
					availableMoves[newY][newX] = 1;
		}
	}
}
