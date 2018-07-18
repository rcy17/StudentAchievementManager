#include "Subject.h"
#include "ConsoleUtils.h"
CSubject::CSubject():m_bChanged(true),m_fGPA(0)
{

}

CSubject::CSubject(const string&Name, const string&Number,int Credit) :m_szName(Name), m_szNumber(Number),
m_bChanged(true), m_fGPA(0),m_nCredit(Credit)
{

}

CSubject::~CSubject()
{
	m_szName.clear();
	m_szNumber.clear();
	m_lstStudents.clear();
}

void CSubject::SetName(const string &s)
{
	m_szName = s;
}

void CSubject::SetNumber(const string &s)
{
	m_szNumber = s;
}

void CSubject::AddStudentGrade(const string &StudentNumber,const string &Grade)
{
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)//先遍历链表看看该学号是否已经出现
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			cout << "学号为" << StudentNumber << "已有该科成绩,为" << iterator->GetGrade() << "，是否修改？" << endl;
			if (PressAnyKeyToContinue('\r', "按Enter键修改，按其他任意键放弃操作"))
			{
				iterator->assign(StudentNumber + Grade);
				cout << "修改成功!" << endl;
				Sleep(1000);
				Changed();
			}
			return;
		}
	}
	m_lstStudents.push_back(StudentNumber + Grade);//未找到该学号则直接添加
	Changed();
}

void CSubject::DeleteStudentGrade(const string &StudentNumber)
{
	
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)//先遍历链表找到该学生
	{
		if (iterator->GetNumber()==StudentNumber)
		{
			m_lstStudents.erase(iterator);
			cout << "删除成功！" << endl;
			Sleep(1000);
			Changed();
			return;
		}
	}
	cout << "未找到该学生信息！" << endl;//若未找到则报告错误信息
	PressAnyKeyToContinue();
	return;
}

void CSubject::EditStudentGrade(const string &StudentNumber,const string& grade)
{
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			iterator->assign(StudentNumber + grade);
			cout << "修改成功!" << endl;
			Sleep(1000);
			Changed();
			return;
		}
	}
	cout << "未找到该学生信息！" << endl;
	PressAnyKeyToContinue();
	return;
}

string CSubject::GetStudentGrade(const string&StudentNumber)
{
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");
}

float CSubject::GetGPA()
{
	if (!m_bChanged)
		return m_fGPA;
	m_bChanged = false;
	float Sum = 0.f;
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		Sum +=GetGP(iterator->GetGrade());
	}
	return m_fGPA = Sum / m_lstStudents.size();
}

int CSubject::GetCredit()const
{
	return m_nCredit;
}

string CSubject::GetName()const
{
	return m_szName;
}

bool CSubject::operator==(const CSubject&A)
{
	if (A.m_szName == m_szName)
		return true;
	return false;
}

void CSubject::Changed()
{
	m_bChanged = true;
}


void CSubject::EditName(const string&Name)
{
	m_szName = Name;
}

void CSubject::ChangeCredit(int Credit)
{
	m_nCredit = Credit;
}