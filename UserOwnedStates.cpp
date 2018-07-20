#include "UserOwnedStates.h"
#include "User.h"
#include "ConsoleUtils.h"

#include<algorithm>
#include <iostream>
using std::cout;

//一个记录从学号到学生的map
extern map<string, size_t>g_mNumberToStudent;
//一个记录了从课程号到课程的map
extern map<string, size_t>g_mNumberToSubject;
//一个记录了所有学生的vector
extern vector<CStudent>g_vStudent;
//一个记录了所有课程的vector
extern vector<CSubject>g_vSubject;

//----------------------------------------欢迎界面的方法类

//获取CInitialize的唯一实例
CInitialize* CInitialize::Instance()
{
	static CInitialize instance;

	return &instance;
}

//进入CInitialize(实际不可能用到)
void CInitialize::Enter(CUser* pCUser)
{
	PressAnyKeyToContinue();
	//不可能用到欢迎界面的进入函数
}

//CInitialize的执行函数
void CInitialize::Execute(CUser* pCUser)
{
	//先读取文件数据
	FileOpetate("SaveData.dat", 'r');
	//此处是欢迎界面
	CoutMenu(WELCOME);
	//进入主菜单
	pCUser->ChangeCState(CMainMenu::Instance());

}

//CInitialize退出函数
void CInitialize::Exit(CUser* pCUser)
{

}

//CInitialize读取数据的函数
void CInitialize::ReadData()
{
	//先读入学生数再读入学生学号、姓名、课程数、课程链表
	size_t StudentCount;
	m_ifstream >> StudentCount;

	//由于第0个学生位置已被系统占用，从1开始计数
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string StudentName, StudentNumber;
		size_t StudentSubject;

		//读取学号，姓名，课程数
		m_ifstream >> StudentNumber >> StudentName >> StudentSubject;
		g_vStudent.push_back(CStudent(StudentName, StudentNumber));
		for (size_t j = 0; j < StudentSubject; j++)
		{
			//读入课程链表
			string List;
			m_ifstream >> List;
			g_vStudent[i].m_lstSubjects.push_back(List);
		}
	}

	//先读入学生数再读入学生学号、姓名、课程数、课程链表
	size_t SubjectCount;
	m_ifstream >> SubjectCount;

	//由于第0个课程位置已被系统占用，从1开始计数
	for (size_t i = 1; i <= SubjectCount; i++)
	{
		string SubjectName, SubjectNumber;
		size_t SubjectStudent;
		int SubjectCredit;

		//读取课程号，课程名，课程学分，选课人数
		m_ifstream >> SubjectNumber >> SubjectName >> SubjectCredit >> SubjectStudent;
		g_vSubject.push_back(CSubject(SubjectName, SubjectNumber, SubjectCredit));
		for (size_t j = 0; j < SubjectStudent; j++)
		{
			string List;

			//读取学生链表
			m_ifstream >> List;
			g_vSubject[i].m_lstStudents.push_back(List);
		}
	}

	//读入学号与学生关系的map
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string Number;
		size_t Label;

		//先读入学号，再读入下标
		m_ifstream >> Number >> Label;
		g_mNumberToStudent.insert(pair<string, size_t>(Number, Label));
	}

	//写入课程号与课程关系的map
	for (size_t i = 1; i <= SubjectCount; i++)
	{
		string Number;
		size_t Label;

		//先读入课程号，再读入下标
		m_ifstream >> Number >> Label;
		g_mNumberToSubject.insert(pair<string, size_t>(Number, Label));
	}
}

//仅为将CInitialize确认为一个非抽象类
void CInitialize::WriteData()
{
	return;
}

//--------------------------------------主界面的方法类

//获取CMainMenu唯一实例
CMainMenu* CMainMenu::Instance()
{
	static CMainMenu instance;

	return &instance;
}

//CMainMenu进入函数，打印出相关信息
void CMainMenu::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != MAIN)
	{
		CoutMenu(MAIN);
		pCUser->CUser::ChangeCurrentMenu(MAIN);
	}
}

