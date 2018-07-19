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

CInitialize* CInitialize::Instance()
{
	static CInitialize instance;

	return &instance;
}

void CInitialize::Enter(CUser* pCUser)
{
	PressAnyKeyToContinue();
	//不可能用到欢迎界面的进入函数
}

void CInitialize::Execute(CUser* pCUser)
{
	//先读取文件数据
	FileOpetate("SaveData.dat", 'r');
	//此处是欢迎界面
	CoutMenu(WELCOME);

	pCUser->ChangeCState(CMainMenu::Instance());

}

void CInitialize::Exit(CUser* pCUser)
{
	//该函数同样不会被用到
}

void CInitialize::ReadData()
{
	//先读入学生数再读入学生学号、姓名、课程数、课程链表
	size_t StudentCount;
	m_ifstream >> StudentCount;
	for (size_t i = 1; i <= StudentCount; i++)//由于第0个学生位置已被系统占用，从1开始计数
	{
		string StudentName, StudentNumber;
		size_t StudentSubject;
		m_ifstream >> StudentNumber >> StudentName >> StudentSubject;
		g_vStudent.push_back(CStudent(StudentName, StudentNumber));
		for (size_t j = 0; j < StudentSubject; j++)
		{
			string List;
			m_ifstream >> List;
			g_vStudent[i].m_lstSubjects.push_back(List);
		}
	}
	//先读入学生数再读入学生学号、姓名、课程数、课程链表
	size_t SubjectCount;
	m_ifstream >> SubjectCount;
	for (size_t i = 1; i <= SubjectCount; i++)//由于第0个课程位置已被系统占用，从1开始计数
	{
		string SubjectName, SubjectNumber;
		size_t SubjectStudent;
		int SubjectCredit;
		m_ifstream >> SubjectNumber >> SubjectName >> SubjectCredit >> SubjectStudent;
		g_vSubject.push_back(CSubject(SubjectName, SubjectNumber, SubjectCredit));
		for (size_t j = 0; j < SubjectStudent; j++)
		{
			string List;
			m_ifstream >> List;
			g_vSubject[i].m_lstStudents.push_back(List);
		}
	}
	//读入学号与学生关系的map
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string Number;
		size_t Label;
		m_ifstream >> Number >> Label;
		g_mNumberToStudent.insert(pair<string, size_t>(Number, Label));
	}
	//写入课程号与课程关系的map
	for (size_t i = 1; i <= SubjectCount; i++)
	{
		string Number;
		size_t Label;
		m_ifstream >> Number >> Label;
		g_mNumberToSubject.insert(pair<string, size_t>(Number, Label));
	}
}

void CInitialize::WriteData()
{
	return;
}



//--------------------------------------主界面的方法类

CMainMenu* CMainMenu::Instance()
{
	static CMainMenu instance;

	return &instance;
}

void CMainMenu::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != MAIN)
	{
		CoutMenu(MAIN);
		pCUser->CUser::ChangeCurrentMenu(MAIN);
	}
}

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

void CMainMenu::Exit(CUser* pCUser)
{

}


//--------------------------------------录入成绩界面的方法类

CInputResults* CInputResults::Instance()
{
	static CInputResults instance;

	return &instance;
}

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

void CInputResults::Execute(CUser* pCUser)
{
	//录入界面同一颜色
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
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
			pCUser->ChangeCState(CMainMenu::Instance());
			break;
		default:
			cout << "\a\r请按下有效按键";
			break;
		}
		break;
	case INPUT_STUDENT:
		StudentInput(pCUser);
		Enter(pCUser);
		break;
	case INPUT_SUBJECT:
		SubjectInput(pCUser);
		Enter(pCUser);
		break;
	case INPUT_FREE:
		FreeInput(pCUser);
		Enter(pCUser);
		break;
	case INPUT_FILE:
		FileInput(pCUser);
		Enter(pCUser);
		break;
	}
}

void CInputResults::Exit(CUser* pCUser)
{

}

