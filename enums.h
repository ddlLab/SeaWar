#pragma once

#include "types.h"

DECLARE_ENUM_CLASS(eCellType,
	EMPTY,
	ALIVE,
	HITTED,
	MISSED
); 

DECLARE_ENUM_CLASS(eTokenType,
	COMMAND,
	POSSITION);