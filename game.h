#pragma once

#include "user.h"


class eGame : private eUser
{
public:
	eGame();
	~eGame() = default;
	eUser User1;
	eUser User2;
};