#pragma once
#include "enums.h"
#include "tools.h"
#include <vector>
#include "cell.h"
  
class eCell;

class eShip
{
public:
	std::vector<eCell>  cells();
	std::string			Dump()			const;

	bool				ShipIsAlive()   const		{ return shipStatus == eShipStatus::ALIVE; };
	bool				ShipIsDead()    const		{ return shipStatus == eShipStatus::DEAD; };
	bool				AddCell()	    const		{ return shipStatus == eShipStatus::PREPARED; };
	bool				CanAddCell();
	bool				Start()		    const		{ return shipStatus == eShipStatus::ALIVE; };

	void				OnHitted()		const		{ return pos; };
private:
	eShipStatus shipStatus = eShipStatus::INVALID;
};

