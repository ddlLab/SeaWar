#pragma once
#include "enums.h"
#include "tools.h"
#include "cell.h"
  
class eCell;
class eBoard;

class eShip
{
public:
	eShip();
	~eShip();

	string				Dump()			const;
	bool				IsValid()		const;

	bool				IsPrepared()	const		{ return shipStatus == eShipStatus::PREPARED; };
	bool				IsAlive()		const		{ return shipStatus == eShipStatus::ALIVE; };
	bool				IsDead()		const		{ return shipStatus == eShipStatus::DEAD; };

	bool				AddCell(shared_ptr<eCell>); //{ return shipStatus == eShipStatus::PREPARED; };
	bool				Start();					//{ return shipStatus == eShipStatus::ALIVE; };

//todo : dima see as example cell
	void				Register(eBoard*);
	void				UnRegister(eBoard*);

	const eCells&		Cells()						  const { return cells; }
	int					Size()						  const { return cells.size(); }


	bool				OnHitted(shared_ptr<eCell>)	  const;
private:
	void				CheckStatus();
	bool				CanAddCell(const eCell& cell) const;
	void				UnRegisterCells();

	eShipStatus shipStatus = eShipStatus::INVALID;
	eCells		cells;
	eBoard*		board = nullptr;
};

using eShips = vector<shared_ptr<eShip>>;

