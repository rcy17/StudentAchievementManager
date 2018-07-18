#include "User.h"
#include "UserOwnedStates.h"

//һ����¼������ѧ����vector
vector<CStudent>g_vStudent(1);
//һ����¼�����пγ̵�vector
vector<CSubject>g_vSubject(1);
//һ����¼��ѧ�ŵ�ѧ��vector�±��map
map<string, size_t>g_mNumberToStudent;
//һ����¼�˴ӿγ̺ŵ��γ�vector�±��map
map<string, size_t>g_mNumberToSubject;

CUser::CUser():m_Menu(WELCOME),m_pCurrentCState(CInitialize::Instance())
                                                                 
{
	g_vStudent[0].SetName("���޴���");
	g_vStudent[0].SetNumber("0000");
	g_vSubject[0].SetName("�޴˿γ�");
	g_vSubject[0].SetNumber("0000");
}



//--------------------------- ChangeCState -------------------------------------
//-----------------------------------------------------------------------------
void CUser::ChangeCState(CState* pNewCState)
{
  //ȷ����ǰ״̬����һ״̬����Ϊ��
  assert (m_pCurrentCState && pNewCState);

  //���õ�ǰ״̬���˳�����
  m_pCurrentCState->Exit(this);

  //״̬��Ϊ��״̬
  m_pCurrentCState = pNewCState;

  //������״̬�Ľ��뺯��
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
		cout << "���и�ѧ�������������!" << endl;
		PressAnyKeyToContinue();
	}

}

bool CUser::DeleteStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())//���ж��Ƿ��и�ѧ�ŵ�ѧ��
	{
		cout << "��ȷ��Ҫɾ��ѧ��Ϊ" << s << ",����Ϊ" << g_vStudent[FindStudent(s)].GetName() << "��ѧ����ȫ����Ϣ��" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter�������������������ȡ��"))
		{
			auto ptrLstStu = &(g_vStudent[iterator->second].m_lstSubjects);//�ҵ���ѧ���Ŀγ���������һ��
			for (auto iterator = ptrLstStu->begin(); iterator != ptrLstStu->end(); iterator++)
			{
				auto ptrLstSub = &(g_vSubject[g_mNumberToSubject.find((*iterator).GetNumber())->second].m_lstStudents);
				for (auto it = ptrLstStu->begin(); it != ptrLstStu->end(); it++)//�ٽ���ѧ���Ŀγ̶�Ӧ��ѧ���������һ��
				{
					if ((*it).GetNumber() == s)
					{
						ptrLstSub->erase(it);//ɾ���γ̵�ѧ�������и�ѧ������Ϣ
					}
					break;
				}
			}
			g_vStudent.erase(g_vStudent.begin()+iterator->second);//ɾ����ѧ����ѧ��vector�е���Ϣ
			for (auto it = g_mNumberToStudent.begin(); it != g_mNumberToStudent.end(); it++)//��vector���±�����ֵ����1
			{
				if (it->second > iterator->second)
					it->second--;
			}
			g_mNumberToStudent.erase(iterator);//ɾ����ѧ����map�е���Ϣ
			cout << "�ѳɹ�ɾ����" << endl;
			return true;
		}
		cout << "��ȡ��ɾ��!" << endl;
	}
	else
	{
		cout << "δ�ҵ���ѧ�ŵ�ѧ����" << endl;
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
		cout << "���иÿγ̣����������!" << endl;
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