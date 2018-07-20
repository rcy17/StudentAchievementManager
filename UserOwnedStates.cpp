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

//��ȡCInitialize��Ψһʵ��
CInitialize* CInitialize::Instance()
{
	static CInitialize instance;

	return &instance;
}

//����CInitialize(ʵ�ʲ������õ�)
void CInitialize::Enter(CUser* pCUser)
{
	PressAnyKeyToContinue();
	//�������õ���ӭ����Ľ��뺯��
}

//CInitialize��ִ�к���
void CInitialize::Execute(CUser* pCUser)
{
	//�ȶ�ȡ�ļ�����
	FileOpetate("SaveData.dat", 'r');
	//�˴��ǻ�ӭ����
	CoutMenu(WELCOME);
	//�������˵�
	pCUser->ChangeCState(CMainMenu::Instance());

}

//CInitialize�˳�����
void CInitialize::Exit(CUser* pCUser)
{

}

//CInitialize��ȡ���ݵĺ���
void CInitialize::ReadData()
{
	//�ȶ���ѧ�����ٶ���ѧ��ѧ�š��������γ������γ�����
	size_t StudentCount;
	m_ifstream >> StudentCount;

	//���ڵ�0��ѧ��λ���ѱ�ϵͳռ�ã���1��ʼ����
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string StudentName, StudentNumber;
		size_t StudentSubject;

		//��ȡѧ�ţ��������γ���
		m_ifstream >> StudentNumber >> StudentName >> StudentSubject;
		g_vStudent.push_back(CStudent(StudentName, StudentNumber));
		for (size_t j = 0; j < StudentSubject; j++)
		{
			//����γ�����
			string List;
			m_ifstream >> List;
			g_vStudent[i].m_lstSubjects.push_back(List);
		}
	}

	//�ȶ���ѧ�����ٶ���ѧ��ѧ�š��������γ������γ�����
	size_t SubjectCount;
	m_ifstream >> SubjectCount;

	//���ڵ�0���γ�λ���ѱ�ϵͳռ�ã���1��ʼ����
	for (size_t i = 1; i <= SubjectCount; i++)
	{
		string SubjectName, SubjectNumber;
		size_t SubjectStudent;
		int SubjectCredit;

		//��ȡ�γ̺ţ��γ������γ�ѧ�֣�ѡ������
		m_ifstream >> SubjectNumber >> SubjectName >> SubjectCredit >> SubjectStudent;
		g_vSubject.push_back(CSubject(SubjectName, SubjectNumber, SubjectCredit));
		for (size_t j = 0; j < SubjectStudent; j++)
		{
			string List;

			//��ȡѧ������
			m_ifstream >> List;
			g_vSubject[i].m_lstStudents.push_back(List);
		}
	}

	//����ѧ����ѧ����ϵ��map
	for (size_t i = 1; i <= StudentCount; i++)
	{
		string Number;
		size_t Label;

		//�ȶ���ѧ�ţ��ٶ����±�
		m_ifstream >> Number >> Label;
		g_mNumberToStudent.insert(pair<string, size_t>(Number, Label));
	}

	//д��γ̺���γ̹�ϵ��map
	for (size_t i = 1; i <= SubjectCount; i++)
	{
		string Number;
		size_t Label;

		//�ȶ���γ̺ţ��ٶ����±�
		m_ifstream >> Number >> Label;
		g_mNumberToSubject.insert(pair<string, size_t>(Number, Label));
	}
}

//��Ϊ��CInitializeȷ��Ϊһ���ǳ�����
void CInitialize::WriteData()
{
	return;
}

//--------------------------------------������ķ�����

//��ȡCMainMenuΨһʵ��
CMainMenu* CMainMenu::Instance()
{
	static CMainMenu instance;

	return &instance;
}

//CMainMenu���뺯������ӡ�������Ϣ
void CMainMenu::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != MAIN)
	{
		CoutMenu(MAIN);
		pCUser->CUser::ChangeCurrentMenu(MAIN);
	}
}

//CMainMenuִ�к������û����в���
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

//CMainMenu�˳�����
void CMainMenu::Exit(CUser* pCUser)
{

}


//--------------------------------------¼��ɼ�����ķ�����

