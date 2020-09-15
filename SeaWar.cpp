// SeaWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<conio.h>
#include <array>
#include "tools.h"
#include "types.h"

using namespace std;

int main()
{
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


	}
}