//CMainMenu执行函数，用户进行操作
void CMainMenu::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

	//char c = _getch();
	switch (_getch())
	{
	case '1':
		pCUser->ChangeCState(CInputResults::Instance());
		break;
	case '2':
		pCUser->ChangeCState(CQueryStudents::Instance());
		break;
	case '3':
		pCUser->ChangeCState(CQuerySubjects::Instance());
		break;
	case '4':
		pCUser->ChangeCState(CRankList::Instance());
		break;
	case '5':
		pCUser->ChangeCState(CClear::Instance());
		break;
	case '6':
		pCUser->ChangeCState(CExit::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CMainMenu退出函数
void CMainMenu::Exit(CUser* pCUser)
{

}


//--------------------------------------录入成绩界面的方法类

//获取CInputResults唯一实例
CInputResults* CInputResults::Instance()
{
	static CInputResults instance;

	return &instance;
}

//CInputResults进入函数，打印出相关信息
void CInputResults::Enter(CUser* pCUser)
{
	//若菜单不在录入成绩界面，则切换到录入成绩界面
	if (pCUser->Menu() != PUTIN)
	{
		CoutMenu(PUTIN);
		pCUser->CUser::ChangeCurrentMenu(PUTIN);
	}
	m_pUser = pCUser;
}

//CInputResults执行函数，等待用户选择录入方式
void CInputResults::Execute(CUser* pCUser)
{
	//录入界面同一颜色
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);

	//依据所处子菜单来决定行为
	switch (pCUser->Menu())
	{
	case PUTIN:
		//等待用户按下主菜单数字键
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		switch (_getch())
		{
		case '1':
			pCUser->ChangeCurrentMenu(INPUT_STUDENT);
			break;
		case '2':
			pCUser->ChangeCurrentMenu(INPUT_SUBJECT);
			break;
		case '3':
			pCUser->ChangeCurrentMenu(INPUT_FREE);
			break;
		case '4':
			pCUser->ChangeCurrentMenu(INPUT_FILE);
			break;
		case '5':
		case 27:
			//按下5或者ESC返回主菜单
			pCUser->ChangeCState(CMainMenu::Instance());
			break;
		default:
			cout << "\a\r请按下有效按键";
			break;
		}
		break;

	case INPUT_STUDENT:
		//先进入学生成绩录入菜单
		StudentInput(pCUser);
		//录入完成后返回录入主菜单
		Enter(pCUser);
		break;

	case INPUT_SUBJECT:
		//先进入课程成绩录入菜单
		SubjectInput(pCUser);
		//录入完成返回录入主菜单
		Enter(pCUser);
		break;

	case INPUT_FREE:
		//先进入自由录入菜单
		FreeInput(pCUser);
		//录入完成后进入录入主菜单
		Enter(pCUser);
		break;

	case INPUT_FILE:
		//先进入批量录入菜单
		FileInput(pCUser);
		//录入完成后进入录入主菜单
		Enter(pCUser);
		break;
	}
}

//CInputResults退出函数
void CInputResults::Exit(CUser* pCUser)
{

}

//CInputResults批量录入用的读取函数
void CInputResults::ReadData()
{
	//先录入课程数量
	size_t SubjectCount;
	m_ifstream >> SubjectCount;
	if (m_ifstream.fail())
	{
		cout << "读入数字失败，中止录入!" << endl;
		PressAnyKeyToContinue();
		return;
	}
	if (SubjectCount < 0)
	{
		cout << "课程数小于0，中止录入!" << endl;
		PressAnyKeyToContinue();
		return;
	}
	for (size_t i = 0; i < SubjectCount; i++)
	{
		//再读入课程号，课程名，课程学分，添加人数
		string SubjectNumber, SubjectName;
		int Credit;
		size_t StudentCount;
		m_ifstream >> SubjectNumber;
		m_ifstream >> SubjectName;
		m_ifstream >> Credit;
		m_ifstream >> StudentCount;
		if (!(m_pUser->CheckSubjectNumber(SubjectNumber) && m_pUser->CheckCredit(Credit) && StudentCount >= 0))
		{
			cout << "第" << i + 1 << "门课程:课程号" << SubjectNumber << "课程名" << SubjectName <<
				"添加人数" << StudentCount << "中包含非法信息，中止读入" << endl;
			PressAnyKeyToContinue();
			return;
		}
		size_t SubjectLabel;

		//先判定是否已包含该科目信息，若有则直接录入，没有则添加，由于批量录入本身属于测试功能，此处不检查是否冲突
		while (!(SubjectLabel = m_pUser->FindSubject(SubjectNumber)))
		{
			m_pUser->AddSubject(SubjectName, SubjectNumber, Credit);
		}
		for (size_t j = 0; j < StudentCount; j++)
		{
			//读入每个学生的学号，姓名，字母表示的成绩
			string StudentNumber, StudentName, Grade;
			m_ifstream >> StudentNumber;
			m_ifstream >> StudentName;
			m_ifstream >> Grade;
			if (!(m_pUser->CheckStudentNumber(StudentNumber) && GetGP(Grade) != -1.0f))
			{
				cout << "课程号为" << SubjectNumber << "的第" << j + 1 << "个学生信息:学号" << StudentNumber <<
					"姓名" << StudentName << "成绩" << Grade << "中包含非法信息，跳过本条内容！" << endl;
				continue;
			}
			size_t StudentLabel;

			//先判断是否已包含该学生信息，其他同判断科目信息
			while (!(StudentLabel = m_pUser->FindStudent(StudentNumber)))
			{
				m_pUser->AddStudent(StudentName, StudentNumber);
			}
			g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
			g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
		}
	}
}

//仅为将CInputResults确认为非抽象类
void CInputResults::WriteData()
{

}

//CInputResults自由录入界面
void CInputResults::FreeInput(CUser* pCUser)
{
	system("cls");
	cout << "--------------------------自由录入--------------------------------" << endl;
	string StudentName, StudentNumber, SubjectNumber, SubjectName, Grade;
	size_t StudentLabel, SubjectLabel;
	cout << "请依次输入学号，课程号，成绩(字母表示)，用空格隔开，或输入W结束自由录入:" << endl;

	//录入学生号并判断退出
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}

	//录入课程号并判断推出
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}

	//录入成绩并判断退出
	cin >> Grade;
	if (Grade == string("W"))
	{
		ClearInput();
		return;
	}

	//判断学号存在性与合法性
	while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
	{
		if (pCUser->CheckStudentNumber(StudentNumber))
		{
			cout << "学号" << StudentNumber << "不存在，是否添加？(添加输入学生姓名，返回输入W)" << endl;
			cin >> StudentName;
			if (StudentName == string("W"))
			{
				ClearInput();
				return;
			}
			pCUser->AddStudent(StudentName, StudentNumber);
		}
		else
		{
			cout << "学号<" << StudentNumber << ">不合法，请重新输入！(或输入W返回)" << endl;
			cin >> StudentNumber;
			if (StudentNumber == string("W"))
			{
				ClearInput();
				return;
			}
		}
	}

	//判断课程号存在性与合法性
	while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
	{
		if (pCUser->CheckSubjectNumber(SubjectNumber))
		{
			int Credit;
			cout << "课程号" << SubjectNumber << "不存在，是否添加？(添加输入课程名与学分数，返回输入W)" << endl;
			cin >> SubjectName;
			if (SubjectName == string("W"))
			{
				ClearInput();
				return;
			}
			cin >> Credit;
			while (!pCUser->CheckCredit(Credit))
			{
				cout << "无效的学分数，请重新输入或输入W返回:";
				cin >> Credit;
			}

			pCUser->AddSubject(SubjectName, SubjectNumber, Credit);
		}
		else
		{
			cout << "课程号<" << SubjectNumber << ">不合法，请重新输入！(或输入W返回)" << endl;
			cin >> SubjectNumber;
			if (SubjectNumber == string("W"))
			{
				ClearInput();
				return;
			}
		}
	}

	//判断成绩合法性
	while (GetGP(Grade) == -1.0f)
	{
		cout << "对于学号" << StudentNumber << "课程号" << SubjectNumber << "输入的成绩<" << Grade <<
			">无效，请输入一个字母成绩（如A+,F）,或输入W返回" << endl;
		cin >> Grade;
		if (Grade == string("W"))
		{
			ClearInput();
			return;
		}
	}
	g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
	g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
	FreeInput(pCUser);

}