void CInputResults::ReadData()
{
	//先录入课程数量
	size_t SubjectCount;
	cin >> SubjectCount;
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
		cin >> SubjectNumber;
		cin >> SubjectName;
		cin >> Credit;
		cin >> StudentCount;
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
			cin >> StudentNumber;
			cin >> StudentName;
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

void CInputResults::WriteData()
{

}

void CInputResults::FreeInput(CUser* pCUser)
{
	system("cls");
	cout << "--------------------------自由录入--------------------------------" << endl;
	string StudentName, StudentNumber, SubjectNumber, SubjectName, Grade;
	size_t StudentLabel, SubjectLabel;
	cout << "请依次输入学号，课程号，成绩(字母表示)，用空格隔开，或输入W结束自由录入:" << endl;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
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

void CInputResults::StudentInput(CUser* pCUser)
{
	system("cls");
	string StudentNumber;
	cout << "请输入目标学生的学号:";
	cin >> StudentNumber;

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
		cin >> SubjectNumber;
		if (SubjectNumber == string("W"))
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

void CInputResults::SubjectInput(CUser* pCUser)
{
	system("cls");
	string SubjectNumber;
	cout << "请输入目标课程的课程号:";
	cin >> SubjectNumber;

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

void CInputResults::FileInput(CUser* pCUser)
{
	cout << "注:批量录入必须严格按照格式书写的文本文档，先输入需录入成绩的课程数量，依次输入课程号，课程名，" <<
		"课程学分，添加人数，每个学生的学号，姓名，字母表示的成绩，各个信息之间用空格隔开" << endl;
	cout << "请输入批量录入文件名" << endl;
	string szFileName;
	cin >> szFileName;
	FileOpetate(szFileName, 'r');
	cout << "录入结束！" << endl;
	PressAnyKeyToContinue();
}

//--------------------------------------查改学生成绩界面的方法类

CQueryStudents* CQueryStudents::Instance()
{
	static CQueryStudents instance;

	return &instance;
}

void CQueryStudents::Enter(CUser* pCUser)
{
	//若菜单不在查改学生成绩界面，则切换到查改学生成绩界面
	if (pCUser->Menu() != STUDENTS)
	{
		CoutMenu(STUDENTS);

		pCUser->CUser::ChangeCurrentMenu(STUDENTS);
	}
}

void CQueryStudents::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		QueryStudent(pCUser);
		CoutMenu(STUDENTS);
		break;
	case '2':
		EditStudent(pCUser);
		CoutMenu(STUDENTS);
		break;
	case '3':
	case 27:
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

void CQueryStudents::Exit(CUser* pCUser)
{
}

void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询学生的学号:(返回请输入W)";
	string StudentNumber;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		for (auto iterator = g_vStudent[StudentLabel].m_lstSubjects.begin(); iterator != g_vStudent[StudentLabel].m_lstSubjects.end(); iterator++)
		{
			cout << iterator->GetNumber() << g_vSubject[pCUser->FindSubject(iterator->GetNumber())].GetName() << iterator->GetGrade() << endl;
		}
		cout << "是否需要删改或增添成绩信息?" << endl;
		while (PressAnyKeyToContinue(27, "按ESC返回,按其他任意键编辑信息。"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		return;
	}
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

void CQueryStudents::EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLabel)
{
	cout << "请输入目标课程的课程号:(返回请输入W)";
	string SubjectNumber;
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{
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
	else
	{
		cout << "未找到课程号为" << SubjectNumber << "的课程信息，如果希望添加该课程请前往成绩录入菜单！" << endl;

	}
}

void CQueryStudents::EditStudent(CUser* pCUser)
{
	system("cls");
	cout << "请输入待修改学生的学号(或输入W退出):";
	string StudentNumber;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;
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
	else
	{
		cout << "未找到该学号学生！" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键重新输入或按其他任意键退出"))
			EditStudent(pCUser);
		else
			return;
	}
}

//--------------------------------------查改课程成绩的方法类

CQuerySubjects* CQuerySubjects::Instance()
{
	static CQuerySubjects instance;

	return &instance;
}

void CQuerySubjects::Enter(CUser* pCUser)
{
	//若菜单不在查改课程成绩界面，则切换到查改课程成绩界面
	if (pCUser->Menu() != SUBJECTS)
	{
		CoutMenu(SUBJECTS);

		pCUser->CUser::ChangeCurrentMenu(SUBJECTS);
	}
}

void CQuerySubjects::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		QuerySubject(pCUser);
		CoutMenu(SUBJECTS);
		break;
	case '2':
		EditSubject(pCUser);
		CoutMenu(SUBJECTS);
	case '3':
	case 27:
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

void CQuerySubjects::Exit(CUser* pCUser)
{

}

void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询课程的课程号:(返回输入W)";
	string SubjectNumber;
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{
		for (auto iterator = g_vSubject[SubjectLabel].m_lstStudents.begin(); iterator != g_vSubject[SubjectLabel].m_lstStudents.end(); iterator++)
		{
			cout << iterator->GetNumber() << g_vStudent[pCUser->FindStudent(iterator->GetNumber())].GetName() << iterator->GetGrade() << endl;
		}
		cout << "是否需要删改或增添成绩信息?" << endl;
		while (PressAnyKeyToContinue(27, "按ESC返回,按其他任意键继续编辑信息。"))
		{
			EditInfomation(pCUser, SubjectNumber, SubjectLabel);

		}
		return;
	}
	else
	{
		cout << "未找到该课程号对应课程，是否重新输入?(添加课程请到录入成绩界面)" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键重新输入，按其他任意键返回。"))
			QuerySubject(pCUser);
	}
}

void CQuerySubjects::EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLabel)
{
	cout << "请输入目标学生的学号:(返回请输入W)";
	string StudentNumber;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		if (g_vSubject[SubjectLabel].GetStudentGrade(StudentNumber) != string("W"))
		{
			string NewGrade;
			cout << "学号为" << StudentNumber << "姓名为" << g_vStudent[StudentLabel].GetName() << "的学生的成绩为"
				<< g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) << endl;
			cout << "请输入其新成绩(用大写字母表示,删除请输入W):";
			if ((NewGrade = InputPa()) != string("W"))
			{
				g_vStudent[StudentLabel].EditSubjectGrade(SubjectNumber, NewGrade);
				g_vSubject[SubjectLabel].EditStudentGrade(StudentNumber, NewGrade);
			}
			else
			{
				g_vStudent[StudentLabel].DeleteSubjectGrade(SubjectNumber);
				g_vSubject[SubjectLabel].DeleteStudentGrade(StudentNumber);
			}
		}
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

void CQuerySubjects::EditSubject(CUser* pCUser)
{
	system("cls");
	cout << "请输入待修改课程的课程号(或输入W退出):";
	string Number;
	cin >> Number;
	if (Number == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;
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
	else
	{
		cout << "未找到该课程号课程！" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键重新输入或按其他任意键退出"))
			EditSubject(pCUser);
		else
			return;
	}
}

//--------------------------------------排行榜界面的方法类

CRankList* CRankList::Instance()
{
	static CRankList instance;

	return &instance;
}

void CRankList::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != RANK)
	{
		CoutMenu(RANK);

		pCUser->CUser::ChangeCurrentMenu(RANK);
	}
}

void CRankList::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
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
		pCUser->ChangeCState(CMainMenu::Instance());
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

void CRankList::Exit(CUser* pCUser)
{

}

bool CompareGPAForStudent(CStudent*A, CStudent*B)
{
	return A->GetGPA() > B->GetGPA();
}

bool CompareCreditsForStudent(CStudent*A, CStudent*B)
{
	return A->GetCredits() > B->GetCredits();
}

void CRankList::ShowGPAList()
{
	system("cls");
	vector<CStudent*>vGPAList;
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)//遍历所有学生，将指向他们得指针加入vector
	{
		vGPAList.push_back(&(*iterator));
	}
	sort(&(vGPAList[0]), &(vGPAList[vGPAList.size() - 1]), CompareGPAForStudent);//对学生成绩进行排序并输出
	cout << "------------------GPA排行榜-------------------" << endl;
	for (size_t i = 0; i < vGPAList.size(); i++)
	{
		cout << "第" << i + 1 << "名:" << vGPAList[i]->GetNumber() <<
			"\t" << vGPAList[i]->GetName() << "\t\t";
		cout.precision(3);
		cout.width(4);
		cout << vGPAList[i]->GetGPA() << endl;
	}
	PressAnyKeyToContinue();
	vGPAList.clear();
}

void CRankList::ShowCreditList()
{
	system("cls");
	vector<CStudent*>vCreditsList;
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)//遍历所有学生，将指向他们得指针加入vector
	{
		vCreditsList.push_back(&(*iterator));
	}
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

void CRankList::ShowFailList()
{
	system("cls");
	cout << "----------------挂科记录--------------------" << endl;
	for (auto IteratorForStudent = g_vStudent.begin() + 1; IteratorForStudent != g_vStudent.end(); IteratorForStudent++)//遍历所有学生
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{
			if (IteratorForSubject->GetGrade() == string("F"))//遍历该学生所有课程，找到不及格的
				cout << "学号" << IteratorForStudent->GetNumber() << "  姓名" << IteratorForStudent->GetName() <<
				":" << "\t课程号" << IteratorForSubject->GetNumber() << " 课程名：" <<
				g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() <<
				endl;//输出学号、姓名、课程号、课程名
		}
	}
	PressAnyKeyToContinue();
}

