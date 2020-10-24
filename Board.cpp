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
//-----------------------------------------------------------------------
string eBoard::ToString() const
{
	switch (status)
	{
	case eGameStatus::PREPARING: return  "Preparing";
	case eGameStatus::STARTING: return  "Starting";
	case eGameStatus::STARTED: return  "Started";
	case eGameStatus::FINISHED: return  "Finished";
	}
}
//-----------------------------------------------------------------------
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
	return false;
}
/*/-----------------------------------------------------------------------
bool eBoard::CanAddShip(const eShip&  _ship) const
{
	eShip ship;
	int number;
	int max_number;
	if (status == eGameStatus::PREPARING
		/*&& number of ships/
		&& _ship.IsPrepared()
		&& ships.size() < MAX_COUNT)
	{
		switch (ship.size)
		{
		case ship.size(4): max_number=1;
		case ship.size(3): max_number=2;
		case ship.size(2): max_number=3;
		case ship.size(1): max_number=4;
		}
		if (number < max_number)
		{
			bool canAdd = true;
		}
		for (const shared_ptr<const eCell> cell : _ship.Cells())
		{

		}
		return canAdd;
	}
	return false;
}
/*///-----------------------------------------------------------------------
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