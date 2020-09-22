#include "cell.h"
#include <sstream>

//-----------------------------------------------------------------------
eCell::eCell(const ePosition& _pos)
: pos(_pos)
, cellType(eCellType::EMPTY)
{}
//-----------------------------------------------------------------------
string eCell::Dump() const
{
	std::stringstream res;
	res << "cellType:" << ToString(cellType)
		<< ", pos: "   << pos.Dump();
	return res.str();
}
//-----------------------------------------------------------------------
bool eCell::IsValid() const
{
	return IsValidEnum(cellType) && pos.IsValid();
}
//-----------------------------------------------------------------------
void eCell::OnHitted()
{
	switch (cellType)
	{
	case eCellType::ALIVE: cellType = eCellType::HITTED;
	case eCellType::EMPTY: cellType = eCellType::MISSED;
	}
}
