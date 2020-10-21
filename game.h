#pragma once

#include "user.h"

class eGame
{
public:
	eGame();
	~eGame() = default;

protected:
	eUser* User1 = nullptr;
	eUser* User2 = nullptr;

};