#include "ChessPiece.h"
#include <SFML/Graphics.hpp>

//constructors
ChessPiece::ChessPiece(int pieceId, int nx, int ny, bool white, sf::Texture *t) : id(pieceId), x(nx), y(ny), isWhite(white), texture(t) {	
	sprite.setTexture(*texture);	
	float scaleX = tileWidth / ((float)texture->getSize().x / 6);
	float scaleY = tileWidth / ((float)texture->getSize().y / 2);	
	sprite.setScale(sf::Vector2f(scaleX, scaleY));
	sprite.setPosition(sf::Vector2f(x * tileWidth, y * tileWidth));
}

Pawn::Pawn(int pieceId, int nx, int ny, bool white, sf::Texture *t) : ChessPiece(pieceId, nx, ny, white, t) {
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 5, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 5, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Rook::Rook(int pieceId, int nx, int ny, bool white, sf::Texture* t) : ChessPiece(pieceId, nx, ny, white, t) {
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 4, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 4, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Knight::Knight(int pieceId, int nx, int ny, bool white, sf::Texture* t) : ChessPiece(pieceId, nx, ny, white, t) {
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 3, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 3, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Bishop::Bishop(int pieceId, int nx, int ny, bool white, sf::Texture* t) : ChessPiece(pieceId, nx, ny, white, t) {
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 2, 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6) * 2, t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

Queen::Queen(int pieceId, int nx, int ny, bool white, sf::Texture* t) : ChessPiece(pieceId, nx, ny, white, t) {
	if (isWhite)sprite.setTextureRect(sf::IntRect((t->getSize().x / 6), 0, t->getSize().x / 6, t->getSize().y / 2));
	else sprite.setTextureRect(sf::IntRect((t->getSize().x / 6), t->getSize().y / 2, t->getSize().x / 6, t->getSize().y / 2));
}

King::King(int pieceId, int nx, int ny, bool white, sf::Texture* t) : ChessPiece(pieceId, nx, ny, white, t) {
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

	x = nx;
	y = ny;
	pieceGrid[y][x] = id;

	sprite.setPosition(sf::Vector2f(x * tileWidth, y * tileWidth));
	++moveCount;
}

bool ChessPiece::canMove(int boardPieces[][8], int x, int y) {
	int pieceId = boardPieces[y][x];
	if (pieceId != 0) {
		if (isWhite) {
			if (pieceId > 15)
				return false;
			else return true;
		}
		else {
			if (pieceId < 16) return true;
			else return false;
		}
	}
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

	/*availableMoves = moves;*/
	/*for (int y = 0; y < 8; ++y)
		for (int x = 0; x < 8; ++x)
			if (moves[y][x] == 1)
				if (!canMove(boardPieces, x, y))
					moves[y][x] = 0;*/
}

void Rook::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	if (moveCount == 0) {
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y - 1 != -1) availableMoves[y - 1][x] = 1; else if (!isWhite && y + 1 != 8) availableMoves[y + 1][x] = 1;
}


void Knight::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	if (moveCount == 0) {
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y - 1 != -1) availableMoves[y - 1][x] = 1; else if (!isWhite && y + 1 != 8) availableMoves[y + 1][x] = 1;
}


void Bishop::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	if (moveCount == 0) {
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y - 1 != -1) availableMoves[y - 1][x] = 1; else if (!isWhite && y + 1 != 8) availableMoves[y + 1][x] = 1;
}


void Queen::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	if (moveCount == 0) {
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y - 1 != -1) availableMoves[y - 1][x] = 1; else if (!isWhite && y + 1 != 8) availableMoves[y + 1][x] = 1;
}

void King::showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) {
	if (moveCount == 0) {
		if (isWhite)
			availableMoves[y - 2][x] = 1;
		else
			availableMoves[y + 2][x] = 1;
	}
	if (isWhite && y - 1 != -1) availableMoves[y - 1][x] = 1; else if (!isWhite && y + 1 != 8) availableMoves[y + 1][x] = 1;
}
