#pragma once
#include <SFML/Graphics.hpp>
#include "Console.h"

class ChessPiece
{   
protected:
	//const
	const int tileWidth = 100;

	//state
	int id;
	int moveCount = 0;
	int x, y;
	bool isAlive = true;
	bool isWhite;

	//piece drawing
	sf::Sprite sprite;
	sf::Texture *texture;

	//consolue output
	Console* console;
	std::string pieceName;

public:
	//constr
	ChessPiece(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	
	//inline
	inline int getId() { return id; }		
	inline bool isOpponent(bool isW) { if (isW == isWhite)return false;  else return true; }
	
	//other
	void kill();
	void move(int nx, int ny, int(&pieceGrid)[8][8], std::vector<ChessPiece*>& pieces);
	virtual void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]) { };
	virtual void draw(sf::RenderWindow &window);	
};

class Pawn : public ChessPiece {		
public :
	Pawn(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

class Rook : public ChessPiece {
public:
	Rook(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

class Knight : public ChessPiece {
public:
	Knight(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

class Bishop : public ChessPiece {
public:
	Bishop(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

class Queen : public ChessPiece {
public:
	Queen(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

class King : public ChessPiece {
public:
	King(int id, int x, int y, bool isWhite, sf::Texture* t, Console* c);
	void showMoves(int boardPieces[][8], int(&availableMoves)[8][8]);
};

