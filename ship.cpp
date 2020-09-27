#include "ship.h"
#include <sstream>

//-----------------------------------------------------------------------
string eShip::Dump() const
{
	std::stringstream res;
	res << "shipStatus:" << shipStatus
		<< ", pos: " << pos.Dump();
	return res.str();
}
//-----------------------------------------------------------------------
void eShip::OnHitted()
{
	switch (shipStatus)
	{
	
	}
}