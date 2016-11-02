#include "stdafx.h"

#include "console.h"
#include "player.h"
#include "board.h"

HumanPlayer::HumanPlayer(bool offensive)
{
	offensive_ = offensive;
	choice_ = -1;
}

void HumanPlayer::move()
{
	int n = -1;
	while (n < 0 || n >= 7 || Board::isFull(n))
	{
		Console::clear();
		Board::print();
		std::cout << ' ';
		for (int line = 0; line < 7; ++line)
			if (!Board::isFull(line))
				std::cout << line + 1 << ' ';
			else
				std::cout << "  ";
		std::cout << std::endl;
		std::cout << "Your choice?" << std::endl;
		std::cout << std::endl;
		std::cin >> n;
		--n;
	}
	choose(n);
}

