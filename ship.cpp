#include "ship.h"
#include "vector_tools.h"
#include "board.h"
#include <sstream>
#include <algorithm>

//-----------------------------------------------------------------------
eShip::~eShip()
{
	UnRegisterCells();
}
//-----------------------------------------------------------------------
void eShip::UnRegisterCells() 
{
	for (shared_ptr<eCell> cell : cells)
	{
		cell->UnRegister(this);
	}
	cells.clear();
}
//-----------------------------------------------------------------------
string eShip::Dump() const
{
	std::stringstream res;
	res << "shipStatus:" << shipStatus
		<< ", cells: " << DumpTotal(cells);
	return res.str();
}
//-----------------------------------------------------------------------
bool eShip::IsValid() const
{
	return IsValidEnum(shipStatus) 
		&& IsValidTotal(cells)
		&& cells.size() <= 4
		&& !cells.empty();
}
//-----------------------------------------------------------------------
bool eShip::AddCell(shared_ptr<eCell> _cell)
{
	if (CanAddCell(*_cell))
	{
		cells.emplace_back(_cell);
		_cell->Register(this);
		return true;
	}
	UnRegisterCells();
	return false;
}
//-----------------------------------------------------------------------
bool eShip::Start()
{
	if (shipStatus == eShipStatus::PREPARED
		&& IsValid())
	{
		shipStatus = eShipStatus::ALIVE;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------
void eShip::Register(eBoard* _board)
{
}
//-----------------------------------------------------------------------
void eShip::UnRegister(eBoard*  _board)
{
}

//-----------------------------------------------------------------------
bool eShip::OnHitted(shared_ptr<eCell> _cell) const
{
	for (shared_ptr<eCell> c : cells)
	{
		if (c == _cell)
		{
			_cell->OnHitted();
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------
void eShip::CheckStatus()
{
	if (shipStatus == eShipStatus::ALIVE)
	{
		bool isAllHitted = std::all_of(cells.cbegin(), cells.cend(), [](const shared_ptr<eCell>& _c)
		{
			return _c->IsHitted();
		});
		if (isAllHitted)
		{
			shipStatus = eShipStatus::DEAD;
		}
	}
}
//-----------------------------------------------------------------------
bool eShip::CanAddCell(const eCell& _cell) const
{	
	if (shipStatus == eShipStatus::PREPARED
		&& _cell.IsEmpty()
		&& cells.size() < eShip::MaxLength())
	{
		bool canAdd = true;
		if (!cells.empty())
		{
			ePosition minCell = cells[0]->Position();
			ePosition maxCell = cells[0]->Position();
			for (shared_ptr<const eCell> cell : cells)
			{
				if (minCell >= cell->Position())
				{
					minCell = cell->Position();
				}
				if (maxCell <= cell->Position())
				{
					maxCell = cell->Position();
				}
			}
			
			int diffX = abs(maxCell.col - minCell.col);
			int diffY = abs(maxCell.row - minCell.row);
			
			canAdd = (diffX == 0 && diffY + 1 < cells.size()) 
				  || (diffY == 0 && diffX + 1 < cells.size());
		}
		return canAdd;
	}
	return false;
}
//-----------------------------------------------------------------------