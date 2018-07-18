#include "UserOwnedStates.h"
#include "User.h"
#include "ConsoleUtils.h"

#include<algorithm>
#include <iostream>
using std::cout;

//һ����¼��ѧ�ŵ�ѧ����map
extern map<string, size_t>g_mNumberToStudent;
//һ����¼�˴ӿγ̺ŵ��γ̵�map
extern map<string, size_t>g_mNumberToSubject;
//һ����¼������ѧ����vector
extern vector<CStudent>g_vStudent;
//һ����¼�����пγ̵�vector
extern vector<CSubject>g_vSubject;

//----------------------------------------��ӭ����ķ�����

CInitialize* CInitialize::Instance()
{
	static CInitialize instance;

	return &instance;
}

void CInitialize::Enter(CUser* pCUser)
{
	PressAnyKeyToContinue();
	//�������õ���ӭ����Ľ��뺯��
}

void CInitialize::Execute(CUser* pCUser)
{
	//�ȶ�ȡ�ļ�����
	FileOpetate("SaveData.dat", 'r');
	//�˴��ǻ�ӭ����
	CoutMenu(WELCOME);

	pCUser->ChangeCState(CMainMenu::Instance());

}

void CInitialize::Exit(CUser* pCUser)
{
	//�ú���ͬ�����ᱻ�õ�
}

void CInitialize::ReadData()
{
	return;
}

void CInitialize::WriteData()
{
	return;
}



//--------------------------------------������ķ�����

CMainMenu* CMainMenu::Instance()
{
	static CMainMenu instance;

	return &instance;
}

void CMainMenu::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != MAIN)
	{
		CoutMenu(MAIN);
		pCUser->CUser::ChangeCurrentMenu(MAIN);
	}
}

void CMainMenu::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

void CMainMenu::Exit(CUser* pCUser)
{
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "���˳����˵�";*/
}


//--------------------------------------¼��ɼ�����ķ�����

CInputResults* CInputResults::Instance()
{
	static CInputResults instance;

	return &instance;
}

void CInputResults::Enter(CUser* pCUser)
{
	//���˵�����¼��ɼ����棬���л���¼��ɼ�����
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
		//�ȴ��û��������˵����ּ�
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
			cout << "\a\r�밴����Ч����";
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
		<< "���˳����˵�";*/
}

void CInputResults::ReadData()
{

}

void CInputResults::WriteData()
{

}

//--------------------------------------���ѧ���ɼ�����ķ�����

CQueryStudents* CQueryStudents::Instance()
{
	static CQueryStudents instance;

	return &instance;
}

void CQueryStudents::Enter(CUser* pCUser)
{
	//���˵����ڲ��ѧ���ɼ����棬���л������ѧ���ɼ�����
	if (pCUser->Menu() != STUDENTS)
	{
		CoutMenu(STUDENTS);

		pCUser->CUser::ChangeCurrentMenu(STUDENTS);
	}
}

void CQueryStudents::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

void CQueryStudents::Exit(CUser* pCUser)
{
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "���˳����˵�";*/
}

void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯѧ����ѧ��:(����������W)";
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
		cout << "�Ƿ���Ҫɾ�Ļ�������Ϣ?" << endl;
		if (PressAnyKeyToContinue(27, "��ESC����,������������༭��Ϣ��"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		else
			return;
	}
	else
	{
		cout << "δ�ҵ���ѧ�Ŷ�Ӧѧ�����Ƿ���Ӹ�ѧ��?()" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter�����ѧ������������������ء�"))
		{
			string StudentName;
			cout << "����������(������W����):";
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
	cout << "������Ŀ��ѧ����ѧ��:(����������W)";
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
			cout << "ѧ��Ϊ" << SubjectNumber << "����Ϊ" << g_vSubject[SubjectLabel].GetName() << "��ѧ���ĳɼ�Ϊ"
				<< g_vSubject[SubjectLabel].GetStudentGrade(StudentNumber) << endl;
			cout << "���������³ɼ�(�ô�д��ĸ��ʾ,ɾ��������W):";
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
			cout << "δ�ҵ�ѧ��Ϊ" << SubjectNumber << "��ѧ���Ŀγ̳ɼ������ϣ����ӳɼ�������ɼ�����д��ĸ��������������W:" << endl;
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
		cout << "δ�ҵ�ѧ��Ϊ" << SubjectNumber << "��ѧ������Ϣ�����ϣ����Ӹ�ѧ����������ѧ�����������ѧ����Ϣ������������W:" << endl;
		string Name;
		cin >> Name;
		if (Name != string("W"))
		{
			pCUser->AddSubject(Name, SubjectNumber);
			cout << "��������ɼ�(����������W):";
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
			}
		}
	}
}

//--------------------------------------��Ŀγ̳ɼ��ķ�����

CQuerySubjects* CQuerySubjects::Instance()
{
	static CQuerySubjects instance;

	return &instance;
}

void CQuerySubjects::Enter(CUser* pCUser)
{
	//���˵����ڲ�Ŀγ̳ɼ����棬���л�����Ŀγ̳ɼ�����
	if (pCUser->Menu() != SUBJECTS)
	{
		CoutMenu(SUBJECTS);

		pCUser->CUser::ChangeCurrentMenu(SUBJECTS);
	}
}

void CQuerySubjects::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

void CQuerySubjects::Exit(CUser* pCUser)
{
	/*SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	cout << "\n" << GetNameOfEntity(pCUser->ID()) << ": "
		<< "���˳����˵�";*/
}

