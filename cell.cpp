﻿#include "cell.h"
#include <sstream>

//-----------------------------------------------------------------------
eCell::eCell(const ePosition& _pos)
: pos(_pos)
, cellType(eCellType::EMPTY)
{}
//-----------------------------------------------------------------------
void eCell::Register(eShip*_ship)
{
	cellType = eCellType::ALIVE;
	ship = _ship;
}
//-----------------------------------------------------------------------
void eCell::UnRegister(eShip *)
{
	ship = nullptr;
	cellType = eCellType::EMPTY;
}
//-----------------------------------------------------------------------
string eCell::Dump() const
{
	std::stringstream res;
	res << "cellType:" << cellType
		<< ", pos: "   << pos.Dump();
	return res.str();
}
//-----------------------------------------------------------------------
string eCell::ShortDump(bool isCurrentPlayer) const
{
	switch (cellType)
	{
	case eCellType::ALIVE: return isCurrentPlayer? "O":"~";
	case eCellType::EMPTY: return  "~";
	case eCellType::HITTED:return  "X";
	case eCellType::MISSED:return  "*";
	}
	return"";
}
//-----------------------------------------------------------------------
bool eCell::IsValid() const
{
	return IsValidEnum(cellType) && pos.IsValid();
}
//-----------------------------------------------------------------------
bool eCell::OnHitted()
{
	switch (cellType)
	{
	case eCellType::ALIVE: cellType = eCellType::HITTED; return true;
	case eCellType::EMPTY: cellType = eCellType::MISSED; return true;
	}
	return false;
}
