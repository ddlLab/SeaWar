#pragma once

#include <string>
#include <sstream>
#include "sfinae_types.h"

using std::stringstream;
using std::string;

template<class T>
typename std::enable_if<is_pointer_type<T>::value, string>::type
DumpTotal(const vector<T>& _items,const string& sep = ",")
{
	stringstream ss;
	ss << "[";
	for (size_t i = 0; i < _items.size(); ++i)
	{
		ss << "(" << _items[i]->Dump() << ")";
		if (i != _items.size() - 1)
		{
			ss << sep;
		}
	}
	ss << "]";
	return ss.str();
}

template<class T>
typename std::enable_if<!is_pointer_type<T>::value, string>::type
DumpTotal(const vector<T>& _items, const string& sep = ",")
{
	stringstream ss;
	ss << "[";
	for (size_t i = 0; i < _items.size(); ++i)
	{
		ss <<"("<< _items[i].Dump()<<")";
		if (i != _items.size() - 1)
		{
			ss << sep;
		}
	}
	ss << "]";
	return ss.str();
}

template<class T>
typename std::enable_if<!is_pointer_type<T>::value, bool>::type
 IsValidTotal(const vector<T>& _items)
{
	for (const T& i : _items)
	{
		if (!i.IsValid())
			return false;
	}
	return true;
}

template<class T>
typename std::enable_if<is_pointer_type<T>::value, bool>::type
 IsValidTotal(const vector<T>& _items)
{
	for (const T& i : _items)
	{
		if (!i->IsValid())
			return false;
	}
	return true;
}