//CInputResults学生成绩录入界面
void CInputResults::StudentInput(CUser* pCUser)
{
	system("cls");
	string StudentNumber;
	cout << "请输入目标学生的学号(或输入W返回):";

	//录入学号并判断返回
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;

	//判断学号合法性
	while (!(pCUser->CheckStudentNumber(StudentNumber)))
	{
		cout << "无效的学号!请重新输入或输入W返回!" << endl;
		cin >> StudentNumber;
		if (StudentNumber == string("W"))
		{
			ClearInput();
			return;
		}
	}

	//判断学号存在性
	while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
	{

		cout << "未找到学号为" << StudentNumber << "的学生，请输入姓名添加学生或输入W返回" << endl;
		string StudentName;
		cin >> StudentName;
		if (StudentName == string("W"))
		{
			ClearInput();
			return;
		}
		pCUser->AddStudent(StudentName, StudentNumber);

	}

	//循环输入课程成绩
	while (true)
	{
		system("cls");
		cout << "请输入课程号与成绩,用空格隔开，或输入W返回" << endl;
		string SubjectNumber, SubjectName, Grade;
		size_t SubjectLabel;

		//录入课程号并判断返回
		cin >> SubjectNumber;
		if (SubjectNumber == string("W"))
		{
			ClearInput();
			return;
		}

		//录入成绩并判断返回
		cin >> Grade;
		if (Grade == string("W"))
		{
			ClearInput();
			return;
		}

		//判断课程号存在性与合法性
		while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
		{
			if (pCUser->CheckSubjectNumber(SubjectNumber))
			{
				cout << "课程号" << SubjectNumber << "不存在，是否添加？(添加分别输入课程名和学分，返回输入W)" << endl;
				cin >> SubjectName;
				if (SubjectName == string("W"))
				{
					ClearInput();
					return;
				}
				int Credit;
				cin >> Credit;
				while (!pCUser->CheckCredit(Credit))
				{
					cout << "无效的学分数，请重新输入或输入W返回:";
					cin >> Credit;
				}
				pCUser->AddSubject(SubjectName, SubjectNumber, Credit);
			}
			else
			{
				cout << "课程号<" << SubjectNumber << ">不合法，请重新输入！(或输入W返回)" << endl;
				cin >> SubjectNumber;
				if (SubjectNumber == string("W"))
				{
					ClearInput();
					return;
				}
			}
		}

		//判断成绩合法性
		while (GetGP(Grade) == -1.0f)
		{
			cout << "对于学号" << StudentNumber << "课程号" << SubjectNumber << "输入的成绩<" << Grade <<
				">无效，请输入一个字母成绩（如A+,F）,或输入W返回" << endl;
			cin >> Grade;
			if (Grade == string("W"))
			{
				ClearInput();
				return;
			}
		}
		g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
		g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
	}
}

