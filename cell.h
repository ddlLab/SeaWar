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

	void				Register(eShip*);
//	void				UnRegister(eShip*);

	string				Dump()					const;
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