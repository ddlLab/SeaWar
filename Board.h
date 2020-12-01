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

	int					shipcount;

	shared_ptr<eCell>	GetCellByPos(const ePosition& _pos);

	string				Dump()						const;
	string				ShortDump(bool isCurrentPlayer)					const;
	bool				IsValid()					const;
	eHitResult			OnHitted(const ePosition& _pos);

private:
	void				UnRegisterShips();

//todo : dima see as example ship
	bool				CanAddShip(const eShip&) const;
	bool				LimitNotReached(const eShip&) const;

	eGameStatus			status = eGameStatus::INVALID;
	eShips				ships;
};