//��ȡCInputResultsΨһʵ��
CInputResults* CInputResults::Instance()
{
	static CInputResults instance;

	return &instance;
}

//CInputResults���뺯������ӡ�������Ϣ
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

//CInputResultsִ�к������ȴ��û�ѡ��¼�뷽ʽ
void CInputResults::Execute(CUser* pCUser)
{
	//¼�����ͬһ��ɫ
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);

	//���������Ӳ˵���������Ϊ
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
			//����5����ESC�������˵�
			pCUser->ChangeCState(CMainMenu::Instance());
			break;
		default:
			cout << "\a\r�밴����Ч����";
			break;
		}
		break;

	case INPUT_STUDENT:
		//�Ƚ���ѧ���ɼ�¼��˵�
		StudentInput(pCUser);
		//¼����ɺ󷵻�¼�����˵�
		Enter(pCUser);
		break;

	case INPUT_SUBJECT:
		//�Ƚ���γ̳ɼ�¼��˵�
		SubjectInput(pCUser);
		//¼����ɷ���¼�����˵�
		Enter(pCUser);
		break;

	case INPUT_FREE:
		//�Ƚ�������¼��˵�
		FreeInput(pCUser);
		//¼����ɺ����¼�����˵�
		Enter(pCUser);
		break;

	case INPUT_FILE:
		//�Ƚ�������¼��˵�
		FileInput(pCUser);
		//¼����ɺ����¼�����˵�
		Enter(pCUser);
		break;
	}
}

//CInputResults�˳�����
void CInputResults::Exit(CUser* pCUser)
{

}

//CInputResults����¼���õĶ�ȡ����
void CInputResults::ReadData()
{
	//��¼��γ�����
	size_t SubjectCount;
	m_ifstream >> SubjectCount;
	if (m_ifstream.fail())
	{
		cout << "��������ʧ�ܣ���ֹ¼��!" << endl;
		PressAnyKeyToContinue();
		return;
	}
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
		m_ifstream >> SubjectNumber;
		m_ifstream >> SubjectName;
		m_ifstream >> Credit;
		m_ifstream >> StudentCount;
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
			m_ifstream >> StudentNumber;
			m_ifstream >> StudentName;
			m_ifstream >> Grade;
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

//��Ϊ��CInputResultsȷ��Ϊ�ǳ�����
void CInputResults::WriteData()
{

}

//CInputResults����¼�����
void CInputResults::FreeInput(CUser* pCUser)
{
	system("cls");
	cout << "--------------------------����¼��--------------------------------" << endl;
	string StudentName, StudentNumber, SubjectNumber, SubjectName, Grade;
	size_t StudentLabel, SubjectLabel;
	cout << "����������ѧ�ţ��γ̺ţ��ɼ�(��ĸ��ʾ)���ÿո������������W��������¼��:" << endl;

	//¼��ѧ���Ų��ж��˳�
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}

	//¼��γ̺Ų��ж��Ƴ�
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}

	//¼��ɼ����ж��˳�
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