//CInputResults课程成绩录入界面
void CInputResults::SubjectInput(CUser* pCUser)
{
	system("cls");
	string SubjectNumber;
	cout << "请输入目标课程的课程号(或输入W返回):";

	//录入课程号并判断返回
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;

	//判断课程号合法性
	while (!(pCUser->CheckSubjectNumber(SubjectNumber)))
	{
		cout << "无效的课程号!请重新输入或输入W返回!" << endl;
		cin >> SubjectNumber;
		if (SubjectNumber == string("W"))
		{
			ClearInput();
			return;
		}
	}

	//判断课程号存在性
	while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
	{

		cout << "未找到课程为" << SubjectNumber << "的课程，请输入课程名与学分(空格隔开)添加课程或输入W返回" << endl;
		string SubjectName;
		cin >> SubjectName;
		if (SubjectName == string("W"))
		{
			ClearInput();
			return;
		}
		int Credit;
		cin >> Credit;
		while (!pCUser->CheckCredit(Credit))
		{
			cout << "无效的学分数，请重新输入或输入W返回:";
			cin >> Credit;
		}
		pCUser->AddSubject(SubjectName, SubjectNumber, Credit);

	}

	//循环输入学生成绩
	while (true)
	{
		system("cls");
		cout << "请输入学号与成绩,用空格隔开，或输入W返回" << endl;
		string StudentNumber, StudentName, Grade;
		size_t StudentLabel;
		cin >> StudentNumber;
		if (StudentNumber == string("W"))
		{
			ClearInput();
			return;
		}
		cin >> Grade;
		if (Grade == string("W"))
		{
			ClearInput();
			return;
		}

		//判断学号存在性与合法性
		while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
		{
			if (pCUser->CheckStudentNumber(StudentNumber))
			{
				cout << "学号" << StudentNumber << "不存在，是否添加？(添加输入学号名，返回输入W)" << endl;
				cin >> StudentName;
				if (StudentName == string("W"))
				{
					ClearInput();
					return;
				}
				pCUser->AddStudent(StudentName, StudentNumber);
			}
			else
			{
				cout << "学号<" << StudentNumber << ">不合法，请重新输入！(或输入W返回)" << endl;
				cin >> StudentNumber;
				if (StudentNumber == string("W"))
				{
					ClearInput();
					return;
				}
			}
		}

		//判断成绩合法性
		while (GetGP(Grade) == -1.0f)
		{
			cout << "对于学号" << StudentNumber << "课程号" << SubjectNumber << "输入的成绩<" << Grade <<
				">无效，请输入一个字母成绩（如A+,F）,或输入W返回" << endl;
			cin >> Grade;
			if (Grade == string("W"))
			{
				ClearInput();
				return;
			}
		}
		g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
		g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
	}
}

//CInputResults批量录入界面
void CInputResults::FileInput(CUser* pCUser)
{
	system("cls");
	cout << "注:批量录入必须严格按照格式书写的文本文档，先输入需录入成绩的课程数量，依次输入课程号，课程名，" <<
		"课程学分，添加人数，每个学生的学号，姓名，字母表示的成绩，各个信息之间用空格隔开" << endl;
	cout << "请输入批量录入的完整文件名(或输入W返回)" << endl;
	string szFileName;

	//输入文件名并判断返回
	ClearInput();
	cin >> szFileName;
	if (szFileName == string("W"))
	{
		ClearInput();
		return;
	}
	FileOpetate(szFileName, 'r');
	cout << "录入结束！" << endl;
	PressAnyKeyToContinue();
}

//--------------------------------------查改学生成绩界面的方法类

//获取CQueryStudents唯一实例
CQueryStudents* CQueryStudents::Instance()
{
	static CQueryStudents instance;

	return &instance;
}

//CQueryStudents进入函数，打印出相关信息
void CQueryStudents::Enter(CUser* pCUser)
{
	//若菜单不在查改学生成绩界面，则切换到查改学生成绩界面
	if (pCUser->Menu() != STUDENTS)
	{
		CoutMenu(STUDENTS);

		pCUser->CUser::ChangeCurrentMenu(STUDENTS);
	}
}

//CQueryStudents执行函数，等待用户操作
void CQueryStudents::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		//进入查询界面
		QueryStudent(pCUser);
		//查询完回到CQueryStudents主界面
		CoutMenu(STUDENTS);
		break;
	case '2':
		//进入编辑学生信息界面
		EditStudent(pCUser);
		//编辑完回到CQueryStudents主界面
		CoutMenu(STUDENTS);
		break;
	case '3':
	case 27:
		//按下3或者ESC回到主菜单
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CQueryStudents退出函数
void CQueryStudents::Exit(CUser* pCUser)
{
}

