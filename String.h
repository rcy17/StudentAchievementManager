#ifndef STRING_H
#define STRING_H
//------------------------------------------------------------------------
//
//  Name:   String.h
//
//  Desc:   ������һ���̳���string��String��
//
//------------------------------------------------------------------------
#include<string>
#include<iostream>
using namespace std;

//������string��Ӷ�������ѧ����ɼ�ƴ�ӡ���
class String :public string
{
public:
	String(string);
	~String();

	//��ȡѧ��/�γ̺�
	string GetNumber();

	//��ȡ�ɼ�
	string GetGrade();
private:

};


#endif