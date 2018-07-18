#include "User.h"
#include "UserOwnedStates.h"

//一个记录了所有学生的vector
vector<CStudent>g_vStudent(1);
//一个记录了所有课程的vector
vector<CSubject>g_vSubject(1);
//一个记录从学号到学生vector下标的map
map<string, size_t>g_mNumberToStudent;
//一个记录了从课程号到课程vector下标的map
map<string, size_t>g_mNumberToSubject;

CUser::CUser():m_Menu(WELCOME),m_pCurrentCState(CInitialize::Instance())
                                                                 
{
	g_vStudent[0].SetName("查无此人");
	g_vStudent[0].SetNumber("0000");
	g_vSubject[0].SetName("无此课程");
	g_vSubject[0].SetNumber("0000");
}



//--------------------------- ChangeCState -------------------------------------
//-----------------------------------------------------------------------------
void CUser::ChangeCState(CState* pNewCState)
{
  //确保当前状态与下一状态都不为空
  assert (m_pCurrentCState && pNewCState);

  //调用当前状态的退出函数
  m_pCurrentCState->Exit(this);

  //状态改为新状态
  m_pCurrentCState = pNewCState;

  //调用新状态的进入函数
  m_pCurrentCState->Enter(this);
}




//-----------------------------------------------------------------------------
void CUser::Update()
{

  
  if (m_pCurrentCState)
  {
    m_pCurrentCState->Execute(this);
  }
}


void CUser::AddStudent(const string&Name, const string&Number)
{
	if (!FindStudent(Number))
	{
		
		g_mNumberToStudent.insert(pair<string,size_t>(Number, g_vStudent.size()));
		g_vStudent.push_back(CStudent(Name, Number));
	}
	else
	{
		cout << "已有该学生，无须再添加!" << endl;
		PressAnyKeyToContinue();
	}

}

bool CUser::DeleteStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())//先判断是否有该学号的学生
	{
		cout << "您确定要删除学号为" << s << ",姓名为" << g_vStudent[FindStudent(s)].GetName() << "的学生的全部信息吗？" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键继续，按其他任意键取消"))
		{
			auto ptrLstStu = &(g_vStudent[iterator->second].m_lstSubjects);//找到该学生的课程链表并遍历一遍
			for (auto iterator = ptrLstStu->begin(); iterator != ptrLstStu->end(); iterator++)
			{
				auto ptrLstSub = &(g_vSubject[g_mNumberToSubject.find((*iterator).GetNumber())->second].m_lstStudents);
				for (auto it = ptrLstStu->begin(); it != ptrLstStu->end(); it++)//再将该学生的课程对应的学生链表遍历一遍
				{
					if ((*it).GetNumber() == s)
					{
						ptrLstSub->erase(it);//删除课程的学生链表中该学生的信息
					}
					break;
				}
			}
			g_vStudent.erase(g_vStudent.begin()+iterator->second);//删除该学生在学生vector中的信息
			for (auto it = g_mNumberToStudent.begin(); it != g_mNumberToStudent.end(); it++)//将vector中下标更大的值均减1
			{
				if (it->second > iterator->second)
					it->second--;
			}
			g_mNumberToStudent.erase(iterator);//删除该学生在map中的信息
			cout << "已成功删除！" << endl;
			return true;
		}
		cout << "已取消删除!" << endl;
	}
	else
	{
		cout << "未找到该学号的学生！" << endl;
	}
	return false;
}

void CUser::AddSubject(const string&Name, const string&Number)
{
	if (!FindSubject(Number))
	{

		g_mNumberToSubject.insert(pair<string, size_t>(Number, g_vSubject.size()));
		g_vSubject.push_back(CSubject(Name, Number));
	}
	else
	{
		cout << "已有该课程，无须再添加!" << endl;
		PressAnyKeyToContinue();
	}

}
/*
bool CUser::DeleteSubject(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())
	{
	}
}*/

size_t CUser::FindStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())
		return iterator->second;
	else
		return 0;
}

size_t CUser::FindSubject(const string&s)
{
	auto iterator = g_mNumberToSubject.find(s);
	if (iterator != g_mNumberToSubject.end())
		return iterator->second;
	else
		return 0;
}

enum_menu CUser::Menu()const
{
	return m_Menu;
}

void CUser::ChangeCurrentMenu(const enum_menu loc)
{
	m_Menu = loc;
}