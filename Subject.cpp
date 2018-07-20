#include "Subject.h"
#include "ConsoleUtils.h"
#include<map>
#include<vector>


CSubject::CSubject() :m_fGPA(0)
{

}

CSubject::CSubject(const string&Name, const string&Number, int Credit) : m_szName(Name), m_szNumber(Number),
m_fGPA(0), m_nCredit(Credit)
{

}

CSubject::~CSubject()
{
	m_szName.clear();
	m_szNumber.clear();
	m_lstStudents.clear();
}

//设定课程名
void CSubject::SetName(const string &s)
{
	m_szName = s;
}

//设定课程号
void CSubject::SetNumber(const string &s)
{
	m_szNumber = s;
}

//向链表添加某学生该科成绩
void CSubject::AddStudentGrade(const string &StudentNumber, const string &Grade)
{
	//先遍历链表看看该学号是否已经出现
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			cout << "学号为" << StudentNumber << "已有该科成绩,为" << iterator->GetGrade() << "，是否修改？" << endl;
			if (PressAnyKeyToContinue('\r', "按Enter键修改，按其他任意键放弃操作"))
			{
				iterator->assign(StudentNumber + Grade);
			}
			return;
		}
	}
	m_lstStudents.push_back(StudentNumber + Grade);//未找到该学号则直接添加
}

//从链表删除某学生该科成绩
void CSubject::DeleteStudentGrade(const string &StudentNumber)
{
	//先遍历链表找到该学生
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			m_lstStudents.erase(iterator);
			return;
		}
	}
	cout << "未找到该学生信息！" << endl;//若未找到则报告错误信息
	PressAnyKeyToContinue();
	return;
}

//在链表修改某学生该科成绩
void CSubject::EditStudentGrade(const string &StudentNumber, const string& grade)
{
	//先遍历找到该科信息
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			iterator->assign(StudentNumber + grade);
			return;
		}
	}
	cout << "未找到该学生信息！" << endl;//未找到则报告错误信息
	PressAnyKeyToContinue();
	return;
}

//于链表获取某学生该科成绩
string CSubject::GetStudentGrade(const string&StudentNumber)
{
	//先遍历链表以找到该科信息
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");//未找到则返回W
}

//获取该科平均成绩
float CSubject::GetGPA()
{
	float Sum = 0.f;
	size_t Count = m_lstStudents.size();
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		//同科目运算，只需对各个学生成绩简单求均值
		float GP = GetGP(iterator->GetGrade());

		//若有学生记了P，那么认为此课为P/F课程，不计算GPA
		//由于这是老师管理录入成绩的系统，并不考虑学生手动记P/F造成的影响
		if (GP == -2.0f)
		{
			return -2.0f;
		}
		else
		{
			Sum += GP;
		}
	}
	return m_fGPA = Sum / Count;
}

//获取该科学分
int CSubject::GetCredit()const
{
	return m_nCredit;
}

//获取课程名
string CSubject::GetName()const
{
	return m_szName;
}

//获取课程号
string CSubject::GetNumber()const
{
	return m_szNumber;
}

//重载==，以课程号为比较依据
bool CSubject::operator==(const CSubject&A)
{
	if (A.m_szNumber == m_szNumber)
		return true;
	return false;
}

//改变课程学分
void CSubject::ChangeCredit(int Credit)
{
	m_nCredit = Credit;
}
