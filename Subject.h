#ifndef SBUJECT_H
#define SBUJECT_H
//------------------------------------------------------------------------
//
//  Name:   Subject.h
//
//  Desc:   定义课程类，并给出了一系列操作接口
//          另外给了两个关于绩点的接口
//
//------------------------------------------------------------------------
#include"ConsoleUtils.h"
#include<list>
#include"String.h"
class CSubject
{
public:
	CSubject();
	CSubject(const string&Name, const string&Number, int Credit);
	~CSubject();

	//设置课程号
	void SetName(const string &s);

	//设置课程名
	void SetNumber(const string &s);

	//向链表添加某学生该科成绩
	void AddStudentGrade(const string &StudentNumber, const string &Grade);

	//从链表删除某学生该科成绩
	void DeleteStudentGrade(const string &StudentNumber);

	//在链表修改某学生该科成绩
	void EditStudentGrade(const string &StudentNumber, const string &Grade);

	//于链表获取某学生该科成绩
	string GetStudentGrade(const string&StudentNumber);

	//重载==运算符，比较依据是课程号
	bool operator==(const CSubject&A);

	//记录所有选课学生学号与成绩的链表
	list<String>m_lstStudents;

	//计算所有选课学生的该科GPA
	float GetGPA();

	//获取课程学分
	int GetCredit()const;

	//获取课程名
	string GetName()const;

	//获取课程号
	string GetNumber()const;

	//改变学分
	void ChangeCredit(int Credit);
private:
	//课程号
	string m_szNumber;

	//课程名
	string m_szName;

	//记录当前该课所有成绩GPA
	float m_fGPA;

	//该课学分
	int m_nCredit;
};


//从字母绩点获取数字显示，当输入非法时返回-1.0f
inline float GetGP(string s)
{
	if (s == string("A+"))
		return 4.0f;
	else if (s == string("A"))
		return 4.0f;
	else if (s == string("A-"))
		return 3.7f;
	else if (s == string("B+"))
		return 3.3f;
	else if (s == string("B"))
		return 3.0f;
	else if (s == string("B-"))
		return 2.7f;
	else if (s == string("C+"))
		return 2.3f;
	else if (s == string("C"))
		return 2.0f;
	else if (s == string("C-"))
		return 1.7f;
	else if (s == string("D+"))
		return 1.3f;
	else if (s == string("D"))
		return 1.0f;
	else if (s == string("F"))
		return 0.0f;
	else if (s == string("P"))
	{
		return -2.0f;
	}
	else return -1.0f;
}

//判断绩点合法性，若是正确字母则直接返回，错误字母要求重新输入
inline string InputPa(int n = 0)
{
	string tem;
	std::cin >> tem;
	if (GetGP(tem) != -1.0f)
		return tem;
	else if (tem == string("W"))
	{
		ClearInput();
		return tem;
	}
	else
	{
		if (n)
			cout << '\r';
		cout << "非法输入!请重新输入有效成绩(必须是字母表示，如A+，以避免二义性):";
		return InputPa(n++);
	}
}

#endif
