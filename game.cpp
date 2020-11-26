#include "game.h"
#include <iostream>

eGame::eGame(eUser* _user1, eUser* _user2)
: user1(_user1)
, user2(_user2)
{
}

void eGame::Init()
{
	user1->Init(&board1, &board2);
	user2->Init(&board2, &board1);

	//ePreparer preparer(&board1, &board2);
	//preparer.Start();

	//delete after implement preparer
	/*
	shared_ptr<eShip> ship = make_shared<eShip>();
	ship->AddCell(board1.GetCellByPos(ePosition(0, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(1, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(2, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(3, 0)));
	board1.AddShip(ship);
	ship = make_shared<eShip>();
	ship->AddCell(board2.GetCellByPos(ePosition(1, 0)));
	ship->AddCell(board2.GetCellByPos(ePosition(1, 1)));
	ship->AddCell(board2.GetCellByPos(ePosition(1, 2)));
	board2.AddShip(ship);
	ship = make_shared<eShip>();
	ship->AddCell(board1.GetCellByPos(ePosition(0, 5)));
	ship->AddCell(board1.GetCellByPos(ePosition(1, 5)));
	ship->AddCell(board1.GetCellByPos(ePosition(2, 5)));
	board1.AddShip(ship);
	ship = make_shared<eShip>();
	ship->AddCell(board2.GetCellByPos(ePosition(7, 2)));
	ship->AddCell(board2.GetCellByPos(ePosition(6, 2)));
	ship->AddCell(board2.GetCellByPos(ePosition(5, 2)));
	board2.AddShip(ship);
	*/
}

void eGame::Start()
{
	//if (user1->CanStart() && user2->CanStart())
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