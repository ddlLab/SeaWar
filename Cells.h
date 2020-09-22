#pragma once

#include <iostream>
#include "enums.h"
#include "tools.h"
#include "token.h"
#include <vector>
#include <string>

using namespace std;

class eCell
{
public:
	eCell();
	~eCell();
	eCell ShipRegister();
	eCell ShipUnRegister();
	eCell Dump();
	const ePosition& Position() const { return pos; }
	bool IsEmpty = true, OnHitted, IsAlive, IsHitted, IsPassed;
private:
	eCellType	cellType = eCellType::EMPTY;
	ePosition pos;
	if ((eCell.pos == eShip.pos) && !IsHitted)
	{
		eCellType cellType = eCellType::ALIVE;
	}
	else if ((eCell.pos == eShip.pos) && IsShoted)
	{
		eCellType cellType = eCellType::HITTED;
	}
	else if ((eCell.pos != eShip.pos) && IsShoted)
	{
		eCellType cellType = eCellType::MISSED;
	}
	else
	{
		eCellType	cellType = eCellType::EMPTY;
	}

	
};

eCell::eCell()
{
}

eCell::~eCell()
{
}