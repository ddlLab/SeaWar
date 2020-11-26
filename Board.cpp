#include "Board.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include "vector_tools.h"


static const size_t MAX_COUNT = 10;

static void DumpHeader(std::stringstream& os);
static void DumpLineDigit(std::stringstream& os, int c);
static void DumpNextLine(std::stringstream& os, int& c);


//-----------------------------------------------------------------------
eBoard::~eBoard()
{
	UnRegisterShips();
}
//-----------------------------------------------------------------------
void eBoard::UnRegisterShips()
{
	for (shared_ptr<eShip> ship : ships)
	{
		ship->UnRegister(this);
	}
	ships.clear();
}
//-----------------------------------------------------------------------
eBoard::eBoard()
:status(eGameStatus::PREPARING)
{
	for (int row = 0; row < 10; row++)
	{
		for (int col = 0; col < 10; col++)
		{
			ePosition p(col, row);
			emplace_back(std::make_shared<eCell>(p));	
		}
	}
}
//-----------------------------------------------------------------------
bool eBoard::CanStart() const
{
	return ships.size()==10;
}
//-----------------------------------------------------------------------
string eBoard::Dump() const
{
	std::stringstream os;
	os << "[";
	for (shared_ptr<const eCell> cell : *this)
	{
		os << "{" << cell->Dump() << "}";
	}
	os << "]";
	return os.str();
}
//-----------------------------------------------------------------------
string eBoard::ShortDump(bool isCurrentPlayer) const
{
	int i=0;
	int c=0;
	std::stringstream os;
	
	DumpHeader(os);
	os << std::endl;
	DumpLineDigit(os, c);
	for (shared_ptr<const eCell> cell : *this)
	{
		os << "|" << cell->ShortDump(isCurrentPlayer);
		i++;
		if (i == 10)// back == last item
		{
			DumpNextLine(os, c);
			i = 0;
		}
	}
	return os.str();
}
//-----------------------------------------------------------------------
bool eBoard::IsValid() const
{
	return IsValidEnum(status)
		&& IsValidTotal(*this) 
		&& IsValidTotal(ships);
}
//-----------------------------------------------------------------------
eHitResult eBoard::OnHitted(const ePosition& _pos) 
{
	eBoard::iterator it = std::find_if(begin(), end(), [_pos](shared_ptr<eCell>& _cell)
	{
		return _cell->Position() == _pos;
	});
	if(it==end())
	{
		return eHitResult::INVALID;
	}
	if(!(*it)->OnHitted())
	{
		return eHitResult::DOUBLESHOT;
	}
	if ((*it)->IsHitted())
	{
		return eHitResult::HITTED;
	}
	return eHitResult::MISSED;
}
//-----------------------------------------------------------------------
bool eBoard::AddShip(shared_ptr<eShip> _ship)
{
	if (CanAddShip(*_ship))
	{
		ships.emplace_back(_ship);
		_ship->Register(this);
		return true;
	}
	_ship->UnRegister(this);
	return false;
}
//-----------------------------------------------------------------------
bool eBoard::CanAddShip(const eShip&  _ship) const
{
	if (status == eGameStatus::PREPARING
		&& _ship.IsPrepared()
		&& ships.size() < MAX_COUNT
		&& LimitNotReached(_ship))
	{
		bool canAdd = true;

		for (const shared_ptr<const eCell>& cellShip : _ship.Cells())
		{
			for (shared_ptr<const eCell> cell : *this)
			{
				if (ShortRoute(cellShip->Position(), cell->Position()) == 1)
				{
					if (!cell->IsMine(&_ship) && !cell->IsEmpty())
					{
						canAdd = false;
						break;
					}
				}
			}
		}
		return canAdd;
	}
	return false;
}
//-----------------------------------------------------------------------
bool eBoard::LimitNotReached(const eShip&  _ship) const
{
	int currentShipsWithSameSize = std::count_if(ships.cbegin(),
											     ships.cend(),
											     [shipSize = _ship.Size()](const shared_ptr<eShip>& shipOnBoard)
	{
		return shipOnBoard->Size() == shipSize;
	});

	switch (_ship.Size())
	{
	//количество палуб
	case 1: return currentShipsWithSameSize < 4;
	case 2: return currentShipsWithSameSize < 3;
	case 3: return currentShipsWithSameSize < 2;
	case 4: return currentShipsWithSameSize < 1;
	}

	return false;
}
//-----------------------------------------------------------------------
bool eBoard::Start()
{
	if (status == eGameStatus::STARTING
		&& IsValid())
	{
		status = eGameStatus::STARTED;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------
shared_ptr<eCell>	eBoard::GetCellByPos(const ePosition& _pos)
{
	eBoard::iterator it = std::find_if(begin(), end(), [_pos](shared_ptr<eCell>& _cell)
	{
		return _cell->Position() == _pos;
	});
	return it != end() ? *it : nullptr;
}

//-----------------------------------------------------------------------
void DumpHeader(std::stringstream& os)
{
	string word = "ABCDEFGHIJ";
	os << std::setw(4) << "|";
	for (char s : word)
	{
		os << s << "|";
	}
}
//-----------------------------------------------------------------------
void DumpLineDigit(std::stringstream& os, int c)
{
	os << std::setw(3) << c;
}
//-----------------------------------------------------------------------
void DumpNextLine(std::stringstream& os, int& c)
{
	c++;
	os << "|" << std::endl;
	if (c <= 10)
		DumpLineDigit(os, c);
}