//CInputResultsѧ���ɼ�¼�����
void CInputResults::StudentInput(CUser* pCUser)
{
	system("cls");
	string StudentNumber;
	cout << "������Ŀ��ѧ����ѧ��(������W����):";

	//¼��ѧ�Ų��жϷ���
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
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

		//¼��γ̺Ų��жϷ���
		cin >> SubjectNumber;
		if (SubjectNumber == string("W"))
		{
			ClearInput();
			return;
		}

		//¼��ɼ����жϷ���
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

//CInputResults�γ̳ɼ�¼�����
void CInputResults::SubjectInput(CUser* pCUser)
{
	system("cls");
	string SubjectNumber;
	cout << "������Ŀ��γ̵Ŀγ̺�(������W����):";

	//¼��γ̺Ų��жϷ���
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
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

//CInputResults����¼�����
void CInputResults::FileInput(CUser* pCUser)
{
	system("cls");
	cout << "ע:����¼������ϸ��ո�ʽ��д���ı��ĵ�����������¼��ɼ��Ŀγ���������������γ̺ţ��γ�����" <<
		"�γ�ѧ�֣����������ÿ��ѧ����ѧ�ţ���������ĸ��ʾ�ĳɼ���������Ϣ֮���ÿո����" << endl;
	cout << "����������¼��������ļ���(������W����)" << endl;
	string szFileName;

	//�����ļ������жϷ���
	ClearInput();
	cin >> szFileName;
	if (szFileName == string("W"))
	{
		ClearInput();
		return;
	}
	FileOpetate(szFileName, 'r');
	cout << "¼�������" << endl;
	PressAnyKeyToContinue();
}

//--------------------------------------���ѧ���ɼ�����ķ�����

//��ȡCQueryStudentsΨһʵ��
CQueryStudents* CQueryStudents::Instance()
{
	static CQueryStudents instance;

	return &instance;
}

//CQueryStudents���뺯������ӡ�������Ϣ
void CQueryStudents::Enter(CUser* pCUser)
{
	//���˵����ڲ��ѧ���ɼ����棬���л������ѧ���ɼ�����
	if (pCUser->Menu() != STUDENTS)
	{
		CoutMenu(STUDENTS);

		pCUser->CUser::ChangeCurrentMenu(STUDENTS);
	}
}

//CQueryStudentsִ�к������ȴ��û�����
void CQueryStudents::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		//�����ѯ����
		QueryStudent(pCUser);
		//��ѯ��ص�CQueryStudents������
		CoutMenu(STUDENTS);
		break;
	case '2':
		//����༭ѧ����Ϣ����
		EditStudent(pCUser);
		//�༭��ص�CQueryStudents������
		CoutMenu(STUDENTS);
		break;
	case '3':
	case 27:
		//����3����ESC�ص����˵�
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\a\r�밴����Ч����";
		break;
	}
}

//CQueryStudents�˳�����
void CQueryStudents::Exit(CUser* pCUser)
{
}

//CQueryStudents��ѯѧ����Ϣ����
void CQueryStudents::QueryStudent(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯѧ����ѧ��:(����������W)";
	string StudentNumber;

	//����ѧ�Ų��жϷ���
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;

	//�����ҵ�ѧ�����ӡ���γ̳ɼ�
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		for (auto iterator = g_vStudent[StudentLabel].m_lstSubjects.begin(); iterator != g_vStudent[StudentLabel].m_lstSubjects.end(); iterator++)
		{
			//��ӡ�����ƿγ̺ţ��γ������ɼ�
			cout << iterator->GetNumber() << "\t" << g_vSubject[pCUser->FindSubject(iterator->GetNumber())].GetName() <<
				" " << iterator->GetGrade() << endl;
		}

		//����γ̾���
		float GPA = g_vStudent[StudentLabel].GetGPA();
		if (GPA == -2.0f)
			cout << "��ѧ��������ЧGPA��Ϣ" << endl;
		else
		{
			cout << "��ѧ��GPAΪ";
			cout.precision(4);
			cout << GPA << endl;
		}
		cout << "�Ƿ���Ҫɾ�Ļ�����ɼ���Ϣ?" << endl;
		while (!PressAnyKeyToContinue(27, "��ESC����,������������༭��Ϣ��"))
		{
			EditInfomation(pCUser, StudentNumber, StudentLabel);

		}
		return;
	}

	//�Ҳ�����ѧ�Ŷ�Ӧѧ���������
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

