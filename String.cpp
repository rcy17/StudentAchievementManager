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
	
	//避开课程号第一位的大写字母
	for (auto iterator = tem.begin()+1; iterator != tem.end(); iterator++)
	{
		//遇到第一个非字母后，将它往后的内容全部删除
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

	//先删除课程号第一位的大写字母
	auto iterator = tem.begin();
	iterator = tem.erase(iterator);
	for (; iterator != tem.end(); )
	{
		//删除遇到的每一个数字
		if (*iterator <= '9' && *iterator >= '0')
		{

			iterator=tem.erase(iterator);
		}
		else
		{
			return tem;
		}
	}
	return tem;
}
