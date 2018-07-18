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
	return;
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
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "已退出主菜单";*/
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
}

void CInputResults::Execute(CUser* pCUser)
{
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
			break;
		default:
			cout << "\a\r请按下有效按键";
			break;
		}
		if (pCUser->Menu() != PUTIN)
			CoutMenu(pCUser->Menu());
		break;
	case INPUT_STUDENT:
		break;
	case INPUT_SUBJECT:
		break;
	case INPUT_FREE:

		break;
	case INPUT_FILE:
	{
		std::string tem;
		std::cin >> tem;
		FileOpetate(tem, 'r');
	}
	break;
	}
}

void CInputResults::Exit(CUser* pCUser)
{
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "已退出主菜单";*/
}

void CInputResults::ReadData()
{

}

void CInputResults::WriteData()
{

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
		pCUser->ChangeCState(NULL);
		break;
	case '2':
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
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "已退出主菜单";*/
}

void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询学生的学号:(返回请输入W)";
	string StudentNumber;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
		return;
	size_t StudentLabel;
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		for (auto iterator = g_vStudent[StudentLabel].m_lstSubjects.begin(); iterator != g_vStudent[StudentLabel].m_lstSubjects.end(); iterator++)
		{
			cout << iterator->GetNumber() << g_vSubject[pCUser->FindSubject(iterator->GetNumber())].GetName() << iterator->GetGrade() << endl;
		}
		cout << "是否需要删改或增添信息?" << endl;
		if (PressAnyKeyToContinue(27, "按ESC返回,按其他任意键编辑信息。"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		else
			return;
	}
	else
	{
		cout << "未找到该学号对应学生，是否添加该学生?()" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键添加学生，按其他任意键返回。"))
		{
			string StudentName;
			cout << "请输入姓名(或输入W返回):";
			cin >> StudentName;
			if (StudentName == string("W"))
			{
				QueryStudent(pCUser);
			}
			else
			{
				pCUser->AddStudent(StudentName, StudentNumber);
			}
		}
		else return;
	}
}

void CQueryStudents::EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLabel)
{
	cout << "请输入目标学生的学号:(返回请输入W)";
	string SubjectNumber;
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
		return;
	size_t SubjectLabel;
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{
		if (g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) != string("W"))
		{
			string NewGrade;
			cout << "学号为" << SubjectNumber << "姓名为" << g_vSubject[SubjectLabel].GetName() << "的学生的成绩为"
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
			cout << "未找到学号为" << SubjectNumber << "的学生的课程成绩，如果希望添加成绩请输入成绩（大写字母），返回请输入W:" << endl;
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
		cout << "未找到学号为" << SubjectNumber << "的学生的信息，如果希望添加该学生请先输入学生姓名以添加学生信息，返回请输入W:" << endl;
		string Name;
		cin >> Name;
		if (Name != string("W"))
		{
			pCUser->AddSubject(Name, SubjectNumber);
			cout << "请输入其成绩(返回请输入W):";
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
			}
		}
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
		//pCUser->ChangeCurrentMenu(SUBJECTS_INPUT);
		QuerySubject(pCUser);
		CoutMenu(SUBJECTS);
		//Enter(pCUser);
		break;
	case '2':
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
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "已退出主菜单";*/
}

void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "请输入待查询课程的课程号:(返回输入W)";
	string SubjectNumber;
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
		return;
	size_t SubjectLabel;
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{
		for (auto iterator = g_vSubject[SubjectLabel].m_lstStudents.begin(); iterator != g_vSubject[SubjectLabel].m_lstStudents.end(); iterator++)
		{
			cout << iterator->GetNumber() << g_vStudent[pCUser->FindStudent(iterator->GetNumber())].GetName() << iterator->GetGrade() << endl;
		}
		cout << "是否需要删改或增添信息?" << endl;
		if (PressAnyKeyToContinue(27, "按ESC返回,按其他任意键继续编辑信息。"))
		{
			EditInfomation(pCUser,SubjectNumber,SubjectLabel);
			
		}
		else
			return;
	}
	else
	{
		cout << "未找到该课程号对应课程，是否重新输入?(添加课程请到录入成绩界面)" << endl;
		if (PressAnyKeyToContinue('\r', "按Enter键重新输入，按其他任意键返回。"))
			QuerySubject(pCUser);
	}
}

void CQuerySubjects::EditInfomation(CUser*pCUser,const string&SubjectNumber,const size_t&SubjectLabel)
{
	cout << "请输入目标学生的学号:(返回请输入W)";
	string StudentNumber;
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
		return;
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
			string Grade=InputPa();
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

	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
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
		cout << "第" << i << "名:" << vGPAList[i]->GetNumber() <<
			"\t" << vGPAList[i]->GetName() << "\t" << vGPAList[i]->GetGPA() << endl;
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
	for (auto IteratorForStudent = g_vStudent.begin(); IteratorForStudent != g_vStudent.begin(); IteratorForStudent++)//遍历所有学生
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{
			if (IteratorForSubject->GetGrade() == "F")//遍历该学生所有课程，找到不及格的
				cout << IteratorForStudent->GetNumber() << IteratorForStudent->GetName() << ":" << IteratorForSubject->GetNumber()<<
				g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() << endl;//输出学号、姓名、课程号、课程名
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
		pCUser->ChangeCState(NULL);
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

}