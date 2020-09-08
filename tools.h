#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

const char START_COL	= 'a';
const char END_COL		= 'h';
const char START_ROW	= '1';
const char END_ROW		= '8';

struct ePosition
{
	ePosition(char x, char y):col(x),row(y){}
	ePosition(int x, int y):col(x+START_COL),row(y+START_ROW){}
	ePosition()								= default;
	ePosition(const ePosition&)				= default;
	ePosition(ePosition&&)					= default;
	~ePosition()							= default;

	ePosition& operator=(const ePosition&)	= default;
	ePosition& operator=(ePosition&&)		= default;

	bool IsValid()		const { return col >= START_COL && col <= END_COL && row >= START_ROW && row <= END_ROW; }
	std::string Dump()	const { std::string t; t += col; t += row; return t; }

	int XToBoard()	const { return col - START_COL; }
	int YToBoard()	const { return row - START_ROW; }

	bool operator==(const ePosition& pos)	const { return col == pos.col && row == pos.row; }
	bool operator<(const ePosition& pos)	const { return Dump() < pos.Dump(); }
	bool operator>(const ePosition& pos)	const { return Dump() > pos.Dump(); }
	bool operator!=(const ePosition& pos)	const { return !operator==(pos); }

	char col = 0; //a-h
	char row = 0; //1-8
};


using ePositions = vector<ePosition>;

void GetTraektory(const ePosition& from, const ePosition& to, vector<ePosition>& traektory);

