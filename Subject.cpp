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

//�趨�γ���
void CSubject::SetName(const string &s)
{
	m_szName = s;
}

//�趨�γ̺�
void CSubject::SetNumber(const string &s)
{
	m_szNumber = s;
}

//���������ĳѧ���ÿƳɼ�
void CSubject::AddStudentGrade(const string &StudentNumber, const string &Grade)
{
	//�ȱ�����������ѧ���Ƿ��Ѿ�����
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			cout << "ѧ��Ϊ" << StudentNumber << "���иÿƳɼ�,Ϊ" << iterator->GetGrade() << "���Ƿ��޸ģ�" << endl;
			if (PressAnyKeyToContinue('\r', "��Enter���޸ģ��������������������"))
			{
				iterator->assign(StudentNumber + Grade);
			}
			return;
		}
	}
	m_lstStudents.push_back(StudentNumber + Grade);//δ�ҵ���ѧ����ֱ�����
}

//������ɾ��ĳѧ���ÿƳɼ�
void CSubject::DeleteStudentGrade(const string &StudentNumber)
{
	//�ȱ��������ҵ���ѧ��
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			m_lstStudents.erase(iterator);
			return;
		}
	}
	cout << "δ�ҵ���ѧ����Ϣ��" << endl;//��δ�ҵ��򱨸������Ϣ
	PressAnyKeyToContinue();
	return;
}

//�������޸�ĳѧ���ÿƳɼ�
void CSubject::EditStudentGrade(const string &StudentNumber, const string& grade)
{
	//�ȱ����ҵ��ÿ���Ϣ
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			iterator->assign(StudentNumber + grade);
			return;
		}
	}
	cout << "δ�ҵ���ѧ����Ϣ��" << endl;//δ�ҵ��򱨸������Ϣ
	PressAnyKeyToContinue();
	return;
}

//�������ȡĳѧ���ÿƳɼ�
string CSubject::GetStudentGrade(const string&StudentNumber)
{
	//�ȱ����������ҵ��ÿ���Ϣ
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		if (iterator->GetNumber() == StudentNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");//δ�ҵ��򷵻�W
}

//��ȡ�ÿ�ƽ���ɼ�
float CSubject::GetGPA()
{
	float Sum = 0.f;
	size_t Count = m_lstStudents.size();
	for (auto iterator = m_lstStudents.begin(); iterator != m_lstStudents.end(); iterator++)
	{
		//ͬ��Ŀ���㣬ֻ��Ը���ѧ���ɼ������ֵ
		float GP = GetGP(iterator->GetGrade());

		//����ѧ������P����ô��Ϊ�˿�ΪP/F�γ̣�������GPA
		//����������ʦ����¼��ɼ���ϵͳ����������ѧ���ֶ���P/F��ɵ�Ӱ��
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

//��ȡ�ÿ�ѧ��
int CSubject::GetCredit()const
{
	return m_nCredit;
}

//��ȡ�γ���
string CSubject::GetName()const
{
	return m_szName;
}

//��ȡ�γ̺�
string CSubject::GetNumber()const
{
	return m_szNumber;
}

//����==���Կγ̺�Ϊ�Ƚ�����
bool CSubject::operator==(const CSubject&A)
{
	if (A.m_szNumber == m_szNumber)
		return true;
	return false;
}

//�ı�γ�ѧ��
void CSubject::ChangeCredit(int Credit)
{
	m_nCredit = Credit;
}
