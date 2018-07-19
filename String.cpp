#include "String.h"

String::String(string s) :string(s)
{
}

String::~String()
{

}

//读取数据中的学号/课程号
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

//读取数据中的成绩
string String::GetGrade()
{
	string tem = *this;
	for (auto iterator = tem.begin()+1; iterator != tem.end(); )
	{
		if (*iterator <= '9' && *iterator >= '0')
		{

			iterator=tem.erase(iterator);
		}
		else
			return tem;
	}
	return tem;
}
