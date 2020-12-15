#include "game.h"
#include "text_functions.h"
#include <iostream>

using namespace std;

static void PrepareBoard(eBoard* board, eUser* user);
static void PrepareBoard(eBoard* board, eUser* user, istream& is);

#define TEST

eGame::eGame(eUser* _user1, eUser* _user2)
: user1(_user1)
, user2(_user2)
{
}
void eGame::Init()
{
	user1->Init(&board1, &board2);
	user2->Init(&board2, &board1);
#ifndef TEST
	PrepareBoard(&board1, user1);
	PrepareBoard(&board2, user2);
#else
	stringstream ss1;
	ss1 << "a0 r b3 r c5 r d7 r c0 c1 r e0 e1 r g0 g1 r i0 i1 r i0 i1 i2 r i7 h7 g7 r g9 h9 i9 j9 r";
	PrepareBoard(&board1, user1,ss1);
	stringstream ss2;
	ss2 << "a0 r c0 r e0 r g0 r a2 b2 r d2 d3 r f2 f3 r i0 i1 i2 r i7 h7 g7 r g9 h9 i9 j9 r";
	PrepareBoard(&board2, user2, ss2);
#endif
}

void eGame::Start()
{
	if (user1->CanStart() && user2->CanStart())
	{
		DoStep();
	}
}
void eGame::Done()
{
}


void eGame::DoStep()
{
	if (board1.IsFinished())
	{
		cout << user2->Name() << " в неравном но очень стремном бою одержал неравную но очень стремную победу!";
		return;
	}

	if (board2.IsFinished())
	{
		cout << user1->Name() << "при трезвом уме и нетвердой памяти одержал неравную но очень стремную победу!";
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

static void PrepareBoard(eBoard* board, eUser* user)
{
	{
		string cords;
		while (board->IsPreparing())
		{
			shared_ptr<eShip> ship = make_shared<eShip>();
			cout << "Игрок " << user->Name() << " введите корабли" << endl;
			cout << "Введите координаты корабля(по 1 клетке(пример: '0, 1')" << endl;
			cout << "Если корабль готов нажмите 'R'" << endl;
			int it = 0;
			while (it < 4)
			{
				cin >> cords;
				if (cords == "r" || cords == "R") break;
				auto cell = board->GetCellByPos(ePosition(cords));
				ship->AddCell(cell);
				it++;
			}
			board->AddShip(ship);
			cout << board->ShortDump(true) << endl;
			cords = "";
			ship.reset();
		}
	}
}

static void PrepareBoard(eBoard* board, eUser* user, istream& is)
{
	{
		string cords;
		cout << "Игрок " << user->Name() << " введите корабли" << endl;
		while (board->IsPreparing())
		{
			shared_ptr<eShip> ship = make_shared<eShip>();
			//cout << "Введите координаты корабля(по 1 клетке(пример: '0, 1')" << endl;
			//cout << "Если корабль готов нажмите 'R'" << endl;
			int it = 0;
			while (it < 4)
			{
				is >> cords;
				if (cords == "r" || cords == "R") break;
				auto cell = board->GetCellByPos(ePosition(cords));
				ship->AddCell(cell);
				it++;
			}
			board->AddShip(ship);
			//cout << board->ShortDump(true) << endl;
			cords = "";
			ship.reset();
		}
		cout << board->ShortDump(true) << endl;
	}
}