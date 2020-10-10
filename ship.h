#pragma once
#include "enums.h"
#include "tools.h"
#include "cell.h"
  
class eCell;

class eShip
{
public:
	eShip() = default;
	~eShip();

	string				Dump()			const;
	bool				IsValid()		const;

	bool				IsPrepared()	const		{ return shipStatus == eShipStatus::PREPARED; };
	bool				IsAlive()		const		{ return shipStatus == eShipStatus::ALIVE; };
	bool				IsDead()		const		{ return shipStatus == eShipStatus::DEAD; };

	bool				AddCell(shared_ptr<eCell>); //{ return shipStatus == eShipStatus::PREPARED; };
	bool				Start();					//{ return shipStatus == eShipStatus::ALIVE; };

	bool				OnHitted(shared_ptr<eCell>)	  const;
private:
	void				CheckStatus();
	bool				CanAddCell(const eCell& cell) const;
	void				UnRegisterCells();

	eShipStatus shipStatus = eShipStatus::INVALID;
	eCells		cells;
};

using eShips = vector<shared_ptr<eShip>>;

