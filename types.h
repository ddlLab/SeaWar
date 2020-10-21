#pragma once

#include <string>
#include <sstream>
#include <stdexcept>

using std::string;
using std::istream;
using std::ostream;

// Search and remove whitespace from both ends of the string
static std::string TrimEnumString(const std::string &s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isspace(*it)) { it++; }
	std::string::const_reverse_iterator rit = s.rbegin();
	while (rit.base() != it && isspace(*rit)) { rit++; }
	return std::string(it, rit.base());
}
static void SplitEnumArgs(const char* szArgs, std::string Array[], int nMax)
{
	std::stringstream ss(szArgs);
	std::string strSub;
	int nIdx = 0;
	while (ss.good() && (nIdx < nMax)) {
		getline(ss, strSub, ',');
		Array[nIdx] = TrimEnumString(strSub);
		nIdx++;
	}
};

template<class T> static T FromString(const string&) { return T();  }

//#define DECLARE_ENUM(ename, ...) \
//    enum ename { __VA_ARGS__, MAX_NUMBER_OF_##ename }; \
//    static std::string ename##Strings[MAX_NUMBER_OF_##ename]; \
//    static const char* ename##ToString(ename e) { \
//        if (ename##Strings[0].empty()) { SplitEnumArgs(#__VA_ARGS__, ename##Strings, MAX_NUMBER_OF_##ename); } \
//        return ename##Strings[e].c_str(); \
//    } \
//    static ename StringTo##ename(const char* szEnum) { \
//        for (int i = 0; i < MAX_NUMBER_OF_##ename; i++) { if (ename##Strings[i] == szEnum) { return (ename)i; } } \
//        return MAX_NUMBER_OF_##ename; \
//    }

#define DECLARE_ENUM_CLASS(ename, ...)																				\
    enum class ename : int { INVALID=-1, __VA_ARGS__, TOTAL };														\
																													\
    static std::string ename##Strings[(int)ename::TOTAL];															\
																													\
    static std::string ToString(ename e) {																			\
		if(e==ename::INVALID)																						\
			return "INVALID";																						\
		if (ename##Strings[0].empty()) { SplitEnumArgs(#__VA_ARGS__, ename##Strings, (int)ename::TOTAL); }			\
        return ename##Strings[(int)e];																				\
    }																												\
																													\
   template<> static ename FromString(const string& szEnum) {														\
		if("INVALID" == szEnum)																						\
			return ename::INVALID;																					\
		if (ename##Strings[0].empty()) { SplitEnumArgs(#__VA_ARGS__, ename##Strings, (int)ename::TOTAL); }			\
       for (int i = 0; i < (int)ename::TOTAL; i++) { if (ename##Strings[i] == szEnum) { return (ename)i; } }		\
       return ename::INVALID;																						\
   }																												\
																													\
	static ostream& operator<<(ostream& _os, ename _item)															\
	{																												\
		_os << ToString(_item);																						\
		return _os;																									\
	}																												\
																													\
	static istream& operator>>(istream& _is, ename& _item)															\
	{																												\
		string item;																								\
		_is >> item;																								\
		_item = FromString<ename>(item);																			\
		return _is;																									\
	}																												\
																													\
	static bool IsValidEnum(ename _item)	{ return _item != ename::INVALID && _item != ename::TOTAL;  }			\
	

#define DEFINE_SIMPLE_STATE(type, var, method)		   \
public:												   \
	type      method() const		 { return var; }   \
	void      method(type _var)		 { var = _var; }   \
private:											   \

#define DEFINE_SIMPLE_FIELD(type, var, method)						   \
public:																   \
	const type&     method() const					 { return var; }   \
	void			method(const type& _var)		 { var = _var; }   \
private:															   \

#define DEFINE_SIMPLE_FIELD_REF(type, var, method)						\
public:																	\
	const type&     method() const					 { return var; }	\
		  type&     method()						 { return var; }	\
private:															    \

#define DEFINE_SIMPLE_FIELD_TOTAL(type, var, method)						\
	DEFINE_SIMPLE_FIELD(type, var, method)									\
public:																		\
	type&				method()						 { return var; }	\
private:																	\
