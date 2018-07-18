#ifndef SBUJECT_H
#define SBUJECT_H
#include<list>
#include"String.h"
class CSubject
{
public:
	CSubject();
	CSubject(const string&Name, const string&Number);
	~CSubject();
	//���ÿγ̺�
	void SetName(const string &s);
	//���ÿγ���
	void SetNumber(const string &s);
	//���������ĳѧ���ÿƳɼ�
	void AddStudentGrade(const string &StudentNumber, const string &Grade);
	//������ɾ��ĳѧ���ÿƳɼ�
	void DeleteStudentGrade(const string &StudentNumber);
	//�������޸�ĳѧ���ÿƳɼ�
	void EditStudentGrade(const string &StudentNumber, const string &Grade);
	//�������ȡĳѧ���ÿƳɼ�
	string GetStudentGrade(const string&StudentNumber);
	//����==��������Ƚ������ǿγ̺�
	bool operator==(const CSubject&A);
	//��¼����ѡ��ѧ��ѧ����ɼ�������
	list<String>m_lstStudents;
	//��������ѡ��ѧ���ĸÿ�GPA
	float GetGPA();
	//��ȡ�γ�ѧ��
	int GetCredit()const;
	//��ȡ�γ���
	string GetName()const;
	//ÿ���漰GPA�����ݱ����ĺ���ô˺����Ա��
	void Changed();
private:
	//�γ̺�
	string m_szNumber;
	//�γ���
	string m_szName;
	//��¼��ǰ�ÿ����гɼ�GPA
	float m_fGPA;
	//�ÿ�ѧ��
	int m_nCredit;
	//ÿ���漰GPA����Ϣ�����ĺ�m_bChanged��Ϊtrue
	bool m_bChanged;
};





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
	else return -1.f;
}

inline string InputPa(int n=0)
{
	string tem;
	std::cin >> tem;
	if (GetGP(tem) != -1.f)
		return tem;
	else if (tem == string("W"))
	{
		return tem;
	}
	else
	{
		if (n)
			cout << '\r';
		cout << "�Ƿ�����!������������Ч�ɼ�(��������ĸ��ʾ����A+���Ա��������):";
		return InputPa(n++);
	}
}

#endif
