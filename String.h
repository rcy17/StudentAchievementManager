#ifndef STRING_H
#define STRING_H
#include<string>
#include<iostream>
using namespace std;

class String :public string
{
public:
	String(string);
	~String();
	string GetNumber();
	string GetGrade();
private:

};


#endif