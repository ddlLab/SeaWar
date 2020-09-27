#pragma once

#include <string>
#include <sstream>

using std::stringstream;
using std::string;

template<class T>
string DumpTotal(const vector<T>& _items)
{
	stringstream ss;
	ss << "[";
	for (const T& i : _items)
	{
		ss<<i.Dump()<<",";
	}
	ss << "]";
	return ss.str();
}

template<class T>
string DumpTotalPtr(const vector<T>& _items)
{
	stringstream ss;
	ss << "[";
	for (const T& i : _items)
	{
		ss << i->Dump()<<",";
	}
	ss << "]";
	return ss.str();
}

template<class T>
bool IsValidTotal(const vector<T>& _items)
{
	for (const T& i : _items)
	{
		if (!i.IsValid())
			return false;
	}
	return true;
}

template<class T>
bool IsValidTotalPtr(const vector<T>& _items)
{
	for (const T& i : _items)
	{
		if (!i->IsValid())
			return false;
	}
	return true;
}