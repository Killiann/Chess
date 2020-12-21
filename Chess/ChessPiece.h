#pragma once
#include <SFML/Graphics.hpp>

class ChessPiece
{   
protected:
	int id;
	int moveCount = 0;
	int x, y;
	int tileWidth = 100;

	bool isAlive = true;
	bool isWhite;

	sf::Sprite sprite;
	sf::Texture *texture;

	bool canMove(int boardPieces[][8], int x, int y);
public:
	int getId() { return id; }
	virtual void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) { };
	virtual void draw(sf::RenderWindow &window);	
	void move(int nx, int ny, int (&pieceGrid)[8][8], std::vector<ChessPiece*> &pieces);
	void kill();
	ChessPiece(int id, int x, int y, bool isWhite, sf::Texture *t);

	inline bool isOpponent(bool isW) { if (isW == isWhite)return false;  else return true; }
};

class Pawn : public ChessPiece {	
public :
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	Pawn(int id, int x, int y, bool isWhite, sf::Texture *t);
};

class Rook : public ChessPiece {
public:
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	Rook(int id, int x, int y, bool isWhite, sf::Texture* t);
};

class Knight : public ChessPiece {
public:
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	Knight(int id, int x, int y, bool isWhite, sf::Texture* t);
};

class Bishop : public ChessPiece {
public:
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	Bishop(int id, int x, int y, bool isWhite, sf::Texture* t);
};

class Queen : public ChessPiece {
public:
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	Queen(int id, int x, int y, bool isWhite, sf::Texture* t);
};

class King : public ChessPiece {
public:
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
	King(int id, int x, int y, bool isWhite, sf::Texture* t);
};

