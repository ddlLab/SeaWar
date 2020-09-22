#pragma once
#include <string>
using namespace std;

enum class eCellType
{
	EMPTY,
	ALIVE,
	HITTED,
	MISSED
}; 

enum class eTokenType
{
	COMMAND,
	POSSITION,
	UNKNOWN
};