//CQueryStudents查询学生信息界面
void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询学生的学号:(返回请输入W)";
	string StudentNumber;

	//输入学号并判断返回
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;

	//若能找到学生则打印出课程成绩
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		for (auto iterator = g_vStudent[StudentLabel].m_lstSubjects.begin(); iterator != g_vStudent[StudentLabel].m_lstSubjects.end(); iterator++)
		{
			//打印出各科课程号，课程名，成绩
			cout << iterator->GetNumber() << "\t" << g_vSubject[pCUser->FindSubject(iterator->GetNumber())].GetName() <<
				" " << iterator->GetGrade() << endl;
		}

		//输出课程均分
		float GPA = g_vStudent[StudentLabel].GetGPA();
		if (GPA == -2.0f)
			cout << "该学生暂无有效GPA信息" << endl;
		else
		{
			cout << "该学生GPA为";
			cout.precision(4);
			cout << GPA << endl;
		}
		cout << "是否需要删改或增添成绩信息?" << endl;
		while (!PressAnyKeyToContinue(27, "按ESC返回,按其他任意键编辑信息。"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		return;
	}

	//找不到该学号对应学生则考虑添加
	else
	{
		cout << "未找到该学号对应学生，是否添加该学生?" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键添加学生，按其他任意键返回。"))
		{
			string StudentName;
			cout << "请输入姓名(或输入W返回):";
			cin >> StudentName;
			if (StudentName == string("W"))
			{
				ClearInput();
				QueryStudent(pCUser);
			}
			else
			{
				pCUser->AddStudent(StudentName, StudentNumber);
				cout << "添加学生成功，现在您可以在录入成绩界面录入学生成绩了";
				PressAnyKeyToContinue();
			}
		}
		else return;
	}
}

//CQueryStudents编辑学生某课程成绩信息界面
void CQueryStudents::EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLabel)
{
	cout << "请输入目标课程的课程号:(返回请输入W)";
	string SubjectNumber;

	//输入课程号并判断返回
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;

	//若课程号存在则进一部检索
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{

		//若该学生有该科成绩则给出具体信息并提供删改服务
		if (g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) != string("W"))
		{
			string NewGrade;
			cout << "课程号为" << SubjectNumber << "课程名为" << g_vSubject[SubjectLabel].GetName() << "的课的成绩为"
				<< g_vSubject[SubjectLabel].GetStudentGrade(StudentNumber) << endl;
			cout << "请输入其新成绩(用大写字母表示,删除请输入W):";
			if ((NewGrade = InputPa()) != string("W"))
			{
				g_vSubject[SubjectLabel].EditStudentGrade(StudentNumber, NewGrade);
				g_vStudent[StudentLabel].EditSubjectGrade(SubjectNumber, NewGrade);
			}
			else
			{
				g_vSubject[SubjectLabel].DeleteStudentGrade(StudentNumber);
				g_vStudent[StudentLabel].DeleteSubjectGrade(SubjectNumber);
			}
		}

		//若无该科成绩则考虑添加
		else
		{
			cout << "未找到课程号为" << SubjectNumber << "的课程成绩，如果希望添加成绩请输入成绩（大写字母），返回请输入W:" << endl;
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
			}
		}
	}

	//课程号不存在则给出错误信息
	else
	{
		cout << "未找到课程号为" << SubjectNumber << "的课程信息，如果希望添加该课程请前往成绩录入菜单！" << endl;
		PressAnyKeyToContinue();
	}
}

//CQueryStudents学生个人信息修改界面
void CQueryStudents::EditStudent(CUser* pCUser)
{
	system("cls");
	cout << "请输入待修改学生的学号(或输入W退出):";
	string StudentNumber;

	//读入学号并判断返回
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;

	//若学号存在则给出信息
	if (Label = pCUser->FindStudent(StudentNumber))
	{
		cout << "学号为" << StudentNumber << "的学生姓名为" << g_vStudent[Label].GetName() << endl;
		cout << "请输入更改后的姓名(注:学号作为唯一身份标识不应支持修改，输入W退出修改):";
		string Name;
		cin >> Name;
		if (Name == string("W"))
		{
			ClearInput();
			return;
		}
		g_vStudent[Label].SetName(Name);
		cout << "修改成功!" << endl;
		PressAnyKeyToContinue();
	}

	//学号不存在则考虑添加
	else
	{
		cout << "未找到该学号对应学生，是否添加该学生?" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键添加学生，按其他任意键返回。"))
		{
			string StudentName;
			cout << "请输入姓名(或输入W返回):";
			cin >> StudentName;
			if (StudentName == string("W"))
			{
				ClearInput();
				QueryStudent(pCUser);
			}
			else
			{
				pCUser->AddStudent(StudentName, StudentNumber);
				cout << "添加学生成功，现在您可以在录入成绩界面录入学生成绩了";
				PressAnyKeyToContinue();
			}
		}
		else return;
	}
}

