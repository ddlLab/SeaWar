#pragma once

#include <functional>
#include <string>

class eBoard;

using std::string;

class eUser
{
public:
	using fCompleter = std::function<void(bool isSuccess, bool isHitted)>;

public:
	eUser(int id, const string& name);
	eUser()								= delete;
	eUser(const eUser&)					= delete;
	eUser(eUser&&)						= delete;
	virtual ~eUser()					= default;

	eUser& operator=(const eUser&)		= delete;
	eUser& operator=(eUser&&)			= delete;

	void			Init(eBoard* _myBoard, eBoard* _enemyBoard);
	void			Done();


	string			Dump()		const;
	bool			CanStart()	const;

	void			DoStep(const fCompleter& func) { DoStep_(func); }
	const string& 	Name()		const	{ return name;}
protected:
	virtual  void	DoStep_(const fCompleter& func) = 0;
	
	const	int		id			= 0;
	const	string	name;
	const	int		gameId		= 0;
	eBoard*			myboard		= nullptr;
	eBoard*			enemyboard	= nullptr;
};

class eConsoleUser : public eUser
{
public:
	eConsoleUser(int id, const string& name) : eUser(id, name) {}
	eConsoleUser()									= delete;
	eConsoleUser(const eConsoleUser&)				= delete;
	eConsoleUser(eConsoleUser&&)					= delete;
	virtual ~eConsoleUser()							= default;

	eConsoleUser& operator=(const eConsoleUser&)	= delete;
	eConsoleUser& operator=(eConsoleUser&&)			= delete;
protected:
	virtual  void	DoStep_(const fCompleter&) override;
};

