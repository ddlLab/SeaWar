#pragma once

#include "cell.h"
#include "ship.h"


class eBoard : private eCells
{
public:
	eBoard();
	virtual ~eBoard();
	bool				IsPreparing()				const { return status == eGameStatus::PREPARING; };
	bool				IsStarting()				const { return status == eGameStatus::STARTING;  };
	bool				IsStarted()					const { return status == eGameStatus::STARTED;   };
	bool				IsFinished()				const { return status == eGameStatus::FINISHED;  };
	bool				CanStart()					const;

//todo : dima see as example ship
	bool				AddShip(shared_ptr<eShip>);
	bool				Start();

	string				Dump()						const;
	string				ShortDump()					const;
	bool				IsValid()					const;

private:
	void				UnRegisterShips();

//todo : dima see as example ship
//todo : sasha 
	bool				CanAddShip(const eShip& cell) const { return true; }

	eGameStatus	status = eGameStatus::INVALID;
	eShips		ships;
};
