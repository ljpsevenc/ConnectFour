#include "stdafx.h"

#include "player.h"
#include "board.h"
#include <cmath>
#include <algorithm>

ComputerPlayer::ComputerPlayer(bool offensive, bool random)
{
	offensive_ = offensive;
	choice_ = -1;
	random_ = random;
}



void ComputerPlayer::move()
{
	Console::clear();
	Board::print();

	if (random_)
	{
		int n = rand() % 7;

		while (Board::isFull(n))
		{
			n = rand() % 7;
		}
		choose(n);
	}
	else
	{
		std::vector<int> values;
		values.resize(7, 0);
		int maxValue = 0;
		int n = 0;
		for (; n < 7; ++n)
		{
			if (Board::isFull(n)) continue;
			values[n] = evaluate(n);
			if (values[n] > maxValue)
			{
				maxValue = values[n];
			}
		}

		std::vector<int> maxes;
		maxes.reserve(7);
		for (int i = 0; i < 7; ++i)
			if (values[i] == maxValue)
				maxes.push_back(i);

		int choice = rand() % maxes.size();
		choose(maxes[choice]);
	}

	system("pause");
}

int ComputerPlayer::evaluate(int line) const
{
	int k1 = 1;
	int k2 = 1;

	return k1 * evaluatePlayer(line, offensive_) + k2 * evaluatePlayer(line, !offensive_);
}

int ComputerPlayer::evaluatePlayer(int line, bool offensive)
{
	int downValue = exp2(evaluateDown(line, offensive));
	int horizontalValue = exp2(evaluateHorizontal(line, offensive));
	int leftDownValue = exp2(evaluateLeftDown(line, offensive));
	int rigutDownValue = exp2(evaluateRightDown(line, offensive));

	if (downValue == 16) downValue *= 64;
	if (horizontalValue == 16) horizontalValue *= 64;
	if (leftDownValue == 16) leftDownValue *= 64;
	if (rigutDownValue == 16) rigutDownValue *= 64;

	return downValue + horizontalValue + leftDownValue + rigutDownValue;
}

int ComputerPlayer::evaluateDown(int line, bool value)
{
	int result = 1;
	int row = Board::board[line].size() - 1;
	// unlike other directions, there's no need to check up.
	while (row >= 0 &&                 // check if the coordinate is in the board
		   Board::board[line][row] == value)  // check the chesspiece
	{
		++result;
		--row;  // go down
	}
	return result;
}
int ComputerPlayer::evaluateHorizontal(int line, bool value)
{
	int result = 1;
	int row = Board::board[line].size();
	int startLine = line;
	// check left
	line = startLine - 1;
	while (row >= 0 && line >= 0 &&     // check if the coordinate is in the board
		   Board::board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   Board::board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  //go left
	}
	// check right
	line = startLine + 1;
	while (row >= 0 && line < 7 &&
		   Board::board[line].size() > row &&
		   Board::board[line][row] == value)
	{
		++result;
		++line;  // go right
	}
	return result;
}
int ComputerPlayer::evaluateLeftDown(int line, bool value)
{
	int result = 1;
	int row = Board::board[line].size();
	int startRow = row;
	int startLine = line;
	// check left down
	row = startRow - 1;
	line = startLine - 1;
	while (row >= 0 && line >= 0 &&     // check if the coordinate is in the board
		   Board::board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   Board::board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  //go left
		--row;   // go down
	}
	// check right up
	row = startRow + 1;
	line = startLine + 1;
	while (row < 6 && line < 7 &&
		   Board::board[line].size() > row &&
		   Board::board[line][row] == value)
	{
		++result;
		++line;  // go right
		++row;   // go up
	}
	return result;
}
int ComputerPlayer::evaluateRightDown(int line, bool value)
{
	int result = 0;
	int row = Board::board[line].size();
	int startRow = row;
	int startLine = line;
	// check left up
	row = startRow + 1;
	line = startLine - 1;
	while (row < 6 && line >= 0 &&      // check if the coordinate is in the board
		   Board::board[line].size() > row &&  // check if the coordinate stored data in Board::board
		   Board::board[line][row] == value)   // check the chesspiece
	{
		++result;
		--line;  //go left
		++row;   // go up
	}
	// check right down
	row = startRow - 1;
	line = startLine + 1;
	while (row >= 0 && line < 7 &&
		   Board::board[line].size() > row &&
		   Board::board[line][row] == value)
	{
		++result;
		++line;  // go right
		--row;   // go down
	}
	return result;
}