//CQueryStudents�༭ѧ��ĳ�γ̳ɼ���Ϣ����
void CQueryStudents::EditInfomation(CUser*pCUser, const string&StudentNumber, const size_t&StudentLabel)
{
	cout << "������Ŀ��γ̵Ŀγ̺�:(����������W)";
	string SubjectNumber;

	//����γ̺Ų��жϷ���
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;

	//���γ̺Ŵ������һ������
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{

		//����ѧ���иÿƳɼ������������Ϣ���ṩɾ�ķ���
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

		//���޸ÿƳɼ��������
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

	//�γ̺Ų����������������Ϣ
	else
	{
		cout << "δ�ҵ��γ̺�Ϊ" << SubjectNumber << "�Ŀγ���Ϣ�����ϣ����Ӹÿγ���ǰ���ɼ�¼��˵���" << endl;
		PressAnyKeyToContinue();
	}
}

//CQueryStudentsѧ��������Ϣ�޸Ľ���
void CQueryStudents::EditStudent(CUser* pCUser)
{
	system("cls");
	cout << "��������޸�ѧ����ѧ��(������W�˳�):";
	string StudentNumber;

	//����ѧ�Ų��жϷ���
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;

	//��ѧ�Ŵ����������Ϣ
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

	//ѧ�Ų������������
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

//--------------------------------------��Ŀγ̳ɼ��ķ�����

//��ȡCQuerySubjectsΨһʵ��
CQuerySubjects* CQuerySubjects::Instance()
{
	static CQuerySubjects instance;

	return &instance;
}

//CQuerySubjects���뺯������ӡ�������Ϣ
void CQuerySubjects::Enter(CUser* pCUser)
{
	//���˵����ڲ�Ŀγ̳ɼ����棬���л�����Ŀγ̳ɼ�����
	if (pCUser->Menu() != SUBJECTS)
	{
		CoutMenu(SUBJECTS);

		pCUser->CUser::ChangeCurrentMenu(SUBJECTS);
	}
}

//CQuerySubjectsִ�к������ȴ��û�����
void CQuerySubjects::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�
	SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	char c = _getch();
	switch (c)
	{
	case '1':
		//�����ѯ�γ̳ɼ�����
		QuerySubject(pCUser);
		//���ؿγ̲�ѯ���˵�
		CoutMenu(SUBJECTS);
		break;

	case '2':
		//����γ���Ϣ���Ľ���
		EditSubject(pCUser);
		//���ؿγ̲�ѯ���˵�
		CoutMenu(SUBJECTS);

	case '3':
	case 27:
		//����3����ESC�������˵�
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
		cout << "\a\r�밴����Ч����";
		break;
	}
}

//CQuerySubjects�˳�����
void CQuerySubjects::Exit(CUser* pCUser)
{

}

//CQuerySubjects�γ̲�ѯ����
void CQuerySubjects::QuerySubject(CUser* pCUser)
{
	system("cls");
	cout << "���������ѯ�γ̵Ŀγ̺�:(��������W)";
	string SubjectNumber;

	//����γ̺Ų��жϷ���
	ClearInput();
	cin >> SubjectNumber;
	if (SubjectNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t SubjectLabel;

	//���γ̺Ŵ��ڣ������ѧ���ɼ���Ϣ
	if (SubjectLabel = pCUser->FindSubject(SubjectNumber))
	{

		//�������ѧ�ţ�ѧ���������γ̳ɼ�
		for (auto iterator = g_vSubject[SubjectLabel].m_lstStudents.begin(); iterator != g_vSubject[SubjectLabel].m_lstStudents.end(); iterator++)
		{
			cout << iterator->GetNumber() << " " << g_vStudent[pCUser->FindStudent(iterator->GetNumber())].GetName() <<
				" " << iterator->GetGrade() << endl;
		}

		//����γ̾���
		float GPA = g_vSubject[SubjectLabel].GetGPA();
		if (GPA == -2.0f)
		{
			cout << "�ÿ�ΪP/F�γ̣�������GPA" << endl;
		}
		else
		{
			cout << "�ÿγ�ƽ���ɼ�Ϊ";
			cout.precision(4);
			cout << GPA << endl;
		}
		cout << "�Ƿ���Ҫɾ�Ļ�����ɼ���Ϣ?" << endl;
		while (!PressAnyKeyToContinue(27, "��ESC����,����������������༭��Ϣ��"))
		{
			//����ѧ���ɼ��޸Ľ���
			EditInfomation(pCUser, SubjectNumber, SubjectLabel);
		}
		return;
	}

	//������������������
	else
	{
		cout << "δ�ҵ��ÿγ̺Ŷ�Ӧ�γ̣��Ƿ���������?(��ӿγ��뵽¼��ɼ�����)" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter���������룬��������������ء�"))
			QuerySubject(pCUser);
	}
}

//CQuerySubjects�γ�ĳѧ���ɼ��޸Ľ���
void CQuerySubjects::EditInfomation(CUser*pCUser, const string&SubjectNumber, const size_t&SubjectLabel)
{
	cout << "������Ŀ��ѧ����ѧ��:(����������W)";
	string StudentNumber;

	//����ѧ�Ų��жϷ���
	ClearInput();
	cin >> StudentNumber;
	if (StudentNumber == string("W"))
	{
		ClearInput();
		return;
	}
	size_t StudentLabel;

	//��ѧ�Ŵ����������ѧ���ÿ���Ϣ
	if (StudentLabel = pCUser->FindStudent(StudentNumber))
	{
		//��ѧ���ɼ��������ӡ����Ϣ
		if (g_vSubject[SubjectLabel].GetStudentGrade(StudentNumber) != string("W"))
		{
			string NewGrade;
			cout << "ѧ��Ϊ" << StudentNumber << "����Ϊ" << g_vStudent[StudentLabel].GetName() << "��ѧ���ĳɼ�Ϊ"
				<< g_vStudent[StudentLabel].GetSubjectGrade(SubjectNumber) << endl;
			cout << "���������³ɼ�(�ô�д��ĸ��ʾ,ɾ���ɼ�������W):";
			if ((NewGrade = InputPa()) != string("W"))
			{
				g_vStudent[StudentLabel].EditSubjectGrade(SubjectNumber, NewGrade);
				g_vSubject[SubjectLabel].EditStudentGrade(StudentNumber, NewGrade);
				cout << "�޸ĳɹ�!" << endl;
			}
			else
			{
				g_vStudent[StudentLabel].DeleteSubjectGrade(SubjectNumber);
				g_vSubject[SubjectLabel].DeleteStudentGrade(StudentNumber);
				cout << "ɾ���ɹ�!" << endl;
			}
		}

		//������������Ӹ�ѧ���ɼ�
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

	//ѧ�Ų�����������Ӹ�ѧ����Ϣ
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

//CQuerySubjects�༭�γ���Ϣ����
void CQuerySubjects::EditSubject(CUser* pCUser)
{
	system("cls");
	cout << "��������޸Ŀγ̵Ŀγ̺�(������W�˳�):";
	string Number;

	//����γ̺Ų��жϷ���
	ClearInput();
	cin >> Number;
	if (Number == string("W"))
	{
		ClearInput();
		return;
	}
	size_t Label;

	//���γ̺Ŵ������ӡ�������Ϣ
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

	//������������������
	else
	{
		cout << "δ�ҵ��ÿγ̺ſγ̣�" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter����ӿγ̻�����������˳�"))
		{
			cout << "������γ�����ѧ��(�ո����)��ӿγ̻�����W����" << endl;
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
			pCUser->AddSubject(SubjectName, Number, Credit);
			cout << "��ӳɹ�!" << endl;
			PressAnyKeyToContinue();
		}

		else
			return;
	}
}

//--------------------------------------���а����ķ�����

//��ȡCRankListΨһʵ��
CRankList* CRankList::Instance()
{
	static CRankList instance;

	return &instance;
}

//CRankList���뺯������ӡ�����Ϣ
void CRankList::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != RANK)
	{
		CoutMenu(RANK);

		pCUser->CUser::ChangeCurrentMenu(RANK);
	}
}

//CRankListִ�к������ȵ��û�����
void CRankList::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�

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
		cout << "\a\r�밴����Ч����";
		break;
	}
}

