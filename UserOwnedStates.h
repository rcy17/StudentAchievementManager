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
	virtual void ReadData();
	virtual void WriteData();
	CInputResults(const CInputResults&);
	void FreeInput(CUser* pCUser);
	void StudentInput(CUser* pCUser);
	void SubjectInput(CUser* pCUser);
	void FileInput(CUser* pCUser);

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
	void QueryStudent(CUser* pCUser);
	void EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLable);

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
	void QuerySubject(CUser* pCUser);
	void EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLable);

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
	void ShowGPAList();
	void ShowCreditList();
	void ShowFailList();
	CRankList(const CRankList&);

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
	virtual void WriteData();
	CExit(const CExit&);

public:

	//����һ������״̬��
	static CExit* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};



#endif