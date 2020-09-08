#include "tools.h"


const char START_COL	= 'a';
const char END_COL		= 'j';
const char START_ROW	= '0';
const char END_ROW		= '9';

std::string ePosition::Dump()	const 
{
	std::string t;
	t += col;

	if (row == END_ROW)
	{
		t += "10";
	}
	else
	{
		t += (row + 1);
	}
	return t;
}


void GetTraektory(const ePosition& _from, const ePosition& _to, vector<ePosition>& _traektory)
{
	_traektory.clear();
	int diffX = _from.XToBoard() - _to.XToBoard();
	int diffY = _from.YToBoard() - _to.YToBoard();
	if (_from == _to
		|| abs(diffX) == 1 && (diffY == 0 || abs(diffY == 1))
		|| abs(diffY) == 1 && (diffX == 0 && abs(diffX == 1))
	)	
	{
		return;
	}
	bool isFromRightToLeft = diffX > 0;
	bool isFromBottomToUpper = diffY > 0;
	if (diffY == 0)
	{
		for (int i = _from.XToBoard(); i != _to.XToBoard(); isFromRightToLeft ? --i : ++i)
		{
			ePosition pos(i, _from.YToBoard());
			if (pos != _from && pos != _to)
			{
				_traektory.emplace_back(pos);
			}

		}
		return;
	}
	if (diffX == 0)
	{
		for (int i = _from.YToBoard(); i != _to.YToBoard(); isFromBottomToUpper ? --i : ++i)
		{
			ePosition pos(_from.XToBoard(), i);
			if (pos != _from && pos != _to)
			{
				_traektory.emplace_back(pos);
			}

		}
		return;
	}
	for (int i = _from.YToBoard(), j = _from.XToBoard(); i != _to.YToBoard() && j != _to.XToBoard();
		isFromBottomToUpper ? --i : ++i, j = isFromRightToLeft ? --j : ++j)
	{
		ePosition pos(j, i);
		if (pos != _from && pos != _to)
		{
			_traektory.emplace_back(pos);
		}
	}


}