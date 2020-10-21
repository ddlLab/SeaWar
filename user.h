#pragma once

#include "board.h"



class eUser
{
public:
	eUser(int id, const string& name);

	~eUser() = default;

	void	Init(eBoard* _myBoard, eBoard*	_enemyBoard) {}
	void	Done()										 {}


	string	Dump()		const							 { return "";}

	bool	CanStart()	const							 { return false; }

protected:
	int		id			= 0;
	int		gameId		= 0;
	string	name;
	eBoard*	myboard		= nullptr;
	eBoard*	enemyboard	= nullptr;
};
