#include "text_functions.h"
#include <sstream>

using std::stringstream;

//-------------------------------------------------------------
void Split(const string& from, vector<string>& to, const string& sep)
{
	to.clear();
	size_t prev = 0;
	size_t next = 0;
	if (!sep.empty())
	{
		while ((next = from.find(sep, prev)) != string::npos)
		{
			to.emplace_back(from.substr(prev, next - prev));
			prev = next + sep.size();
		}
	}
	else
	{
		for (char t : from)
		{
			to.emplace_back(string(1, t));
		}
	}
}
//-------------------------------------------------------------
void Split(const string& from, vector<string>& to, char	sep)
{
	Split(from, to, string(1, sep));
}
//-------------------------------------------------------------
void Join(const vector<string>& from, string& to, const string& sep)
{
	stringstream res;
	to.clear();
	for (size_t i = 0; i < from.size(); ++i)
	{
		res << from[i];
		if (i != from.size() - 1)
		{
			res << sep;
		}
	}
	to = res.str();
}
//-------------------------------------------------------------
void Join(const vector<string>& from, string& to, char sep)
{
	Join(from, to, string(1, sep));
}