#include "ship.h"
#include "vector_tools.h"
#include <sstream>
#include <algorithm>

//-----------------------------------------------------------------------
string eShip::Dump() const
{
	std::stringstream res;
	res << "shipStatus:" << shipStatus
		<< ", cells: " << DumpTotalPtr(cells);
	return res.str();
}
//-----------------------------------------------------------------------
bool eShip::IsValid() const
{
	return IsValidEnum(shipStatus) 
		&& IsValidTotalPtr(cells)
		&& cells.size() <= 4
		&& !cells.empty();
}
//-----------------------------------------------------------------------
bool eShip::AddCell(shared_ptr<eCell> _cell)
{
	if (CanAddCell (*_cell))
	{
		cells.emplace_back(_cell);
		_cell->Register(this);
		return true;
	}
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
		&& _cell.IsEmpty())
	{
		bool canAdd = true;
		if (!cells.empty())
		{
			for (shared_ptr<eCell> c : cells)
			{
				//todo::dima
			}
		}
		return canAdd;
	}
	return false;
}
//-----------------------------------------------------------------------