//--------------------------------------查改课程成绩的方法类

//获取CQuerySubjects唯一实例
CQuerySubjects* CQuerySubjects::Instance()
{
	static CQuerySubjects instance;

	return &instance;
}

//CQuerySubjects进入函数，打印出相关信息
void CQuerySubjects::Enter(CUser* pCUser)
{
	//若菜单不在查改课程成绩界面，则切换到查改课程成绩界面
	if (pCUser->Menu() != SUBJECTS)
	{
		CoutMenu(SUBJECTS);

		pCUser->CUser::ChangeCurrentMenu(SUBJECTS);
	}
}

//CQuerySubjects执行函数，等待用户操作
void CQuerySubjects::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		//进入查询课程成绩界面
		QuerySubject(pCUser);
		//返回课程查询主菜单
		CoutMenu(SUBJECTS);
		break;

	case '2':
		//进入课程信息更改界面
		EditSubject(pCUser);
		//返回课程查询主菜单
		CoutMenu(SUBJECTS);

	case '3':
	case 27:
		//按下3或者ESC返回主菜单
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CQuerySubjects退出函数
void CQuerySubjects::Exit(CUser* pCUser)
{

}

//CQuerySubjects课程查询界面
void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询课程的课程号:(返回输入W)";
	string SubjectNumber;

	//输入课程号并判断返回
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;

	//若课程号存在，则给出学生成绩信息
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{

		//逐行输出学号，学生姓名，课程成绩
		for (auto iterator = g_vSubject[SubjectLabel].m_lstStudents.begin(); iterator != g_vSubject[SubjectLabel].m_lstStudents.end(); iterator++)
		{
			cout << iterator->GetNumber() << " " << g_vStudent[pCUser->FindStudent(iterator->GetNumber())].GetName() <<
				" " << iterator->GetGrade() << endl;
		}

		//输出课程均分
		float GPA = g_vSubject[SubjectLabel].GetGPA();
		if (GPA == -2.0f)
		{
			cout << "该课为P/F课程，不计算GPA" << endl;
		}
		else
		{
			cout << "该课程平均成绩为";
			cout.precision(4);
			cout << GPA << endl;
		}
		cout << "是否需要删改或增添成绩信息?" << endl;
		while (!PressAnyKeyToContinue(27, "按ESC返回,按其他任意键继续编辑信息。"))
		{
			//进入学生成绩修改界面
			EditInfomation(pCUser, SubjectNumber, SubjectLabel);
		}
		return;
	}

	//不存在则考虑重新输入
	else
	{
		cout << "未找到该课程号对应课程，是否重新输入?(添加课程请到录入成绩界面)" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键重新输入，按其他任意键返回。"))
			QuerySubject(pCUser);
	}
}

//CQuerySubjects课程某学生成绩修改界面
void CQuerySubjects::EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLabel)
{
	cout << "请输入目标学生的学号:(返回请输入W)";
	string StudentNumber;

	//读入学号并判断返回
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;

	//若学号存在则给出该学生该科信息
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		//若学生成绩存在则打印出信息
		if (g_vSubject[SubjectLabel].GetStudentGrade(StudentNumber) != string("W"))
		{
			string NewGrade;
			cout << "学号为" << StudentNumber << "姓名为" << g_vStudent[StudentLabel].GetName() << "的学生的成绩为"
				<< g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) << endl;
			cout << "请输入其新成绩(用大写字母表示,删除成绩请输入W):";
			if ((NewGrade = InputPa()) != string("W"))
			{
				g_vStudent[StudentLabel].EditSubjectGrade(SubjectNumber, NewGrade);
				g_vSubject[SubjectLabel].EditStudentGrade(StudentNumber, NewGrade);
				cout << "修改成功!" << endl;
			}
			else
			{
				g_vStudent[StudentLabel].DeleteSubjectGrade(SubjectNumber);
				g_vSubject[SubjectLabel].DeleteStudentGrade(StudentNumber);
				cout << "删除成功!" << endl;
			}
		}

		//不存在则考虑添加该学生成绩
		else
		{
			cout << "未找到学号为" << StudentNumber << "的学生的课程成绩，如果希望添加成绩请输入成绩（大写字母），返回请输入W:" << endl;
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
			}
		}
	}

	//学号不存在则考虑添加该学生信息
	else
	{
		cout << "未找到学号为" << StudentNumber << "的学生的信息，如果希望添加该学生请先输入学生姓名以添加学生信息，返回请输入W:" << endl;
		string Name;
		cin >> Name;
		if (Name != string("W"))
		{
			pCUser->AddStudent(Name, StudentNumber);
			cout << "请输入其成绩(返回请输入W):";
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
			}
		}
		else
		{
			ClearInput();
			return;
		}
	}
}

