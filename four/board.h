#pragma once

#include "console.h"
#include "player.h"
#include <vector>

/**************************************************************\
*                                                             *
*    Board is also a class who has only static members.       *
*                                                             *
\*************************************************************/

class Board
{
	// AI player may want get board situation.
	friend class ComputerPlayer;
private:
	// This stores data.
	static std::vector< std::vector<bool> > board;

	// These four are used in Board::checkWin(Player&),
	// to check 4 chesspieces are in line.
	static int Board::checkDown(int line, bool value);
	static int Board::checkHorizontal(int line, bool value);
	static int Board::checkLeftDown(int line, bool value);
	static int Board::checkRightDown(int line, bool value);

public:
	// Init function
	static void init();
	static void action(Player& player);
	static bool isFull();
	static bool isFull(int line);
	static void print();
	static bool checkWin(Player& player);
};
