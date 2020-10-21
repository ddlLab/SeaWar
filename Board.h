#pragma once

#include "cell.h"
#include "ship.h"


//todo alex:
//Board must have methods ToString and CanStart() which check can we change state Perepared->Starting
class eBoard : private eCells
{
public:
	eBoard();
	~eBoard();
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
	bool				CanAddShip(const eShip& cell) const;

	eGameStatus	status = eGameStatus::INVALID;
	eShips		ships;
};

//todo: sasha create class User which contains two Boards, and user name. you can add other optional fields
//todo: sasha create class Game which contains two Users
//please thinking  about methods about this two classes and start create method interfaces and release it