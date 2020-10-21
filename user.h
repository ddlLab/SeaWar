#pragma once

#include "board.h"


class eUser : private eBoard
{
public:
	eUser();
	~eUser() = default;
	string Name;
	eBoard board1;
	eBoard board2;


};
