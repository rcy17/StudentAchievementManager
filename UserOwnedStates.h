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

	//继承抽象类CFileOperation的读取函数
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

	CInputResults(const CInputResults&);

	//继承抽象类CFileOperation的读取函数
	virtual void ReadData();
	virtual void WriteData();

	//自由录入
	void FreeInput(CUser* pCUser);

	//学生成绩录入
	void StudentInput(CUser* pCUser);

	//课程成绩录入
	void SubjectInput(CUser* pCUser);

	//批量录入
	void FileInput(CUser* pCUser);

	//仅仅为了在ReadData里调用CUser的成员函数
	CUser* m_pUser;
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

	//进入课程查询菜单
	void QueryStudent(CUser* pCUser);

	//改动课程成绩信息
	void EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLable);

	//改动学生信息
	void EditStudent(CUser* pCUser);

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

	//进入查询学生菜单
	void QuerySubject(CUser* pCUser);

	//改动学生成绩信息
	void EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLable);

	//改动课程信息
	void EditSubject(CUser* pCUser);

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
	CRankList(const CRankList&);

	//展示GPA排行榜
	void ShowGPAList();

	//展示学分排行榜
	void ShowCreditList();

	//展示挂科记录
	void ShowFailList();

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

	//清除函数
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

	CExit(const CExit&);

	//继承抽象类CFileOperation的写入函数
	virtual void WriteData();
public:

	//这是一个有限状态机
	static CExit* Instance();

	virtual void Enter(CUser* user);

	virtual void Execute(CUser* user);

	virtual void Exit(CUser* user);
};



#endif