//CRankList�˳�����
void CRankList::Exit(CUser* pCUser)
{

}

//�Ƚ�GPA���õıȽϺ������ṩ��sort
bool CompareGPAForStudent(CStudent*A, CStudent*B)
{
	return A->GetGPA() > B->GetGPA();
}

//�Ƚ�ѧ�����õıȽϺ������ṩ��sotr
bool CompareCreditsForStudent(CStudent*A, CStudent*B)
{
	return A->GetCredits() > B->GetCredits();
}

//CRankListչʾGPA���а���
void CRankList::ShowGPAList()
{
	system("cls");
	vector<CStudent*>vGPAList;

	//��������ѧ������ָ�����ǵ�ָ�����vector
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)
	{
		vGPAList.push_back(&(*iterator));
	}

	//��ѧ���ɼ������������
	sort(&(vGPAList[0]), &(vGPAList[vGPAList.size() - 1]), CompareGPAForStudent);
	cout << "------------------GPA���а�-------------------" << endl;
	for (size_t i = 0; i < vGPAList.size(); i++)
	{
		cout << "��" << i + 1 << "��:" << vGPAList[i]->GetNumber() <<
			"\t" << vGPAList[i]->GetName() << "\t\t";
		cout.width(4);

		float GPA = vGPAList[i]->GetGPA();
		//��GPAΪ-2.0f����˵��������Ч����
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

//CRankListչʾѧ�����а���
void CRankList::ShowCreditList()
{
	system("cls");
	vector<CStudent*>vCreditsList;

	//��������ѧ������ָ�����ǵ�ָ�����vector
	for (auto iterator = g_vStudent.begin() + 1; iterator != g_vStudent.end(); iterator++)
	{
		vCreditsList.push_back(&(*iterator));
	}

	//��ѧ��ѧ�ֽ������򲢴�ӡ
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

//CRankListչʾ�ҿƼ�¼����
void CRankList::ShowFailList()
{
	system("cls");
	cout << "----------------�ҿƼ�¼--------------------" << endl;

	//��������ѧ��
	for (auto IteratorForStudent = g_vStudent.begin() + 1; IteratorForStudent != g_vStudent.end(); IteratorForStudent++)
	{
		for (auto IteratorForSubject = IteratorForStudent->m_lstSubjects.begin(); IteratorForSubject != IteratorForStudent->m_lstSubjects.end(); IteratorForSubject++)
		{

			//������ѧ�����пγ̣��ҵ��������
			if (IteratorForSubject->GetGrade() == string("F"))
			{
				//���ѧ�š��������γ̺š��γ���
				cout << "ѧ��" << IteratorForStudent->GetNumber() << "  ����" << IteratorForStudent->GetName() <<
					":" << "\t�γ̺�" << IteratorForSubject->GetNumber() << " �γ�����" <<
					g_vSubject[g_mNumberToSubject.find(IteratorForSubject->GetNumber())->second].GetName() <<
					endl;
			}
		}
	}
	PressAnyKeyToContinue();
}

//--------------------------------------ѧ����Ϣ�������ķ�����

//��ȡCClearΨһʵ��
CClear* CClear::Instance()
{
	static CClear instance;

	return &instance;
}

//CClear���뺯������ӡ�������Ϣ
void CClear::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != CLEAR)
	{
		CoutMenu(CLEAR);

		pCUser->CUser::ChangeCurrentMenu(CLEAR);
	}
}

