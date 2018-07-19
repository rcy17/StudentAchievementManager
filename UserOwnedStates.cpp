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
	//�ȶ���ѧ�����ٶ���ѧ��ѧ�š��������γ������γ�����
	size_t StudentCount;
	m_ifstream >> StudentCount;
	for (size_t i = 1; i <= StudentCount; i++)//���ڵ�0��ѧ��λ���ѱ�ϵͳռ�ã���1��ʼ����
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
	//�ȶ���ѧ�����ٶ���ѧ��ѧ�š��������γ������γ�����
	size_t SubjectCount;
	m_ifstream >> SubjectCount;
	for (size_t i = 1; i <= SubjectCount; i++)//���ڵ�0���γ�λ���ѱ�ϵͳռ�ã���1��ʼ����
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
	//����ѧ����ѧ����ϵ��map
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string Number;
		size_t Label;
		m_ifstream >> Number >> Label;
		g_mNumberToStudent.insert(pair<string, size_t>(Number, Label));
	}
	//д��γ̺���γ̹�ϵ��map
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
	m_pUser = pCUser;
}

void CInputResults::Execute(CUser* pCUser)
{
	//¼�����ͬһ��ɫ
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
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
		case 27:
			pCUser->ChangeCState(CMainMenu::Instance());
			break;
		default:
			cout << "\a\r�밴����Ч����";
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
	//��¼��γ�����
	size_t SubjectCount;
	cin >> SubjectCount;
	if (SubjectCount < 0)
	{
		cout << "�γ���С��0����ֹ¼��!" << endl;
		PressAnyKeyToContinue();
		return;
	}
	for (size_t i = 0; i < SubjectCount; i++)
	{
		//�ٶ���γ̺ţ��γ������γ�ѧ�֣��������
		string SubjectNumber, SubjectName;
		int Credit;
		size_t StudentCount;
		cin >> SubjectNumber;
		cin >> SubjectName;
		cin >> Credit;
		cin >> StudentCount;
		if (!(m_pUser->CheckSubjectNumber(SubjectNumber) && m_pUser->CheckCredit(Credit) && StudentCount >= 0))
		{
			cout << "��" << i + 1 << "�ſγ�:�γ̺�" << SubjectNumber << "�γ���" << SubjectName <<
				"�������" << StudentCount << "�а����Ƿ���Ϣ����ֹ����" << endl;
			PressAnyKeyToContinue();
			return;
		}
		size_t SubjectLabel;
		//���ж��Ƿ��Ѱ����ÿ�Ŀ��Ϣ��������ֱ��¼�룬û������ӣ���������¼�뱾�����ڲ��Թ��ܣ��˴�������Ƿ��ͻ
		while (!(SubjectLabel = m_pUser->FindSubject(SubjectNumber)))
		{
			m_pUser->AddSubject(SubjectName, SubjectNumber, Credit);
		}
		for (size_t j = 0; j < StudentCount; j++)
		{
			//����ÿ��ѧ����ѧ�ţ���������ĸ��ʾ�ĳɼ�
			string StudentNumber, StudentName, Grade;
			cin >> StudentNumber;
			cin >> StudentName;
			if (!(m_pUser->CheckStudentNumber(StudentNumber) && GetGP(Grade) != -1.0f))
			{
				cout << "�γ̺�Ϊ" << SubjectNumber << "�ĵ�" << j + 1 << "��ѧ����Ϣ:ѧ��" << StudentNumber <<
					"����" << StudentName << "�ɼ�" << Grade << "�а����Ƿ���Ϣ�������������ݣ�" << endl;
				continue;
			}
			size_t StudentLabel;
			//���ж��Ƿ��Ѱ�����ѧ����Ϣ������ͬ�жϿ�Ŀ��Ϣ
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
	cout << "--------------------------����¼��--------------------------------" << endl;
	string StudentName, StudentNumber, SubjectNumber, SubjectName, Grade;
	size_t StudentLabel, SubjectLabel;
	cout << "����������ѧ�ţ��γ̺ţ��ɼ�(��ĸ��ʾ)���ÿո������������W��������¼��:" << endl;
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
	//�ж�ѧ�Ŵ�������Ϸ���
	while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
	{
		if (pCUser->CheckStudentNumber(StudentNumber))
		{
			cout << "ѧ��" << StudentNumber << "�����ڣ��Ƿ���ӣ�(�������ѧ����������������W)" << endl;
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
			cout << "ѧ��<" << StudentNumber << ">���Ϸ������������룡(������W����)" << endl;
			cin >> StudentNumber;
			if (StudentNumber == string("W"))
			{
				ClearInput();
				return;
			}
		}
	}
	//�жϿγ̺Ŵ�������Ϸ���
	while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
	{
		if (pCUser->CheckSubjectNumber(SubjectNumber))
		{
			int Credit;
			cout << "�γ̺�" << SubjectNumber << "�����ڣ��Ƿ���ӣ�(�������γ�����ѧ��������������W)" << endl;
			cin >> SubjectName;
			if (SubjectName == string("W"))
			{
				ClearInput();
				return;
			}
			cin >> Credit;
			while (!pCUser->CheckCredit(Credit))
			{
				cout << "��Ч��ѧ���������������������W����:";
				cin >> Credit;
			}

			pCUser->AddSubject(SubjectName, SubjectNumber, Credit);
		}
		else
		{
			cout << "�γ̺�<" << SubjectNumber << ">���Ϸ������������룡(������W����)" << endl;
			cin >> SubjectNumber;
			if (SubjectNumber == string("W"))
			{
				ClearInput();
				return;
			}
		}
	}
	//�жϳɼ��Ϸ���
	while (GetGP(Grade) == -1.0f)
	{
		cout << "����ѧ��" << StudentNumber << "�γ̺�" << SubjectNumber << "����ĳɼ�<" << Grade <<
			">��Ч��������һ����ĸ�ɼ�����A+,F��,������W����" << endl;
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
	cout << "������Ŀ��ѧ����ѧ��:";
	cin >> StudentNumber;

	size_t StudentLabel;
	//�ж�ѧ�źϷ���
	while (!(pCUser->CheckStudentNumber(StudentNumber)))
	{
		cout << "��Ч��ѧ��!���������������W����!" << endl;
		cin >> StudentNumber;
		if (StudentNumber == string("W"))
		{
			ClearInput();
			return;
		}
	}
	//�ж�ѧ�Ŵ�����
	while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
	{

		cout << "δ�ҵ�ѧ��Ϊ" << StudentNumber << "��ѧ�����������������ѧ��������W����" << endl;
		string StudentName;
		cin >> StudentName;
		if (StudentName == string("W"))
		{
			ClearInput();
			return;
		}
		pCUser->AddStudent(StudentName, StudentNumber);

	}
	//ѭ������γ̳ɼ�
	while (true)
	{
		system("cls");
		cout << "������γ̺���ɼ�,�ÿո������������W����" << endl;
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
		//�жϿγ̺Ŵ�������Ϸ���
		while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
		{
			if (pCUser->CheckSubjectNumber(SubjectNumber))
			{
				cout << "�γ̺�" << SubjectNumber << "�����ڣ��Ƿ���ӣ�(��ӷֱ�����γ�����ѧ�֣���������W)" << endl;
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
					cout << "��Ч��ѧ���������������������W����:";
					cin >> Credit;
				}
				pCUser->AddSubject(SubjectName, SubjectNumber, Credit);
			}
			else
			{
				cout << "�γ̺�<" << SubjectNumber << ">���Ϸ������������룡(������W����)" << endl;
				cin >> SubjectNumber;
				if (SubjectNumber == string("W"))
				{
					ClearInput();
					return;
				}
			}
		}
		//�жϳɼ��Ϸ���
		while (GetGP(Grade) == -1.0f)
		{
			cout << "����ѧ��" << StudentNumber << "�γ̺�" << SubjectNumber << "����ĳɼ�<" << Grade <<
				">��Ч��������һ����ĸ�ɼ�����A+,F��,������W����" << endl;
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
	cout << "������Ŀ��γ̵Ŀγ̺�:";
	cin >> SubjectNumber;

	size_t SubjectLabel;
	//�жϿγ̺źϷ���
	while (!(pCUser->CheckSubjectNumber(SubjectNumber)))
	{
		cout << "��Ч�Ŀγ̺�!���������������W����!" << endl;
		cin >> SubjectNumber;
		if (SubjectNumber == string("W"))
		{
			ClearInput();
			return;
		}
	}
	//�жϿγ̺Ŵ�����
	while (!(SubjectLabel = pCUser->FindSubject(SubjectNumber)))
	{

		cout << "δ�ҵ��γ�Ϊ" << SubjectNumber << "�Ŀγ̣�������γ�����ѧ��(�ո����)��ӿγ̻�����W����" << endl;
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
			cout << "��Ч��ѧ���������������������W����:";
			cin >> Credit;
		}
		pCUser->AddSubject(SubjectName, SubjectNumber, Credit);

	}
	//ѭ������ѧ���ɼ�
	while (true)
	{
		system("cls");
		cout << "������ѧ����ɼ�,�ÿո������������W����" << endl;
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
		//�ж�ѧ�Ŵ�������Ϸ���
		while (!(StudentLabel = pCUser->FindStudent(StudentNumber)))
		{
			if (pCUser->CheckStudentNumber(StudentNumber))
			{
				cout << "ѧ��" << StudentNumber << "�����ڣ��Ƿ���ӣ�(�������ѧ��������������W)" << endl;
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
				cout << "ѧ��<" << StudentNumber << ">���Ϸ������������룡(������W����)" << endl;
				cin >> StudentNumber;
				if (StudentNumber == string("W"))
				{
					ClearInput();
					return;
				}
			}
		}
		//�жϳɼ��Ϸ���
		while (GetGP(Grade) == -1.0f)
		{
			cout << "����ѧ��" << StudentNumber << "�γ̺�" << SubjectNumber << "����ĳɼ�<" << Grade <<
				">��Ч��������һ����ĸ�ɼ�����A+,F��,������W����" << endl;
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
	cout << "ע:����¼������ϸ��ո�ʽ��д���ı��ĵ�����������¼��ɼ��Ŀγ���������������γ̺ţ��γ�����" <<
		"�γ�ѧ�֣����������ÿ��ѧ����ѧ�ţ���������ĸ��ʾ�ĳɼ���������Ϣ֮���ÿո����" << endl;
	cout << "����������¼���ļ���" << endl;
	string szFileName;
	cin >> szFileName;
	FileOpetate(szFileName, 'r');
	cout << "¼�������" << endl;
	PressAnyKeyToContinue();
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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

void CQueryStudents::Exit(CUser* pCUser)
{
}

void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯѧ����ѧ��:(����������W)";
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
		cout << "�Ƿ���Ҫɾ�Ļ�����ɼ���Ϣ?" << endl;
		while (PressAnyKeyToContinue(27, "��ESC����,������������༭��Ϣ��"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		return;
	}
	else
	{
		cout << "δ�ҵ���ѧ�Ŷ�Ӧѧ�����Ƿ���Ӹ�ѧ��?" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter�����ѧ������������������ء�"))
		{
			string StudentName;
			cout << "����������(������W����):";
			cin >> StudentName;
			if (StudentName == string("W"))
			{
				ClearInput();
				QueryStudent(pCUser);
			}
			else
			{
				pCUser->AddStudent(StudentName, StudentNumber);
				cout << "���ѧ���ɹ���������������¼��ɼ�����¼��ѧ���ɼ���";
				PressAnyKeyToContinue();
			}
		}
		else return;
	}
}

void CQueryStudents::EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLabel)
{
	cout << "������Ŀ��γ̵Ŀγ̺�:(����������W)";
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
			cout << "�γ̺�Ϊ" << SubjectNumber << "�γ���Ϊ" << g_vSubject[SubjectLabel].GetName() << "�Ŀεĳɼ�Ϊ"
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
			cout << "δ�ҵ��γ̺�Ϊ" << SubjectNumber << "�Ŀγ̳ɼ������ϣ����ӳɼ�������ɼ�����д��ĸ��������������W:" << endl;
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
		cout << "δ�ҵ��γ̺�Ϊ" << SubjectNumber << "�Ŀγ���Ϣ�����ϣ����Ӹÿγ���ǰ���ɼ�¼��˵���" << endl;

	}
}

void CQueryStudents::EditStudent(CUser* pCUser)
{
	system("cls");
	cout << "��������޸�ѧ����ѧ��(������W�˳�):";
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
		cout << "ѧ��Ϊ" << StudentNumber << "��ѧ������Ϊ" << g_vStudent[Label].GetName() << endl;
		cout << "��������ĺ������(ע:ѧ����ΪΨһ��ݱ�ʶ��Ӧ֧���޸ģ�����W�˳��޸�):";
		string Name;
		cin >> Name;
		if (Name == string("W"))
		{
			ClearInput();
			return;
		}
		g_vStudent[Label].SetName(Name);
		cout << "�޸ĳɹ�!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		cout << "δ�ҵ���ѧ��ѧ����" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter���������������������˳�"))
			EditStudent(pCUser);
		else
			return;
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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

void CQuerySubjects::Exit(CUser* pCUser)
{

}

void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯ�γ̵Ŀγ̺�:(��������W)";
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
		cout << "�Ƿ���Ҫɾ�Ļ�����ɼ���Ϣ?" << endl;
		while (PressAnyKeyToContinue(27, "��ESC����,����������������༭��Ϣ��"))
		{
			EditInfomation(pCUser, SubjectNumber, SubjectLabel);

		}
		return;
	}
	else
	{
		cout << "δ�ҵ��ÿγ̺Ŷ�Ӧ�γ̣��Ƿ���������?(��ӿγ��뵽¼��ɼ�����)" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter���������룬��������������ء�"))
			QuerySubject(pCUser);
	}
}

void CQuerySubjects::EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLabel)
{
	cout << "������Ŀ��ѧ����ѧ��:(����������W)";
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
	cout << "��������޸Ŀγ̵Ŀγ̺�(������W�˳�):";
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
		cout << "�γ�Ϊ" << Number << "�Ŀγ���Ϊ" << g_vSubject[Label].GetName() << "," <<
			g_vSubject[Label].GetCredit() << "ѧ��" << ",�������޸ĺ�Ŀγ�����ѧ��" <<
			"(ע:�γ̺���Ϊ�γ�Ψһ��ʶ����Ӧ֧���޸�,����W�˳��޸�):" << endl;
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
			cout << "�����ѧ��" << Credit << "�Ƿ�������������:";
			cin >> Credit;
		}
		g_vSubject[Label].SetName(Name);
		g_vSubject[Label].ChangeCredit(Credit);
		cout << "�޸ĳɹ�!" << endl;
		PressAnyKeyToContinue();
	}
	else
	{
		cout << "δ�ҵ��ÿγ̺ſγ̣�" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter���������������������˳�"))
			EditSubject(pCUser);
		else
			return;
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
		cout << "��" << i + 1 << "��:" << vGPAList[i]->GetNumber() <<
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
	for (auto IteratorForStudent = g_vStudent.begin() + 1; IteratorForStudent != g_vStudent.end(); IteratorForStudent++)//��������ѧ��
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{
			if (IteratorForSubject->GetGrade() == string("F"))//������ѧ�����пγ̣��ҵ��������
				cout << "ѧ��" << IteratorForStudent->GetNumber() << "  ����" << IteratorForStudent->GetName() <<
				":" << "\t�γ̺�" << IteratorForSubject->GetNumber() << " �γ�����" <<
				g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() <<
				endl;//���ѧ�š��������γ̺š��γ���
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
	case '\r':
		cout << "���ڴ浵�У�����ǿ�ƹر�...";
		FileOpetate("SaveData.dat", 'w');
		PressAnyKeyToContinue('\0', "�浵�ɹ�����������˳�");
		exit(0);
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
	//��д��ѧ������д��ѧ��ѧ�š��������γ������γ�����
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
	//��д��γ�����д��γ̺š��γ�����ѧ�֡�ѧ������ѧ������
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
	//д��ѧ����ѧ����ϵ��map
	for (auto MapIterator = g_mNumberToStudent.begin(); MapIterator != g_mNumberToStudent.end(); MapIterator++)
	{
		m_ofstream << MapIterator->first << " " << MapIterator->second << " ";
	}
	//д��γ̺���γ̹�ϵ��map
	for (auto MapIterator = g_mNumberToSubject.begin(); MapIterator != g_mNumberToSubject.end(); MapIterator++)
	{
		m_ofstream << MapIterator->first << " " << MapIterator->second << " ";
	}

}