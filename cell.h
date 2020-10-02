#pragma once

#include "enums.h"
#include "tools.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;

class eShip;

class eCell
{
public:
	eCell(const ePosition&);
	eCell()										= delete;
	eCell(const eCell&)							= default;
	eCell(eCell&&)								= default;
	~eCell()									= default;

	eCell&				operator=(const eCell&)	= default;
	eCell&				operator=(eCell&&)		= default;
	//todo: alex
	void				Register(eShip*);	//set up param ship and change cellType to Alive
	void				UnRegister(eShip*); //reset param ship and change cellType to EMPTY

	string				Dump()					const;
//switch case by cellType and return one char which visin state. for example ALIVE - S HiTTEd - X
	string				ShortDump()				const;
	bool				IsValid()				const;

	void				OnHitted();
	bool				IsAlive()				const	{ return cellType == eCellType::ALIVE; };
	bool				IsEmpty()				const	{ return cellType == eCellType::EMPTY; };
	bool				IsHitted()				const	{ return cellType == eCellType::HITTED; };
	bool				IsPassed()				const	{ return cellType == eCellType::MISSED; };
	
	const ePosition&	Position() const	{ return pos; }
private:
	eShip*		ship	 = nullptr;
	eCellType	cellType = eCellType::INVALID;
	ePosition	pos;
	
};

using eCells = vector<shared_ptr<eCell>>;

//todo: alex
//create class Board and its methods;
//Board must have member enum status Perepared|Starting|Started|Finished
//Board must have member Cells and generate them
//Board must have member Ships
//Board must have methods ToString and CanStart() which check can we change state Perepared->Starting