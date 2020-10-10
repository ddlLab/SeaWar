#include "Board.h"
#include <sstream>


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

bool eBoard::CanStart() const
{
	return ships.size()==10;
}

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