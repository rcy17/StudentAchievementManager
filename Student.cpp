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

//�趨ѧ������
void CStudent::SetName(const string&s)
{
	m_szName = s;
}

//�趨ѧ��ѧ��
void CStudent::SetNumber(const string&s)
{
	m_szNumber = s;
}

//��ȡѧ������
string CStudent::GetName()const
{
	return m_szName;
}

//��ȡѧ��ѧ��
string CStudent::GetNumber()const
{
	return m_szNumber;
}

//��ȡѧ������ѧ����
int CStudent::GetCredits()
{
	m_nCredits = 0;
	//�������޿γ̣��ۼ�ѧ�֣�����ҿ��򲻼���ѧ��
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetGrade == string("F"))
			continue;
		m_nCredits += g_vSubject[(g_mNumberToSubject.find(iterator->GetNumber()))->second].GetCredit();
	}
	return m_nCredits;
}

//��ȡѧ�����пε�GPA
float CStudent::GetGPA()
{
	float Sum = 0.0f;
	m_nCredits = 0;
	//�������޿γ̣��ۼӼ�����ѧ�֣������ֵ
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		string Number = iterator->GetNumber();
		auto it = g_mNumberToSubject.find(Number);
		size_t Label = it->second;
		int Credit = g_vSubject[Label].GetCredit();
		//int Credit = g_vSubject[(g_mNumberToSubject.find(iterator->GetNumber()))->second].GetCredit();
		float GP = GetGP(iterator->GetGrade());
		
		//��ĳ��PF���򲻼������
		if (GP == -2.0f)
		{
			continue;
		}
		Sum += GP * Credit;
		m_nCredits += Credit;
	}

	//��������Чѧ�֣����޷��õ���ЧGPA
	if (!m_nCredits)
		return -1.0f;
	return m_fGPA = Sum / m_nCredits;
}

//���������ĳ�γɼ�
void CStudent::AddSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	//�ȱ����������ÿγ̺��Ƿ��Ѿ�����
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			cout << "��ѧ�����пγ̺�Ϊ" << SubjectNumber << "�Ŀ�Ŀ�ɼ�,Ϊ" << iterator->GetGrade() <<
				"���Ƿ��޸ģ�" << endl;
			if (PressAnyKeyToContinue('\r', "��Enter���޸ģ��������������������"))
			{
				iterator->assign(SubjectNumber + Grade);
				cout << "�޸ĳɹ�!" << endl;
				Sleep(1000);
			}
			return;
		}
	}
	m_lstSubjects.push_back(SubjectNumber + Grade);//δ�ҵ���ֱ�����
}

//��������ɾ��ĳ�γɼ�
void CStudent::DeleteSubjectGrade(const string &SubjectNumber)
{
	//�ȱ����������ÿγ̺��Ƿ��ѳ���
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			m_lstSubjects.erase(iterator);
			cout << "ɾ���ɹ�!" << endl;
			Sleep(1000);
			return;
		}
	}
	cout << "δ�ҵ��ÿγ���Ϣ��" << endl;//��δ�ҵ��ÿ��򱨸������Ϣ
	PressAnyKeyToContinue();
	return;
}

//���������޸�ĳ�γɼ�
void CStudent::EditSubjectGrade(const string &SubjectNumber, const string &Grade)
{
	//�ȱ����������ÿγ̺��Ƿ��ѳ���
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)//���ҵ���ֱ���޸�
		{
			iterator->assign(SubjectNumber + Grade);
			cout << "�޸ĳɹ�!" << endl;
			Sleep(1000);
			return;
		}

	}
	cout << "δ�ҵ��ÿγ���Ϣ��" << endl;//��δ�ҵ��򱨸������Ϣ
	PressAnyKeyToContinue();
	return;
}

//���������ҵ�ĳ�γɼ�(ȷ���ɼ����ں����)
string CStudent::GetSubjectGrade(const string &SubjectNumber)
{
	//�������޿γ����ҵ�Ŀ��
	for (auto iterator = m_lstSubjects.begin(); iterator != m_lstSubjects.end(); iterator++)
	{
		if (iterator->GetNumber() == SubjectNumber)
		{
			return iterator->GetGrade();
		}
	}
	return string("W");
}

//����==����������ѧ��Ϊ�Ա�����
bool CStudent::operator==(const CStudent&A)
{
	if (A.m_szNumber == m_szNumber)
		return true;
	return false;
}

