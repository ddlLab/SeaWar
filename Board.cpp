#include "Board.h"
#include <sstream>
#include "vector_tools.h"


static const size_t MAX_COUNT = 10;

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
	for (int col = 0; col < 10; col++)
	{
		for (int row = 0; row < 10; row++)
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
string eBoard::ShortDump() const
{
	int i=0;
	std::stringstream os;
	for (shared_ptr<const eCell> cell : *this)
	{
		os << "|" << cell->ShortDump();
		i++;
		if (i == 10)
		{
			i = 0;
			os << "|\n";
		}

	}
	return os.str();
}
bool eBoard::IsValid() const
{
	return IsValidEnum(status)
		&& IsValidTotal(*this) 
		&& IsValidTotal(ships);
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
//	UnRegister(_ship);
	return false;
}
//-----------------------------------------------------------------------
bool eBoard::CanAddShip(const eShip&  _ship) const
{
	if (status == eGameStatus::PREPARING
		/*&& number of ships*/
		&& _ship.IsPrepared()
		&& ships.size() < MAX_COUNT)
	{
		//todo dima:
		//1. check that we has place for this ship
		// for example we can add only 4 - 1floor ships
		//3 - 2 floors, etc 
		//can use count_if  from library algrithm
		bool canAdd = true;
		for (const shared_ptr<const eCell> cell : _ship.Cells())
		{
			//find all cells around this
			// for exmaple you can use copy_if from library algrithm
			//after you find all around this cell 
			//you can use for loop for finded items
			//in for loop you can check that cell  IsEmpty or IsMine 
			//if condition not exec canAdd =  false and break forLoop
			
			//* in lambda-expr you can capture some info in [] breaks
			//for example int i=5; find_if(begin(), end(), [i](int val)
			//{
			//	return i == val; //I capture "i" in my lambda
			//})
		}
		return canAdd;
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