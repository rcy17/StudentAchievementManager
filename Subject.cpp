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
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)//�ȱ�����������ѧ���Ƿ��Ѿ�����
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			cout << "ѧ��Ϊ" << StudentNumber << "���иÿƳɼ�,Ϊ" << iterator->GetGrade() << "���Ƿ��޸ģ�" << endl;
			if (PressAnyKeyToContinue('\r', "��Enter���޸ģ��������������������"))
			{
				iterator->assign(StudentNumber + Grade);
				cout << "�޸ĳɹ�!" << endl;
				Sleep(1000);
				Changed();
			}
			return;
		}
	}
	m_lstStudents.push_back(StudentNumber + Grade);//δ�ҵ���ѧ����ֱ�����
	Changed();
}

void CSubject::DeleteStudentGrade(const string &StudentNumber)
{
	
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)//�ȱ��������ҵ���ѧ��
	{
		if (iterator->GetNumber()==StudentNumber)
		{
			m_lstStudents.erase(iterator);
			cout << "ɾ���ɹ���" << endl;
			Sleep(1000);
			Changed();
			return;
		}
	}
	cout << "δ�ҵ���ѧ����Ϣ��" << endl;//��δ�ҵ��򱨸������Ϣ
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
			cout << "�޸ĳɹ�!" << endl;
			Sleep(1000);
			Changed();
			return;
		}
	}
	cout << "δ�ҵ���ѧ����Ϣ��" << endl;
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