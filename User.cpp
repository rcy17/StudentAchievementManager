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
	//用户的注册是整个系统工作的开始，这里初始化整个系统的工作状态
	//占用了0号位的vector，以便用map返回下标0时判定为未找到
	g_vStudent[0].SetName("查无此人");
	g_vStudent[0].SetNumber("0000");
	g_vSubject[0].SetName("无此课程");
	g_vSubject[0].SetNumber("0000");
}

//改变状态（菜单）时会用到此函数
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

//每个周期的更新函数
void CUser::Update()
{
  if (m_pCurrentCState)
  {
    m_pCurrentCState->Execute(this);
  }
}

//向vector中新增学生
void CUser::AddStudent(const string&Name, const string&Number)
{
	if (!FindStudent(Number))
	{
		//向vector中添加学生时不能忘了新增map信息，此时新学生下标就是原来vector的size
		g_mNumberToStudent.insert(pair<string,size_t>(Number, g_vStudent.size()));
		g_vStudent.push_back(CStudent(Name, Number));
	}
	else
	{
		cout << "已有该学生，无须再添加!" << endl;
		PressAnyKeyToContinue();
	}

}

//判定课程号输入是否合法
bool CUser::CheckSubjectNumber(const string&SubjectNumber)
{
	auto it = SubjectNumber.begin();
	//首位允许是大写字母或者数字
	if (!((*it >= '0'&&*it <= '9') || (*it >= 'A'&&*it <= 'Z')))
		return false;
	//后面位数只能是数字
	for (it++; it != SubjectNumber.end(); it++)
	{
		if (*it<'0' || *it>'9')
			return false;
	}
	return true;
}

//判断学号输入是否合法
bool CUser::CheckStudentNumber(const string&StudentNumber)
{
	//学号必须是纯数字
	for (auto it = StudentNumber.begin(); it != StudentNumber.end(); it++)
	{
		if (*it<'0' || *it>'9')
			return false;
	}
	return true;
}

//判断学分输入是否合法
bool CUser::CheckCredit(int Credit)
{
	//学号应当是一个0到15的整数
	if (Credit >= 0 && Credit <= 15)
		return true;
	return false;
}

//删除一个学生的全部信息
bool CUser::DeleteStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	//先判断是否有该学号的学生
	if (iterator != g_mNumberToStudent.end())
	{
		cout << "您确定要删除学号为" << s << ",姓名为" << g_vStudent[FindStudent(s)].GetName() << "的学生的全部信息吗？" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键继续，按其他任意键取消"))
		{
			auto ptrLstStu = &(g_vStudent[iterator->second].m_lstSubjects);
			//找到该学生的课程链表并遍历一遍
			for (auto iterator = ptrLstStu->begin(); iterator != ptrLstStu->end(); iterator++)
			{
				auto ptrLstSub = &(g_vSubject[g_mNumberToSubject.find((*iterator).GetNumber())->second].m_lstStudents);
				//再将该学生的课程对应的学生链表遍历一遍
				for (auto it = ptrLstStu->begin(); it != ptrLstStu->end(); it++)
				{
					if ((*it).GetNumber() == s)
					{
						//删除课程的学生链表中该学生的信息
						ptrLstSub->erase(it);
					}
					break;
				}
			}
			//删除该学生在学生vector中的信息
			g_vStudent.erase(g_vStudent.begin()+iterator->second);
			//将vector中下标更大的值均减1
			for (auto it = g_mNumberToStudent.begin(); it != g_mNumberToStudent.end(); it++)
			{
				if (it->second > iterator->second)
					it->second--;
			}
			//删除该学生在map中的信息
			g_mNumberToStudent.erase(iterator);
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

//添加一门课程
void CUser::AddSubject(const string&Name, const string&Number,int Credit)
{
	if (!FindSubject(Number))
	{
		//向vector中添加课程时不能忘了新增map信息，此时新课程下标就是原来vector的size
		g_mNumberToSubject.insert(pair<string, size_t>(Number, g_vSubject.size()));
		g_vSubject.push_back(CSubject(Name, Number,Credit));
		
	}
	else
	{
		cout << "已有该课程，无须再添加!" << endl;
		PressAnyKeyToContinue();
	}

}

//根据学号找到一个学生并返回下标
size_t CUser::FindStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())
		return iterator->second;
	else
		return 0;
}

//根据课程号找到一门课程并返回下标
size_t CUser::FindSubject(const string&s)
{
	auto iterator = g_mNumberToSubject.find(s);
	if (iterator != g_mNumberToSubject.end())
		return iterator->second;
	else
		return 0;
}

//返回用户当前所处的菜单
enum_menu CUser::Menu()const
{
	return m_Menu;
}

//改变用户当前所处菜单
void CUser::ChangeCurrentMenu(const enum_menu loc)
{
	m_Menu = loc;
}
