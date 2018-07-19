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

CStudent::CStudent() :m_fGPA(0), m_nCredits(0)
{

}

CStudent::CStudent(const string&Name, const string&Number) : m_szName(Name), m_szNumber(Number),
m_fGPA(0), m_nCredits(0)
{

}

CStudent::~CStudent()
{
	m_szName.clear();
	m_szNumber.clear();
	m_lstSubjects.clear();
}

//设定学生姓名
void CStudent::SetName(const string&s)
{
	m_szName = s;
}

//设定学生学号
void CStudent::SetNumber(const string&s)
{
	m_szNumber = s;
}

//获取学生姓名
string CStudent::GetName()const
{
	return m_szName;
}

//获取学生学号
string CStudent::GetNumber()const
{
	return m_szNumber;
}

//获取学生所修学分数
int CStudent::GetCredits()
{
	m_nCredits = 0;
	//遍历所修课程，累加学分，如果挂科则不计入学分
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetGrade == string("F"))
			continue;
		m_nCredits += g_vSubject[(g_mNumberToSubject.find(iterator->GetNumber()))->second].GetCredit();
	}
	return m_nCredits;
}

//获取学生所有课的GPA
float CStudent::GetGPA()
{
	float Sum = 0.0f;
	m_nCredits = 0;
	//遍历所修课程，累加绩点与学分，并求均值
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		string Number = iterator->GetNumber();
		auto it = g_mNumberToSubject.find(Number);
		size_t Label = it->second;
		int Credit = g_vSubject[Label].GetCredit();
		//int Credit = g_vSubject[(g_mNumberToSubject.find(iterator->GetNumber()))->second].GetCredit();
		float GP = GetGP(iterator->GetGrade());
		
		//若某课PF，则不计入计算
		if (GP == -2.0f)
		{
			continue;
		}
		Sum += GP * Credit;
		m_nCredits += Credit;
	}

	//若暂无有效学分，则无法得到有效GPA
	if (!m_nCredits)
		return -1.0f;
	return m_fGPA = Sum / m_nCredits;
}

//向链表添加某课成绩
void CStudent::AddSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	//先遍历链表看看该课程号是否已经出现
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			cout << "该学生已有课程号为" << SubjectNumber << "的科目成绩,为" << iterator->GetGrade() <<
				"，是否修改？" << endl;
			if (PressAnyKeyToContinue('\r', "按Enter键修改，按其他任意键放弃操作"))
			{
				iterator->assign(SubjectNumber + Grade);
				cout << "修改成功!" << endl;
				Sleep(1000);
			}
			return;
		}
	}
	m_lstSubjects.push_back(SubjectNumber + Grade);//未找到则直接添加
}

//从链表中删除某课成绩
void CStudent::DeleteSubjectGrade(const string &SubjectNumber)
{
	//先遍历链表看看该课程号是否已出现
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			m_lstSubjects.erase(iterator);
			cout << "删除成功!" << endl;
			Sleep(1000);
			return;
		}
	}
	cout << "未找到该课程信息！" << endl;//若未找到该课则报告错误信息
	PressAnyKeyToContinue();
	return;
}

//在链表中修改某课成绩
void CStudent::EditSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	//先遍历链表看看该课程号是否已出现
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)//若找到则直接修改
		{
			iterator->assign(SubjectNumber + Grade);
			cout << "修改成功!" << endl;
			Sleep(1000);
			return;
		}

	}
	cout << "未找到该课程信息！" << endl;//若未找到则报告错误信息
	PressAnyKeyToContinue();
	return;
}

//于链表中找到某课成绩(确保成绩存在后调用)
string CStudent::GetSubjectGrade(const string &SubjectNumber)
{
	//遍历所修课程以找到目标
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");
}

//重载==操作符，以学号为对比依据
bool CStudent::operator==(const CStudent&A)
{
	if (A.m_szNumber == m_szNumber)
		return true;
	return false;
}