//CClearִ�к������ȵ��û�����
void CClear::Execute(CUser* pCUser)
{
	//�ȴ��û��������˵����ּ�
	SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
	switch (_getch())
	{
	case '1':
		//��1�����������
		Clear(pCUser);
		//�������ٴ�ӡ���ò˵���Ϣ
		CoutMenu(CLEAR);
		break;
	case '2':
	case 27:
		//��2��ESC�������˵�
		pCUser->ChangeCState(CMainMenu::Instance());
		break;
	default:
		cout << "\a\r�밴����Ч����";
		break;
	}
}

//CClear�˳�����
void CClear::Exit(CUser* pCUser)
{

}

//CClear���ѧ����Ϣ����
void CClear::Clear(CUser* pCUser)
{
	CoutMenu(CLEAR_CHOOSE);
	string StudentNumber;
	system("cls");
	cout << "����������ѧ����ѧ��(������W����):";

	//����ѧ�Ų��жϷ���
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


//--------------------------------------�˳�����ķ�����

//��ȡCExitΨһʵ��
CExit* CExit::Instance()
{
	static CExit instance;

	return &instance;
}

//CExit���뺯��������ӡ�������Ϣ
void CExit::Enter(CUser* pCUser)
{
	//���˵����������棬���л���������
	if (pCUser->Menu() != OVER)
	{
		CoutMenu(OVER);
		pCUser->CUser::ChangeCurrentMenu(OVER);
	}
}

//CExitִ�к������ȴ��û�����
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

//CExit�˳�����
void CExit::Exit(CUser* pCUser)
{

}

//��Ϊ��CExit���ǳ�����
void CExit::ReadData()
{

}

//CExitд�����ݺ��������������ļ�
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