//CQuerySubjects编辑课程信息界面
void CQuerySubjects::EditSubject(CUser* pCUser)
{
	system("cls");
	cout << "请输入待修改课程的课程号(或输入W退出):";
	string Number;

	//读入课程号并判断返回
	ClearInput();
	cin >> Number;
	if (Number == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;

	//若课程号存在则打印出相关信息
	if (Label = pCUser->FindSubject(Number))
	{
		cout << "课程为" << Number << "的课程名为" << g_vSubject[Label].GetName() << "," <<
			g_vSubject[Label].GetCredit() << "学分" << ",请输入修改后的课程名与学分" <<
			"(注:课程号作为课程唯一标识，不应支持修改,输入W退出修改):" << endl;
		string Name;
		int Credit;
		cin >> Name;
		if (Name == string("W"))
		{
			ClearInput();
			return;
		}
		cin >> Credit;
		while (!(pCUser->CheckCredit(Credit)))
		{
			cout << "输入的学分" << Credit << "非法，请重新输入:";
			cin >> Credit;
		}
		g_vSubject[Label].SetName(Name);
		g_vSubject[Label].ChangeCredit(Credit);
		cout << "修改成功!" << endl;
		PressAnyKeyToContinue();
	}

	//不存在则考虑重新输入
	else
	{
		cout << "未找到该课程号课程！" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键添加课程或按其他任意键退出"))
		{
			cout << "请输入课程名与学分(空格隔开)添加课程或输入W返回" << endl;
			string SubjectName;
			cin >> SubjectName;
			if (SubjectName == string("W"))
			{
				ClearInput();
				return;
			}
			int Credit;
			cin >> Credit;
			while (!pCUser->CheckCredit(Credit))
			{
				cout << "无效的学分数，请重新输入或输入W返回:";
				cin >> Credit;
			}
			pCUser->AddSubject(SubjectName, Number, Credit);
			cout << "添加成功!" << endl;
			PressAnyKeyToContinue();
		}

		else
			return;
	}
}

//--------------------------------------排行榜界面的方法类

//获取CRankList唯一实例
CRankList* CRankList::Instance()
{
	static CRankList instance;

	return &instance;
}

//CRankList进入函数，打印相关信息
void CRankList::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != RANK)
	{
		CoutMenu(RANK);

		pCUser->CUser::ChangeCurrentMenu(RANK);
	}
}

//CRankList执行函数，等到用户操作
void CRankList::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		ShowGPAList();
		CoutMenu(RANK);
		break;
	case '2':
		ShowCreditList();
		CoutMenu(RANK);
		break;
	case '3':
		ShowFailList();
		CoutMenu(RANK);
		break;
	case '4':
	case 27:
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		pCUser->ChangeCState(CMainMenu::Instance());
		return;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CRankList退出函数
void CRankList::Exit(CUser* pCUser)
{

}

//比较GPA所用的比较函数，提供给sort
bool CompareGPAForStudent(CStudent*A, CStudent*B)
{
	return A->GetGPA() > B->GetGPA();
}

//比较学分所用的比较函数，提供给sotr
bool CompareCreditsForStudent(CStudent*A, CStudent*B)
{
	return A->GetCredits() > B->GetCredits();
}

//CRankList展示GPA排行榜函数
void CRankList::ShowGPAList()
{
	system("cls");
	vector<CStudent*>vGPAList;

	//遍历所有学生，将指向他们的指针加入vector
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)
	{
		vGPAList.push_back(&(*iterator));
	}

	//对学生成绩进行排序并输出
	sort(&(vGPAList[0]), &(vGPAList[vGPAList.size() - 1]), CompareGPAForStudent);
	cout << "------------------GPA排行榜-------------------" << endl;
	for (size_t i = 0; i < vGPAList.size(); i++)
	{
		cout << "第" << i + 1 << "名:" << vGPAList[i]->GetNumber() <<
			"\t" << vGPAList[i]->GetName() << "\t\t";
		cout.width(4);

		float GPA = vGPAList[i]->GetGPA();
		//若GPA为-2.0f，则说明尚无有效绩点
		if (GPA == -2.0f)
		{
			cout << "N/A" << endl;
		}
		else
		{
			cout.precision(4);
			cout << GPA << endl;
		}
	}
	PressAnyKeyToContinue();
	vGPAList.clear();
}

//CRankList展示学分排行榜函数
void CRankList::ShowCreditList()
{
	system("cls");
	vector<CStudent*>vCreditsList;

	//遍历所有学生，将指向他们的指针加入vector
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)
	{
		vCreditsList.push_back(&(*iterator));
	}

	//对学生学分进行排序并打印
	sort(&(vCreditsList[0]), &(vCreditsList[vCreditsList.size() - 1]), CompareCreditsForStudent);
	cout << "--------------------学分排行榜-------------------" << endl;
	for (size_t i = 0; i < vCreditsList.size(); i++)
	{
		cout << "第" << i << "名:" << vCreditsList[i]->GetNumber() <<
			"\t" << vCreditsList[i]->GetName() << "\t" << vCreditsList[i]->GetCredits() << endl;
	}
	PressAnyKeyToContinue();
	vCreditsList.clear();
}

