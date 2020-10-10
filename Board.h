#pragma once

#include "cell.h"
#include "ship.h"



//Board must have methods ToString and CanStart() which check can we change state Perepared->Starting
class eBoard : private eCells
{
public:
	eBoard();
	~eBoard() = default;
	bool				IsPreparing()				const { return status == eGameStatus::PREPARING; };
	bool				IsStarting()				const { return status == eGameStatus::STARTING;  };
	bool				IsStarted()					const { return status == eGameStatus::STARTED;   };
	bool				IsFinished()				const { return status == eGameStatus::FINISHED;  };
	bool				CanStart()					const;

	string				Dump()						const;
	string				ShortDump()						const;

private:

	eGameStatus	status = eGameStatus::INVALID;
	eShips ships;
};
