#pragma once

#include "user.h"
#include "board.h"

class eGame
{
public:
	eGame(eUser* user1, eUser* user2);
	~eGame() = default;

	 void Init();
	void Start();
	void Done();

protected:
	void DoStep();
	void OnUserStepped(bool isSuccess, bool isHitted);

	eUser*		user1 = nullptr;
	eUser*		user2 = nullptr;
	eBoard		board1;
	eBoard		board2;
	string		cords;
	bool		isFirstPlayerStep = true;
	bool		Board1Ready = false;
	bool		Board2Ready = false;
	uint32_t	step = 0;
};