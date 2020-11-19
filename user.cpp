#include "user.h"
#include "Board.h"
#include "text_functions.h"

//*****************************************************
eUser::eUser(int _id, const string& _name)
: id(_id)
, name(_name)
{}
//=====================================================
void eUser::Init(eBoard* _myBoard, eBoard* _enemyBoard)
{
	myboard = _myBoard;
	enemyboard = _enemyBoard;
}
//=====================================================
void eUser::Done()
{
	enemyboard = nullptr;
	myboard = nullptr;
}
//=====================================================
string	eUser::Dump() const
{
	std::stringstream os;
	os << "Player " << name<<std::endl;
	vector<string> my; 
	vector<string> enemy;
	Split(myboard->ShortDump(true),		my, '\n');
	Split(enemyboard->ShortDump(false), enemy, '\n');
	
	for (size_t i = 0; i < my.size(); ++i)
	{
		os << my[i]<< "\t\t" <<enemy[i] << std::endl;
	}
	return os.str();
}
//=====================================================
bool eUser::CanStart() const
{
	return myboard->IsStarting();
}

#include<iostream>
using std::cout;
using std::cin;
using std::endl;
//*****************************************************
void eConsoleUser::DoStep_(const fCompleter& _func)
{
	cout << Dump() << endl;
	cout << "Enter position(R1):" << endl;
	string text;
	cin >> text;
	eHitResult res = enemyboard->OnHitted(ePosition(text));
	switch (res)
	{
	case eHitResult::DOUBLESHOT:	_func(true, false);	return;
	case eHitResult::HITTED:		_func(true, true);	return;
	case eHitResult::MISSED:		_func(true, false);	return;
	}
	_func(false, false);
}