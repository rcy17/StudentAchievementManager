#ifndef STRING_H
#define STRING_H
//------------------------------------------------------------------------
//
//  Name:   String.h
//
//  Desc:   定义了一个继承自string的CString类
//
//------------------------------------------------------------------------
#include<string>
#include<iostream>
using namespace std;

//重载了string类从而做到将学号与成绩拼接、拆开
class CString :public string
{
public:
	CString(string);
	~CString();

	//获取学号/课程号
	string GetNumber();

	//获取成绩
	string GetGrade();
private:

};


#endif