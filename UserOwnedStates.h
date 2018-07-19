#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  �ļ���:   CUserOwnedCStates.h
//
//  ����:   �����������û����ܴ��ڵ�����״̬���ࣩ
//
//------------------------------------------------------------------------
#include "State.h"
#include "FileOperation.h"

class CFileOperation;
class CUser;


//------------------------------------------------------------------------
//
//  ��ӭ���棬ͬʱ��ȡ�ļ�
//------------------------------------------------------------------------
class CInitialize : public CState, public CFileOperation
{
private:

	CInitialize()
	{
	}

	//�̳г�����CFileOperation�Ķ�ȡ����
	virtual void ReadData();

	virtual void WriteData();

	CInitialize(const CInitialize&);

public:

	//����һ������״̬��
	static CInitialize* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);

	
};

//------------------------------------------------------------------------
//
//  ���˵�
//------------------------------------------------------------------------
class CMainMenu : public CState
{
private:

	CMainMenu(){}

	CMainMenu(const CMainMenu&);

public:

	//����һ������״̬��
	static CMainMenu* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	¼��ɼ��˵���ѡ��ѧ���ɼ�¼��/�γ̳ɼ�¼��/����¼��/����¼��
//------------------------------------------------------------------------
class CInputResults : public CState,public CFileOperation
{
private:

	CInputResults(){}

	CInputResults(const CInputResults&);

	//�̳г�����CFileOperation�Ķ�ȡ����
	virtual void ReadData();
	virtual void WriteData();

	//����¼��
	void FreeInput(CUser* pCUser);

	//ѧ���ɼ�¼��
	void StudentInput(CUser* pCUser);

	//�γ̳ɼ�¼��
	void SubjectInput(CUser* pCUser);

	//����¼��
	void FileInput(CUser* pCUser);

	//����Ϊ����ReadData�����CUser�ĳ�Ա����
	CUser* m_pUser;
public:

	//����һ������״̬��
	static CInputResults* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	��ѯ/�޸�ѧ���ɼ��˵�����ѯ����ѧ�������гɼ���GPA����֧���޸���������
//------------------------------------------------------------------------
class CQueryStudents : public CState
{
private:

	CQueryStudents()
	{
	}

	CQueryStudents(const CQueryStudents&);

	//����γ̲�ѯ�˵�
	void QueryStudent(CUser* pCUser);

	//�Ķ��γ̳ɼ���Ϣ
	void EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLable);

	//�Ķ�ѧ����Ϣ
	void EditStudent(CUser* pCUser);

public:

	//����һ������״̬��
	static CQueryStudents* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	��ѯ/�޸Ŀγ̳ɼ��˵�����ѯ�����γ̵�ͳ����Ϣ���޸�ĳѧ���ɼ�
//------------------------------------------------------------------------
class CQuerySubjects : public CState
{
private:

	CQuerySubjects()
	{
	}

	CQuerySubjects(const CQuerySubjects&);

	//�����ѯѧ���˵�
	void QuerySubject(CUser* pCUser);

	//�Ķ�ѧ���ɼ���Ϣ
	void EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLable);

	//�Ķ��γ���Ϣ
	void EditSubject(CUser* pCUser);

public:

	//����һ������״̬��
	static CQuerySubjects* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	���а�˵������������ݿ��е�ѧ������GPA��������
//------------------------------------------------------------------------
class CRankList : public CState
{
private:

	CRankList()
	{
	}
	CRankList(const CRankList&);

	//չʾGPA���а�
	void ShowGPAList();

	//չʾѧ�����а�
	void ShowCreditList();

	//չʾ�ҿƼ�¼
	void ShowFailList();

public:

	//����һ������״̬��
	static CRankList* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	ѧ����Ϣ����˵�����ĳѧ����������Ϣɾ��
//------------------------------------------------------------------------
class CClear : public CState
{
private:

	CClear()
	{
	}
	CClear(const CClear&);

	//�������
	void Clear(CUser* pCUser);
public:

	//����һ������״̬��
	static CClear* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	�˳����棬��ɶ������˳�
//------------------------------------------------------------------------
class CExit : public CState,public CFileOperation
{
private:

	CExit()
	{
	}
	virtual void ReadData();

	CExit(const CExit&);

	//�̳г�����CFileOperation��д�뺯��
	virtual void WriteData();
public:

	//����һ������״̬��
	static CExit* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};



#endif