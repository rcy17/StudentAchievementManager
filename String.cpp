#include "String.h"

String::String(string s) :string(s)
{
}

String::~String()
{
}


string String::GetNumber()
{
	string tem = *this;
	for (auto iterator = tem.begin(); iterator != tem.end(); iterator++)
	{
		if (*iterator > '9' || *iterator < '0')
		{
			tem.erase(iterator, tem.end());
			return tem;
		}
	}
	return tem;
}

string String::GetGrade()
{
	string tem = *this;
	for (auto iterator = tem.begin(); iterator != tem.end(); iterator++)
	{
		if (*iterator > '9' || *iterator < '0')
		{
			tem.erase(tem.begin(), iterator);
			return tem;
		}
	}
	return tem;
}