//CRankList展示挂科记录函数
void CRankList::ShowFailList()
{
	system("cls");
	cout << "----------------挂科记录--------------------" << endl;

	//遍历所有学生
	for (auto IteratorForStudent = g_vStudent.begin() + 1; IteratorForStudent != g_vStudent.end(); IteratorForStudent++)
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{

			//遍历该学生所有课程，找到不及格的
			if (IteratorForSubject->GetGrade() == string("F"))
			{
				//输出学号、姓名、课程号、课程名
				cout << "学号" << IteratorForStudent->GetNumber() << "  姓名" << IteratorForStudent->GetName() <<
					":" << "\t课程号" << IteratorForSubject->GetNumber() << " 课程名：" <<
					g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() <<
					endl;
			}
		}
	}
	PressAnyKeyToContinue();
}

//--------------------------------------学生信息清除界面的方法类

//获取CClear唯一实例
CClear* CClear::Instance()
{
	static CClear instance;

	return &instance;
}

//CClear进入函数，打印出相关信息
void CClear::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != CLEAR)
	{
		CoutMenu(CLEAR);

		pCUser->CUser::ChangeCurrentMenu(CLEAR);
	}
}

//CClear执行函数，等到用户操作
void CClear::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	switch (_getch())
	{
	case '1':
		//按1进入清除界面
		Clear(pCUser);
		//清除完后再打印出该菜单信息
		CoutMenu(CLEAR);
		break;
	case '2':
	case 27:
		//按2或ESC返回主菜单
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CClear退出函数
void CClear::Exit(CUser* pCUser)
{

}

//CClear清除学生信息函数
void CClear::Clear(CUser* pCUser)
{
	CoutMenu(CLEAR_CHOOSE);
	string StudentNumber;
	system("cls");
	cout << "请输入待清除学生的学号(或输入W返回):";

	//输入学号并判断返回
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	pCUser->DeleteStudent(StudentNumber);
	PressAnyKeyToContinue();

}


//--------------------------------------退出界面的方法类

//获取CExit唯一实例
CExit* CExit::Instance()
{
	static CExit instance;

	return &instance;
}

//CExit进入函数，并打印出相关信息
void CExit::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != OVER)
	{
		CoutMenu(OVER);
		pCUser->CUser::ChangeCurrentMenu(OVER);
	}
}

//CExit执行函数，等待用户操作
void CExit::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
	case '\r':
		cout << "正在存档中，请勿强制关闭...";
		FileOpetate("SaveData.dat", 'w');
		PressAnyKeyToContinue('\0', "存档成功，按任意键退出");
		exit(0);
		break;
	case '2':
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

//CExit退出函数
void CExit::Exit(CUser* pCUser)
{

}

//仅为让CExit不是抽象类
void CExit::ReadData()
{

}

//CExit写入数据函数，更新数据文件
void CExit::WriteData()
{
	//先写入学生数再写入学生学号、姓名、课程数、课程链表
	m_ofstream << g_vStudent.size() - 1 << " ";
	for (auto VectorIterator = g_vStudent.begin() + 1; VectorIterator != g_vStudent.end(); VectorIterator++)
	{
		m_ofstream << VectorIterator->GetNumber() << " " << VectorIterator->GetName() << " " <<
			VectorIterator->m_lstSubjects.size() << " ";
		auto pList = &(VectorIterator->m_lstSubjects);
		for (auto ListIterator = pList->begin(); ListIterator != pList->end(); ListIterator++)
		{
			m_ofstream << *ListIterator << " ";
		}
	}
	//先写入课程数在写入课程号、课程名、学分、学生数、学生链表
	m_ofstream << g_vSubject.size() - 1 << " ";
	for (auto VectorIterator = g_vSubject.begin() + 1; VectorIterator != g_vSubject.end(); VectorIterator++)
	{
		m_ofstream << VectorIterator->GetNumber() << " " << VectorIterator->GetName() << " " <<
			VectorIterator->GetCredit() << " " << VectorIterator->m_lstStudents.size() << " ";
		auto pList = &(VectorIterator->m_lstStudents);
		for (auto ListIterator = pList->begin(); ListIterator != pList->end(); ListIterator++)
		{
			m_ofstream << *ListIterator << " ";
		}
	}
	//写入学号与学生关系的map
	for (auto MapIterator = g_mNumberToStudent.begin(); MapIterator != g_mNumberToStudent.end(); MapIterator++)
	{
		m_ofstream << MapIterator->first << " " << MapIterator->second << " ";
	}
	//写入课程号与课程关系的map
	for (auto MapIterator = g_mNumberToSubject.begin(); MapIterator != g_mNumberToSubject.end(); MapIterator++)
	{
		m_ofstream << MapIterator->first << " " << MapIterator->second << " ";
	}

}