//--------------------------------------学生信息清除界面的方法类

CClear* CClear::Instance()
{
	static CClear instance;

	return &instance;
}

void CClear::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != CLEAR)
	{
		CoutMenu(CLEAR);

		pCUser->CUser::ChangeCurrentMenu(CLEAR);
	}
}

void CClear::Execute(CUser* pCUser)
{
	//等待用户按下主菜单数字键
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	switch (_getch())
	{
	case '1':
		Clear(pCUser);
		break;
	case '2':
	case 27://按ESC同样是返回
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r请按下有效按键";
		break;
	}
}

void CClear::Exit(CUser* pCUser)
{

}

void CClear::Clear(CUser* pCUser)
{
	CoutMenu(CLEAR_CHOOSE);
	string tem;
	system("cls");
	cout << "请输入待清除学生的学号:";
	cin >> tem;
	pCUser->DeleteStudent(tem);
	PressAnyKeyToContinue();
	CoutMenu(CLEAR);

}


//--------------------------------------退出界面的方法类

CExit* CExit::Instance()
{
	static CExit instance;

	return &instance;
}

void CExit::Enter(CUser* pCUser)
{
	//若菜单不在主界面，则切换到主界面
	if (pCUser->Menu() != OVER)
	{
		CoutMenu(OVER);
		pCUser->CUser::ChangeCurrentMenu(OVER);
	}
}

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

void CExit::Exit(CUser* pCUser)
{

}

void CExit::ReadData()
{

}

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