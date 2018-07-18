#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
//------------------------------------------------------------------------
//
//  文件名:   CUserOwnedCStates.h
//
//  简述:   这里声明了用户可能处于的所有状态（类）
//
//------------------------------------------------------------------------
#include "State.h"
#include "FileOperation.h"

class CFileOperation;
class CUser;


//------------------------------------------------------------------------
//
//  欢迎界面，同时读取文件
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

	//这是一个有限状态机
	static CInitialize* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);

	
};

//------------------------------------------------------------------------
//
//  主菜单
//------------------------------------------------------------------------
class CMainMenu : public CState
{
private:

	CMainMenu(){}


	CMainMenu(const CMainMenu&);

public:

	//这是一个有限状态机
	static CMainMenu* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	录入成绩菜单，选择学生成绩录入/课程成绩录入/自由录入/批量录入
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

	//这是一个有限状态机
	static CInputResults* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	查询/修改学生成绩菜单，查询给定学生的所有成绩与GPA，并支持修改任意内容
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

	//这是一个有限状态机
	static CQueryStudents* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	查询/修改课程成绩菜单，查询给定课程的统计信息、修改某学生成绩
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

	//这是一个有限状态机
	static CQuerySubjects* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	排行榜菜单，将所有数据库中的学生根据GPA进行排行
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

	//这是一个有限状态机
	static CRankList* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	学生信息清除菜单，将某学生的所有信息删除
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

	//这是一个有限状态机
	static CClear* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};

//------------------------------------------------------------------------
//
//	退出界面，完成读档与退出
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

	//这是一个有限状态机
	static CExit* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};



#endif