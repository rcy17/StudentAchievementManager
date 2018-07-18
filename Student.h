#ifndef STUDENT_H
#define STUDENT_H
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
	//����ѧ������
	void SetName(const string &s);
	//��ȡѧ������
	string GetName()const;
	//����ѧ��ѧ��
	void SetNumber(const string &s);
	//��ȡѧ��ѧ��
	string GetNumber()const;
	//���������ĳ�γɼ�
	void AddSubjectGrade(const string &SubjectNumber,const string& Grade);
	//��������ɾ��ĳ�γɼ�
	void DeleteSubjectGrade(const string &SubjectNumber);
	//���������޸�ĳ�γɼ�
	void EditSubjectGrade(const string &SubjectNumber, const string& Grade);
	//���������ҵ�ĳ�γɼ�(ȷ���ɼ����ں����)
	string GetSubjectGrade(const string &SubejctNumber);
	//��¼�˸�ѧ�����пγ̺���ɼ�������
	list<String>m_lstSubjects;
	//����==��������Ƚ�������ѧ��
	bool operator==(const CStudent&A);
	//��ȡ��ǰGPA
	float GetGPA();
	//ÿ���漰GPA�����ݱ����ĺ���ô˺����Ա��
	void Changed();
	//��ȡ��ǰ��ѧ��
	int GetCredits();
private:
	//��¼ѧ������
	string m_szNumber;
	//��¼ѧ��
	string m_szName;
	//��¼�Ƿ����ݱ��޸ģ�m_bChange=trueʱ��Ҫ����GPA
	bool m_bChange;
	//��¼GPA
	float m_fGPA;
	//��¼ѧ��
	int m_nCredits;
};






#endif
