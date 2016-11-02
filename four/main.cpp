#include "stdafx.h"

#include "console.h"
#include "board.h"
#include "player.h"

int main()
{
	Console::init();
	Board::init();
	srand(time(nullptr));

	Console::set_title("test");

	// Console::set_dimensions(15, 20);


	// If you want to play more than one time, just loop this scope.
	{

		std::map<bool, Player*> players;

		int n = 0;
		while (n != 1 && n != 2 && n != 3)
		{
			Console::clear();
			std::cout << "Offensive Player is: " << std::endl;
			std::cout << "1. Human\t2. AI Computer\t3. Random Computer" << std::endl;
			std::cin >> n;
		}
		if (n == 1)
		{
			Player* player1 = new HumanPlayer(true);
			players[true] = player1;
		}
		else if (n == 2)
		{
			Player* player1 = new ComputerPlayer(true, false);
			players[true] = player1;
		}
		else if (n == 3)
		{
			Player* player1 = new ComputerPlayer(true, true);
			players[true] = player1;
		}
		n = 0;
		while (n != 1 && n != 2 && n != 3)
		{
			Console::clear();
			std::cout << "Defensive Player is: " << std::endl;
			std::cout << "1. Human\t2. AI Computer\t3. Random Computer" << std::endl;
			std::cin >> n;
		}
		if (n == 1)
		{
			Player* player2 = new HumanPlayer(false);
			players[false] = player2;
		}
		else if (n == 2)
		{
			Player* player2 = new ComputerPlayer(false, false);
			players[false] = player2;
		}
		else if (n == 3)
		{
			Player* player2 = new ComputerPlayer(false, true);
			players[false] = player2;
		}

		bool offensiveMoving = true;

		while (true)
		{
			Player* currentPlayer = players[offensiveMoving];
			currentPlayer->move();
			Board::action(*currentPlayer);
			if (Board::checkWin(*currentPlayer))
			{
				Console::clear();
				Board::print();
				std::cout << "Player ";
				if (currentPlayer->isOffensive()) std::cout << 1;
				else std::cout << 2;
				std::cout << " wins!" << std::endl;
				break;
			}
			offensiveMoving = !offensiveMoving;
		}


		delete players[true];
		delete players[false];
	}




	Console::deinit();
	system("pause");
}