#include "String.h"

String::String(string s) :string(s)
{
}

String::~String()
{

}

//��ȡ�����е�ѧ��/�γ̺�
string String::GetNumber()
{
	string tem = *this;
	
	//�ܿ��γ̺ŵ�һλ�Ĵ�д��ĸ
	for (auto iterator = tem.begin()+1; iterator != tem.end(); iterator++)
	{
		//������һ������ĸ�󣬽������������ȫ��ɾ��
		if (*iterator > '9' || *iterator < '0')
		{
			tem.erase(iterator, tem.end());
			return tem;
		}
	}
	return tem;
}

//��ȡ�����еĳɼ�
string String::GetGrade()
{
	string tem = *this;

	//��ɾ���γ̺ŵ�һλ�Ĵ�д��ĸ
	auto iterator = tem.begin();
	iterator = tem.erase(iterator);
	for (; iterator != tem.end(); )
	{
		//ɾ��������ÿһ������
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
