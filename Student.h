#ifndef STUDENT_H
#define STUDENT_H
//------------------------------------------------------------------------
//
//  Name:   Student.h
//
//  Desc:   定义学生类，并给出了一系列操作接口
//
//------------------------------------------------------------------------
#include<list>
#include"String.h"
using namespace std;
#include"Subject.h"
class CStudent
{
public:
	CStudent();
	CStudent(const string&Name, const string&Number);
	~CStudent();

	//设置学生姓名
	void SetName(const string &s);

	//获取学生姓名
	string GetName()const;

	//设置学生学号
	void SetNumber(const string &s);

	//获取学生学号
	string GetNumber()const;

	//向链表添加某课成绩
	void AddSubjectGrade(const string &SubjectNumber,const string& Grade,bool CoverFlag=0);

	//从链表中删除某课成绩
	void DeleteSubjectGrade(const string &SubjectNumber);

	//在链表中修改某课成绩
	void EditSubjectGrade(const string &SubjectNumber, const string& Grade);

	//于链表中找到某课成绩(确保成绩存在后调用)
	string GetSubjectGrade(const string &SubejctNumber);

	//记录了该学生所有课程号与成绩的链表
	list<String>m_lstSubjects;

	//重载==运算符，比较依据是学号
	bool operator==(const CStudent&A);

	//获取当前GPA
	float GetGPA();

	//获取当前总学分
	int GetCredits();
private:
	//记录学生姓名
	string m_szNumber;

	//记录学号
	string m_szName;

	//记录GPA
	float m_fGPA;

	//记录学分
	int m_nCredits;

};


#endif
