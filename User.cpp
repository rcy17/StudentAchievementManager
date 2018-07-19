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
	//�û���ע��������ϵͳ�����Ŀ�ʼ�������ʼ������ϵͳ�Ĺ���״̬
	//ռ����0��λ��vector���Ա���map�����±�0ʱ�ж�Ϊδ�ҵ�
	g_vStudent[0].SetName("���޴���");
	g_vStudent[0].SetNumber("0000");
	g_vSubject[0].SetName("�޴˿γ�");
	g_vSubject[0].SetNumber("0000");
}

//�ı�״̬���˵���ʱ���õ��˺���
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

//ÿ�����ڵĸ��º���
void CUser::Update()
{
  if (m_pCurrentCState)
  {
    m_pCurrentCState->Execute(this);
  }
}

//��vector������ѧ��
void CUser::AddStudent(const string&Name, const string&Number)
{
	if (!FindStudent(Number))
	{
		//��vector�����ѧ��ʱ������������map��Ϣ����ʱ��ѧ���±����ԭ��vector��size
		g_mNumberToStudent.insert(pair<string,size_t>(Number, g_vStudent.size()));
		g_vStudent.push_back(CStudent(Name, Number));
	}
	else
	{
		cout << "���и�ѧ�������������!" << endl;
		PressAnyKeyToContinue();
	}

}

//�ж��γ̺������Ƿ�Ϸ�
bool CUser::CheckSubjectNumber(const string&SubjectNumber)
{
	auto it = SubjectNumber.begin();
	//��λ�����Ǵ�д��ĸ��������
	if (!((*it >= '0'&&*it <= '9') || (*it >= 'A'&&*it <= 'Z')))
		return false;
	//����λ��ֻ��������
	for (it++; it != SubjectNumber.end(); it++)
	{
		if (*it<'0' || *it>'9')
			return false;
	}
	return true;
}

//�ж�ѧ�������Ƿ�Ϸ�
bool CUser::CheckStudentNumber(const string&StudentNumber)
{
	//ѧ�ű����Ǵ�����
	for (auto it = StudentNumber.begin(); it != StudentNumber.end(); it++)
	{
		if (*it<'0' || *it>'9')
			return false;
	}
	return true;
}

//�ж�ѧ�������Ƿ�Ϸ�
bool CUser::CheckCredit(int Credit)
{
	//ѧ��Ӧ����һ��0��15������
	if (Credit >= 0 && Credit <= 15)
		return true;
	return false;
}

//ɾ��һ��ѧ����ȫ����Ϣ
bool CUser::DeleteStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	//���ж��Ƿ��и�ѧ�ŵ�ѧ��
	if (iterator != g_mNumberToStudent.end())
	{
		cout << "��ȷ��Ҫɾ��ѧ��Ϊ" << s << ",����Ϊ" << g_vStudent[FindStudent(s)].GetName() << "��ѧ����ȫ����Ϣ��" << endl;
		if (PressAnyKeyToContinue('\r', "��Enter�������������������ȡ��"))
		{
			auto ptrLstStu = &(g_vStudent[iterator->second].m_lstSubjects);
			//�ҵ���ѧ���Ŀγ���������һ��
			for (auto iterator = ptrLstStu->begin(); iterator != ptrLstStu->end(); iterator++)
			{
				auto ptrLstSub = &(g_vSubject[g_mNumberToSubject.find((*iterator).GetNumber())->second].m_lstStudents);
				//�ٽ���ѧ���Ŀγ̶�Ӧ��ѧ���������һ��
				for (auto it = ptrLstStu->begin(); it != ptrLstStu->end(); it++)
				{
					if ((*it).GetNumber() == s)
					{
						//ɾ���γ̵�ѧ�������и�ѧ������Ϣ
						ptrLstSub->erase(it);
					}
					break;
				}
			}
			//ɾ����ѧ����ѧ��vector�е���Ϣ
			g_vStudent.erase(g_vStudent.begin()+iterator->second);
			//��vector���±�����ֵ����1
			for (auto it = g_mNumberToStudent.begin(); it != g_mNumberToStudent.end(); it++)
			{
				if (it->second > iterator->second)
					it->second--;
			}
			//ɾ����ѧ����map�е���Ϣ
			g_mNumberToStudent.erase(iterator);
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

//���һ�ſγ�
void CUser::AddSubject(const string&Name, const string&Number,int Credit)
{
	if (!FindSubject(Number))
	{
		//��vector����ӿγ�ʱ������������map��Ϣ����ʱ�¿γ��±����ԭ��vector��size
		g_mNumberToSubject.insert(pair<string, size_t>(Number, g_vSubject.size()));
		g_vSubject.push_back(CSubject(Name, Number,Credit));
		
	}
	else
	{
		cout << "���иÿγ̣����������!" << endl;
		PressAnyKeyToContinue();
	}

}

//����ѧ���ҵ�һ��ѧ���������±�
size_t CUser::FindStudent(const string&s)
{
	auto iterator = g_mNumberToStudent.find(s);
	if (iterator != g_mNumberToStudent.end())
		return iterator->second;
	else
		return 0;
}

//���ݿγ̺��ҵ�һ�ſγ̲������±�
size_t CUser::FindSubject(const string&s)
{
	auto iterator = g_mNumberToSubject.find(s);
	if (iterator != g_mNumberToSubject.end())
		return iterator->second;
	else
		return 0;
}

//�����û���ǰ�����Ĳ˵�
enum_menu CUser::Menu()const
{
	return m_Menu;
}

//�ı��û���ǰ�����˵�
void CUser::ChangeCurrentMenu(const enum_menu loc)
{
	m_Menu = loc;
}
