#pragma once

#include "enums.h"
#include "tools.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::make_shared;

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
	void				Register(eShip*);	
	void				UnRegister(eShip*); 

	string				Dump()								const;
	string				ShortDump(bool isCurrentPlayer)							const;
	bool				IsValid()							const;

	bool				OnHitted();
	bool				IsMine(const eShip const* _ship)	const	{ return ship == _ship;  }
	bool				IsAlive()							const	{ return cellType == eCellType::ALIVE;  }
	bool				IsEmpty()							const	{ return cellType == eCellType::EMPTY;  }
	bool				IsHitted()							const	{ return cellType == eCellType::HITTED; }
	bool				IsMissed()							const	{ return cellType == eCellType::MISSED; }
	

	const ePosition&	Position() const	{ return pos; }
private:
	eShip*		ship	 = nullptr;
	eCellType	cellType = eCellType::INVALID;
	ePosition	pos;
	
};

class eCells : public vector<shared_ptr<eCell>>
{


};
