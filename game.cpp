#include "game.h"
#include "text_functions.h"
#include <iostream>

using namespace std;

#define TEST

eGame::eGame(eUser* _user1, eUser* _user2)
: user1(_user1)
, user2(_user2)
{
}
#ifdef TEST
void eGame::Init()
{
	user1->Init(&board1, &board2);
	user2->Init(&board2, &board1);
	string cords = "a0|b3|c5|d7|c0 c1|e0 e1|g0 g1|i0 i1|i0 i1 i2|i7 h7 g7|g9 h9 i9 j9";
	//todo dima:
	//GenerateBoard(board1, map1)//where map this is something like string cords
	//GenerateBoard(board2, map2)//where map this is something like string cords
	//down code this is sample what are your func must do. you can copy and some refac it
	//! do it as func not as method
	vector<string> ships;
	Split(cords, ships, '|');
	for (const string& shipStr : ships)
	{
		stringstream ss;
		ss << shipStr;
		shared_ptr<eShip> ship = make_shared<eShip>();
		while (!ss.eof())
		{
			string pos;
			ss >> pos;
			cout << pos<< endl;
			auto cell = board1.GetCellByPos(ePosition(cords));
			cout << cell->Dump()<< endl;
			ship->AddCell(cell);
		}
		board1.AddShip(ship);
		cout << board1.ShortDump(true) << endl;
		ship.reset();
	}
	
	/*
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
	}*/
}
#else
void eGame::Init()
{
	user1->Init(&board1, &board2);
	user2->Init(&board2, &board1);
	string cords;
	//todo: alex
	//PrepareBoard(board1, user1->Name());
	//PrepareBoard(board2, user2->Name());
	//this code need move to func PrepareBoard and some refac
	//! do it as func not as method
	while (board1.IsPreparing())
	{
		shared_ptr<eShip> ship = make_shared<eShip>();
		cout << "Игрок " << user1->Name() << " введите корабли" << endl;
		cout << "Введите координаты корабля(по 1 клетке(пример: '0, 1')" << endl;
		cout << "Если корабль готов нажмите 'R'" << endl;
		int it = 0;
		while (it < 4)
		{
			cin >> cords;
			if (cords == "r" || cords == "R") break;
			auto cell = board1.GetCellByPos(ePosition(cords));
			ship->AddCell(cell);
			it++;
		}
		board1.AddShip(ship);
		cout << board1.ShortDump(true) << endl;
		cords = "";
		ship.reset();
	}
	/*
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
	}*/
}
#endif

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