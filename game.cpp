#include "game.h"
#include <iostream>

using namespace std;

eGame::eGame(eUser* _user1, eUser* _user2)
: user1(_user1)
, user2(_user2)
{
}

void eGame::Init()
{
	board1.shipcount = 0;
	board2.shipcount = 0;
	user1->Init(&board1, &board2);
	user2->Init(&board2, &board1);
	{
		cout << "Игрок 1 введите корабли" << endl;
		cout << "Введите координаты корабля(по 1 клетке(пример: '0, 1')" << endl;
		cin >> cords;
		shared_ptr<eShip> ship = make_shared<eShip>();
		ship->AddCell(board1.GetCellByPos(ePosition(cords)));
		cout <<eCells.shortDump(true) << endl;
		while (board1.shipcount != 10)
		{
			cout << "Введите координаты корабля" << endl;
			cout << "Если корабль готов нажмите 'R'" << endl;
			cin >> cords;
			if (cords != "r" || cords != "R")
			{
				ship->AddCell(board1.GetCellByPos(ePosition(cords)));
				cout << eCells.shortDump(true) << endl;
			}
			else
			{
				board1.AddShip(ship);
				cout << eCells.shortDump(true) << endl;
			}
		}
	}
	{
		cout << "Игрок 2 введите корабли" << endl;
		cout << "Введите координаты корабля(по 1 клетке(пример: '0, 1')" << endl;
		cin >> cords;
		shared_ptr<eShip> ship = make_shared<eShip>();
		ship->AddCell(board2.GetCellByPos(ePosition(cords)));
		cout << eCells.shortDump(true) << endl;
		while (board2.shipcount != 10)
		{
			cout << "Введите координаты корабля" << endl;
			cout << "Если корабль готов нажмите 'R'" << endl;
			cin >> cords;
			if (cords != "r" || cords != "R")
			{
				ship->AddCell(board2.GetCellByPos(ePosition(cords)));
					cout << eCells.shortDump(true) << endl;
			}
			else
			{
				board2.AddShip(ship);
					cout << eCells.shortDump(true) << endl;
			}
		}
	}
}

void eGame::Start()
{
	if ((user1->CanStart() && user2->CanStart())&&(Board1Ready && Board2Ready))
	{
		DoStep();
	}
}
void eGame::Done()
{
}


void eGame::DoStep()
{
	if (board1.IsFinished() || board2.IsFinished())
	{
		return;
	}
	eUser* user = isFirstPlayerStep ? user1 : user2;
	user->DoStep([this](bool isSuccess, bool isHittted)
	{
		system("cls");
		OnUserStepped(isSuccess, isHittted);
	});
}

void eGame::OnUserStepped(bool isSuccess, bool isHitted)
{
	if (!isSuccess)
	{
		std::cout << "!isSuccess" << std::endl;
		DoStep();
		return;
	}
	step++;
	if (isHitted)
	{
		std::cout << "Krasauchik!" << std::endl;
		DoStep();
		return;
	}
	isFirstPlayerStep = !isFirstPlayerStep;
	DoStep();
}