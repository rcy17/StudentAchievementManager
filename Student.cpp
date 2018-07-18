#include "Student.h"
#include"ConsoleUtils.h"
#include<map>
#include<vector>
//һ����¼��ѧ�ŵ�ѧ����map
extern map<std::string, size_t>g_mNumberToStudent;
//һ����¼�˴ӿγ̺ŵ��γ̵�map
extern map<std::string, size_t>g_mNumberToSubject;
//һ����¼������ѧ����vector
extern vector<CStudent>g_vStudent;
//һ����¼�����пγ̵�vector
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
	GetGPA();//�����Ҫ��һ��ˢ��GPA�뼨�㣬�������Ҫ��ʲô��������
	return m_nCredits;
}

void CStudent::AddSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//�ȱ����������ÿγ̺��Ƿ��Ѿ�����
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			cout << "��ѧ�����пγ̺�Ϊ" << SubjectNumber << "�Ŀ�Ŀ�ɼ�,Ϊ" << iterator->GetGrade() << "���Ƿ��޸ģ�" << endl;
			if (PressAnyKeyToContinue('\r', "��Enter���޸ģ��������������������"))
			{
				iterator->assign(SubjectNumber + Grade);
				cout << "�޸ĳɹ�!" << endl;
				Sleep(1000);
				Changed();
			}
			return;
		}
	}
	m_lstSubjects.push_back(SubjectNumber + Grade);//δ�ҵ���ֱ�����
	Changed();
}

void CStudent::DeleteSubjectGrade(const string &SubjectNumber)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//�ȱ����������ÿγ̺��Ƿ��ѳ���
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			m_lstSubjects.erase(iterator);
			cout << "ɾ���ɹ�!" << endl;
			Sleep(1000);
			Changed();
			return;
		}

	}
	cout << "δ�ҵ��ÿγ���Ϣ��" << endl;//��δ�ҵ��ÿ��򱨸������Ϣ
	PressAnyKeyToContinue();
	return;
}

void CStudent::EditSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)//�ȱ����������ÿγ̺��Ƿ��ѳ���
	{
		if (iterator->GetNumber() == SubjectNumber)//���ҵ���ֱ���޸�
		{
			iterator->assign(SubjectNumber + Grade);
			cout << "�޸ĳɹ�!" << endl;
			Sleep(1000);
			Changed();
			return;
		}

	}
	cout << "δ�ҵ��ÿγ���Ϣ��" << endl;//��δ�ҵ��򱨸������Ϣ
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
	if (!m_bChange)//�������Ҫˢ�£�ֱ�ӷ��ش洢��GPA
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