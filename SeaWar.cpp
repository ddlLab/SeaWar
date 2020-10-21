// SeaWar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <array>
#include "cell.h"
#include "board.h"
#include "vector_tools.h"

using namespace std;

class A
{
	DEFINE_SIMPLE_STATE(int, id, Id)
	DEFINE_SIMPLE_FIELD_TOTAL(string, name, Name)
private:
	int		id;
	string	name;
};

int main()
{
	A a;
	a.Id(5);
	
	cout << a.Id()<<endl;
	a.Name("c3po");
	cout << a.Name()<<endl;
	a.Name() = "bamblbee";
	cout << a.Name()<<endl;
	
	//eBoard board;
	//cout << board.ShortDump() << endl;
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