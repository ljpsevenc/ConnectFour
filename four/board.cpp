#include "stdafx.h"

#include "player.h"
#include "board.h"

// Define the static member variable.
std::vector< std::vector<bool> > Board::board;

void Board::init()
{
	board.resize(7, std::vector<bool>());
	//for (auto line : board)
	//	line.reserve(6);
	for (int i = 0; i < 7; ++i)
		board[i].reserve(6);
}

void Board::action(Player& player)
{
	int line = player.choice();
	bool offensivePlayer = player.isOffensive();
	board[line].push_back(offensivePlayer);
}

bool Board::isFull()
{
	for (int i = 0; i < 7; ++i)
		if (board[i].size() < 6)
			return false;
	return true;
}

bool Board::isFull(int line)
{
	return (board[line].size() == 6);
}

void Board::print()
{
	Console::set_cursor_color(white);
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;
	std::cout << "| | | | | | | |" << std::endl;
	std::cout << "+-+-+-+-+-+-+-+" << std::endl;

	for (int line = 0; line < 7; ++line)
	{
		for (int row = 0; row < board[line].size(); ++row)
		{
			if (board[line][row]) Console::set_cursor_color(yellow);
			else Console::set_cursor_color(green);
			COORD p = { 2 * line + 1, 12 - (2 * row + 1) };
			Console::set_cursor_position(p);
			std::cout << '*';
		}
	}

	Console::set_cursor_color(white);
	COORD p = { 0, 13 };
	Console::set_cursor_position(p);

}


bool Board::checkWin(Player& player)
{
	return (checkDown      (player.choice(), player.isOffensive()) == 4 || 
			checkHorizontal(player.choice(), player.isOffensive()) == 4 || 
			checkLeftDown  (player.choice(), player.isOffensive()) == 4 || 
			checkRightDown (player.choice(), player.isOffensive()) == 4);
}

int Board::checkDown(int line, bool value)
{
	int result = 1;
	int row = board[line].size() - 2;
	// unlike other directions, there's no need to check up.
	while (row >= 0 &&                 // check if the coordinate is in the board
		   board[line][row] == value)  // check the chesspiece
	{
		++result;
		--row;  // go down
	}
	return result;
}
int Board::checkHorizontal(int line, bool value)
{
	int result = 1;
	int row = board[line].size() - 1;
	int startLine = line;
	// check left
	line = startLine - 1;
	while (row >= 0 && line >= 0 &&     // check if the coordinate is in the board
		   board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  //go left
	}
	// check right
	line = startLine + 1;
	while (row >= 0 && line < 7 && 
		   board[line].size() > row && 
		   board[line][row] == value)
	{
		++result;
		++line;  // go right
	}
	return result;
}
int Board::checkLeftDown(int line, bool value)
{
	int result = 1;
	int row = board[line].size() - 1;
	int startRow = row;
	int startLine = line;
	// check left down
	row = startRow - 1;
	line = startLine - 1;
	while (row >= 0 && line >= 0 &&     // check if the coordinate is in the board
		   board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  //go left
		--row;   // go down
	}
	// check right up
	row = startRow + 1;
	line = startLine + 1;
	while (row < 6 && line < 7 &&
		   board[line].size() > row &&
		   board[line][row] == value)
	{
		++result;
		++line;  // go right
		++row;   // go up
	}
	return result;
}
int Board::checkRightDown(int line, bool value)
{
	int result = 1;
	int row = board[line].size() - 1;
	int startRow = row;
	int startLine = line;
	// check left up
	row = startRow + 1;
	line = startLine - 1;
	while (row < 6 && line >= 0 &&      // check if the coordinate is in the board
		   board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  // go left
		++row;   // go up
	}
	// check right down
	row = startRow - 1;
	line = startLine + 1;
	while (row >= 0 && line < 7 &&
		   board[line].size() > row &&
		   board[line][row] == value)
	{
		++result;
		++line;  // go right
		--row;   // go down
	}
	return result;
}