void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯ�γ̵Ŀγ̺�:(��������W)";
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
		cout << "�Ƿ���Ҫɾ�Ļ�������Ϣ?" << endl;
		if (PressAnyKeyToContinue(27, "��ESC����,����������������༭��Ϣ��"))
		{
			EditInfomation(pCUser,SubjectNumber,SubjectLabel);
			
		}
		else
			return;
	}
	else
	{
		cout << "δ�ҵ��ÿγ̺Ŷ�Ӧ�γ̣��Ƿ���������?(��ӿγ��뵽¼��ɼ�����)" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter���������룬��������������ء�"))
			QuerySubject(pCUser);
	}
}

void CQuerySubjects::EditInfomation(CUser*pCUser,const string&SubjectNumber,const size_t&SubjectLabel)
{
	cout << "������Ŀ��ѧ����ѧ��:(����������W)";
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
			cout << "ѧ��Ϊ" << StudentNumber << "����Ϊ" << g_vStudent[StudentLabel].GetName() << "��ѧ���ĳɼ�Ϊ"
				<< g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) << endl;
			cout << "���������³ɼ�(�ô�д��ĸ��ʾ,ɾ��������W):";
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
			cout << "δ�ҵ�ѧ��Ϊ" << StudentNumber << "��ѧ���Ŀγ̳ɼ������ϣ����ӳɼ�������ɼ�����д��ĸ��������������W:" << endl;
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
		cout << "δ�ҵ�ѧ��Ϊ" << StudentNumber << "��ѧ������Ϣ�����ϣ����Ӹ�ѧ����������ѧ�����������ѧ����Ϣ������������W:" << endl;
		string Name;
		cin >> Name;
		if (Name != string("W"))
		{
			pCUser->AddStudent(Name, StudentNumber);
			cout << "��������ɼ�(����������W):";
			string Grade = InputPa();
			if (Grade != string("W"))
			{
				g_vStudent[StudentLabel].AddSubjectGrade(SubjectNumber, Grade);
				g_vSubject[SubjectLabel].AddStudentGrade(StudentNumber, Grade);
			}
		}
	}
}

//--------------------------------------���а����ķ�����

CRankList* CRankList::Instance()
{
	static CRankList instance;

	return &instance;
}

void CRankList::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != RANK)
	{
		CoutMenu(RANK);

		pCUser->CUser::ChangeCurrentMenu(RANK);
	}
}

void CRankList::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
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
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)//��������ѧ������ָ�����ǵ�ָ�����vector
	{
		vGPAList.push_back(&(*iterator));
	}
	sort(&(vGPAList[0]), &(vGPAList[vGPAList.size() - 1]), CompareGPAForStudent);//��ѧ���ɼ������������
	cout << "------------------GPA���а�-------------------" << endl;
	for (size_t i = 0; i < vGPAList.size(); i++)
	{
		cout << "��" << i << "��:" << vGPAList[i]->GetNumber() <<
			"\t" << vGPAList[i]->GetName() << "\t" << vGPAList[i]->GetGPA() << endl;
	}
	PressAnyKeyToContinue();
	vGPAList.clear();
}

void CRankList::ShowCreditList()
{
	system("cls");
	vector<CStudent*>vCreditsList;
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)//��������ѧ������ָ�����ǵ�ָ�����vector
	{
		vCreditsList.push_back(&(*iterator));
	}
	sort(&(vCreditsList[0]), &(vCreditsList[vCreditsList.size() - 1]), CompareCreditsForStudent);
	cout << "--------------------ѧ�����а�-------------------" << endl;
	for (size_t i = 0; i < vCreditsList.size(); i++)
	{
		cout << "��" << i << "��:" << vCreditsList[i]->GetNumber() <<
			"\t" << vCreditsList[i]->GetName() << "\t" << vCreditsList[i]->GetCredits() << endl;
	}
	PressAnyKeyToContinue();
	vCreditsList.clear();
}

void CRankList::ShowFailList()
{
	system("cls");
	cout << "----------------�ҿƼ�¼--------------------" << endl;
	for (auto IteratorForStudent = g_vStudent.begin(); IteratorForStudent != g_vStudent.begin(); IteratorForStudent++)//��������ѧ��
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{
			if (IteratorForSubject->GetGrade() == "F")//������ѧ�����пγ̣��ҵ��������
				cout << IteratorForStudent->GetNumber() << IteratorForStudent->GetName() << ":" << IteratorForSubject->GetNumber()<<
				g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() << endl;//���ѧ�š��������γ̺š��γ���
		}
	}
	PressAnyKeyToContinue();
}

//--------------------------------------ѧ����Ϣ�������ķ�����

CClear* CClear::Instance()
{
	static CClear instance;

	return &instance;
}

void CClear::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != CLEAR)
	{
		CoutMenu(CLEAR);

		pCUser->CUser::ChangeCurrentMenu(CLEAR);
	}
}

void CClear::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	switch (_getch())
	{
	case '1':
		Clear(pCUser);
		break;
	case '2':
	case 27://��ESCͬ���Ƿ���
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r�밴����Ч����";
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
	cout << "����������ѧ����ѧ��:";
	cin >> tem;
	pCUser->DeleteStudent(tem);
	PressAnyKeyToContinue();
	CoutMenu(CLEAR);

}


//--------------------------------------�˳�����ķ�����

CExit* CExit::Instance()
{
	static CExit instance;

	return &instance;
}

void CExit::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != OVER)
	{
		CoutMenu(OVER);
		pCUser->CUser::ChangeCurrentMenu(OVER);
	}
}

void CExit::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
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