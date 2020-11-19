// SeaWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <array>
#include <memory>
#include "cell.h"
#include "board.h"
#include "vector_tools.h"
#include "user.h"
#include "text_functions.h"

using namespace std;

void f(bool isSuccess, bool isHitted)
{
	cout << "isSuccess:" << isSuccess << "\tisHitted:" << isHitted << endl;
}

int main()
{
	string test = "a,b,c,d";
	vector<string> test1;
	Split(test, test1, "");



	eConsoleUser user1(1, "Ivanuch");
	eConsoleUser user2(2, "Petrovich");
	eBoard board1;
	eBoard board2;
	user1.Init(&board1, &board2);
	user2.Init(&board2, &board1);
	shared_ptr<eShip> ship = make_shared<eShip>();
	ship->AddCell(board1.GetCellByPos(ePosition(0, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(1, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(2, 0)));
	ship->AddCell(board1.GetCellByPos(ePosition(3, 0)));
	//ship->AddCell(board.GetCellByPos(ePosition(0, 0)));
	board1.AddShip(ship);
	system("pause");
	system("cls");
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
	
	while (true)
	{
		//	system("clr");
		user1.DoStep([](bool isSuccess, bool isHittted)
		{
			f(isSuccess, isHittted);
		});
	}

	/*vector<eCell> test;
	test.emplace_back(eCell({ 3,5 }));
	test.emplace_back(eCell({ 3,4 }));
	test.emplace_back(eCell({ 3,3 }));
	test.emplace_back(eCell({ 3,2 }));
	test.emplace_back(eCell({ 3,1 }));
	vector<eCell*> test1;
	test1.emplace_back(new eCell({5,3}));
	test1.emplace_back(new eCell({4,3}));
	test1.emplace_back(new eCell({3,3}));
	test1.emplace_back(new eCell({2,3}));
	test1.emplace_back(new eCell({1,3}));

	cout << "test:" << DumpTotal(test) << endl;
	cout << "test1:" << DumpTotal(test1) << endl;


	cout << "test:" << IsValidTotal(test) << endl;

	cout << "test1:" << IsValidTotal(test1) << endl;
	*//*
	eCell  cell({ 3,3 });
	cout << cell.Dump() << endl;

	std::array<std::array<int, 10>, 10> myarray;

	for (auto& col : myarray)
	{
		for (auto& item : col)
		{
			item = 0;
		}
	}
	ePosition pos(0, 0);
	myarray[pos.XToBoard()][pos.YToBoard()] = 1;
	while (true)
	{
		system("cls");

		for (auto& col : myarray)
		{
			for (auto& item : col)
			{
				cout << item;
			}
			cout << endl;
		}
		cout << pos.Dump() << endl;
		char ch = _getch();

		ePosition posNew = pos;
		switch (ch)
		{
		case 'w': --posNew.col; if (posNew.col == START_COL)	pos.col = END_COL; break;
		case 'a':
			--posNew.row;
			if (posNew.row == START_ROW)
				pos.row = END_ROW; break;
		case 's': ++posNew.col; if (posNew.col == END_COL)		pos.col = START_COL; break;
		case 'd': 
			++posNew.row;
			if (posNew.row == END_ROW)
				pos.row = START_ROW; break;
		}

		if (pos != posNew) 
		{
			myarray[pos.XToBoard()][pos.YToBoard()] = 0;
			pos = posNew;
			myarray[pos.XToBoard()][pos.YToBoard()] = 1;
		}


	}*/
}