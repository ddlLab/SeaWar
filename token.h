#pragma once

#include "enums.h"
#include "tools.h"
#include <vector>

using std::vector;

struct eToken
{
	eToken() = default;
	eToken(eTokenType		_type,
		const std::string& _value)
		: type(_type)
		, value(_value)
	{}
	eToken(eTokenType		_type,
		   ePosition		_from, 
		   ePosition		_to)
		: type(_type)
//		, value(ToString(eCommands::MOVE))
		, from(_from)
		, to(_to)
	{}

	std::string Dump()		const { return "from:" + from.Dump() + "to:" + to.Dump(); } //todo: v zavisimosti ot type dump
	bool		IsValid()	const { return from.IsValid() &&  to.IsValid(); }
	
	eTokenType	type	= eTokenType::UNKNOWN;
	ePosition	from	;
	ePosition	to		;
	std::string value;
};

using eTokens = vector<eToken>;