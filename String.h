#ifndef STRING_H
#define STRING_H
//------------------------------------------------------------------------
//
//  Name:   String.h
//
//  Desc:   ������һ���̳���string��CString��
//
//------------------------------------------------------------------------
#include<string>
#include<iostream>
using namespace std;

//������string��Ӷ�������ѧ����ɼ�ƴ�ӡ���
class CString :public string
{
public:
	CString(string);
	~CString();

	//��ȡѧ��/�γ̺�
	string GetNumber();

	//��ȡ�ɼ�
	string GetGrade();
private:

};


#endif