#pragma once
class Player
{
private:
	bool myTurn = false;
	bool white = false;
	int moveCount = 0;

public:
	bool isWhite() { return white; }
	Player(bool turn, bool isWhite);
};

