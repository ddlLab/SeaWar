#include "Board.h"
#include <sstream>
#include <iomanip>
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
	int c=1;
	std::stringstream os;
	
	DumpHeader(os);
	DumpLineDigit(os, c);
	for (shared_ptr<const eCell> cell : *this)
	{
		os << "|" << cell->ShortDump();
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

void DumpHeader(std::stringstream& os)
{
	string word = "RESPUBLICA";
	os << std::setw(4) << "|";
	for (char s : word)
	{
		os << s << "|";
	}
	os << std::endl;
}

void DumpLineDigit(std::stringstream& os, int c)
{
	os << std::setw(3) << c;
}

void DumpNextLine(std::stringstream& os, int& c)
{
	c++;
	os << "|" << std::endl;
	if (c <= 10)
		DumpLineDigit(os, c);
}