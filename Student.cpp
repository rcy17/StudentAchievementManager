#include "Student.h"
#include"ConsoleUtils.h"
#include<map>
#include<vector>
//一个记录从学号到学生的map
extern map<std::string, size_t>g_mNumberToStudent;
//一个记录了从课程号到课程的map
extern map<std::string, size_t>g_mNumberToSubject;
//一个记录了所有学生的vector
extern vector<CStudent>g_vStudent;
//一个记录了所有课程的vector
extern vector<CSubject>g_vSubject;

CStudent::CStudent() :m_bChange(true), m_fGPA(0),m_nCredits(0)
{

}

CStudent::CStudent(const string&Name, const string&Number) : m_szName(Name), m_szNumber(Number),
m_bChange(true), m_fGPA(0),m_nCredits(0)
{

}

CStudent::~CStudent()
{
	m_szName.clear();
	m_szNumber.clear();
	m_lstSubjects.clear();
}

void CStudent::SetName(const string&s)
{
	m_szName = s;
}

void CStudent::SetNumber(const string&s)
{
	m_szNumber = s;
}

string CStudent::GetName()const
{
	return m_szName;
}

string CStudent::GetNumber()const
{
	return m_szNumber;
}

int CStudent::GetCredits()
{
	GetGPA();//如果需要，一次刷新GPA与绩点，如果不需要则什么都不会做
	return m_nCredits;
}

void CStudent::AddSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//先遍历链表看看该课程号是否已经出现
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			cout << "该学生已有课程号为" << SubjectNumber << "的科目成绩,为" << iterator->GetGrade() << "，是否修改？" << endl;
			if (PressAnyKeyToContinue('\r', "按Enter键修改，按其他任意键放弃操作"))
			{
				iterator->assign(SubjectNumber + Grade);
				cout << "修改成功!" << endl;
				Sleep(1000);
				Changed();
			}
			return;
		}
	}
	m_lstSubjects.push_back(SubjectNumber + Grade);//未找到则直接添加
	Changed();
}

void CStudent::DeleteSubjectGrade(const string &SubjectNumber)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//先遍历链表看看该课程号是否已出现
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			m_lstSubjects.erase(iterator);
			cout << "删除成功!" << endl;
			Sleep(1000);
			Changed();
			return;
		}

	}
	cout << "未找到该课程信息！" << endl;//若未找到该课则报告错误信息
	PressAnyKeyToContinue();
	return;
}

void CStudent::EditSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//先遍历链表看看该课程号是否已出现
	{
		if (iterator->GetNumber() == SubjectNumber)//若找到则直接修改
		{
			iterator->assign(SubjectNumber + Grade);
			cout << "修改成功!" << endl;
			Sleep(1000);
			Changed();
			return;
		}

	}
	cout << "未找到该课程信息！" << endl;//若未找到则报告错误信息
	PressAnyKeyToContinue();
	return;
}

string CStudent::GetSubjectGrade(const string &SubjectNumber)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");
}

float CStudent::GetGPA()
{
	if (!m_bChange)//如果不需要刷新，直接返回存储的GPA
		return m_fGPA;
	m_bChange = false;
	float Sum = 0.0f;
	m_nCredits = 0;
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		int Credit = g_vSubject[(g_mNumberToSubject.find(iterator->GetNumber())->second)].GetCredit();
		Sum +=GetGP(iterator->GetGrade()) * Credit;
		m_nCredits += Credit;
	}

	return m_fGPA = Sum / m_nCredits;
}

bool CStudent::operator==(const CStudent&A)
{
	if (A.m_szName == m_szName)
		return true;
	return false;
}

void CStudent::Changed()
{
	m_bChange = true;
}

void CStudent::EditName(const string&Name)
{
	m_szName = Name;
}