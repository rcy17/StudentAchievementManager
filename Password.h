#ifndef PASSWORD_H
#define PASSWORD_H
//------------------------------------------------------------------------
//
//  Name:   Password.h
//
//  Desc:   ���������࣬�����˹��ڶ�д����Ĳ���
//
//------------------------------------------------------------------------

#include "FileOperation.h"
#include "ConsoleUtils.h"

class CPassword :public CFileOperation
{
public:
	CPassword();
	~CPassword();
	virtual void ReadData();
	virtual void WriteData();
	void SetWord();
	void InputWord();
private:
	string m_Key, m_KeyTry, m_KeyInput;
};

inline CPassword::CPassword()
{
}

inline CPassword::~CPassword()
{
}

inline void CPassword::ReadData()
{
	m_ifstream >> m_Key;
}

inline void CPassword::WriteData()
{
	m_ofstream << m_Key;
}

inline void CPassword::SetWord()
{
	//�û���Ҫ����������ͬ����󷽿ɼ���
	while (true)
	{
		m_KeyInput.clear();
		do
		{
			//�������˲����ϳ��ȵģ�����ʾ��������
			if (m_KeyInput.length())
			{
				cout << "����Ӧ����6��16λ֮��,����������:";
			}
			else
			{
				cout << "�������趨��(���ܰ����ո�)����:";
			}
			ClearInput();
			cin >> m_KeyInput;
		} while (m_KeyInput.length() < 6 || m_KeyInput.length() > 16);


		string ForSure;
		cout << "���ٴ���������:";
		ClearInput();
		cin >> ForSure;
		if (m_KeyInput == ForSure)
		{
			break;
		}
		else
		{
			cout << "�����������벻һ�£����������룡\n";
		}
	}
	m_Key.clear();

	//�����Լ���д��������㷨���м���
	for (int i = 0; i < m_KeyInput.length(); i++)
	{
		unsigned int out=0;
		srand((i + 1)*m_KeyInput[i]); 
		for (int j = 0; j < i+1 ; j++)
		{
			out = rand() % ((i + 1)*m_KeyInput[j]);
		}
		out = rand() % ((i + 1)*m_KeyInput[i]);
		m_Key += to_string(out);
	}
}

inline void CPassword::InputWord()
{
	while (true)
	{
		m_KeyTry.clear();
		cin >> m_KeyInput;
		for (int i = 0; i < m_KeyInput.length(); i++)
		{
			unsigned int out=0;
			srand((i + 1)*m_KeyInput[i]);
			for (int j = 0; j < i+1; j++)
			{
				out = rand() % ((i + 1)*m_KeyInput[j]);
			}
			out =  rand() % ((i + 1)*m_KeyInput[i]);
			m_KeyTry += to_string(out);
		}
		if (m_Key == m_KeyTry)
		{
			break;
		}
		else
		{
			cout << "�����������������!" << endl;
		}
	}
	cout << "������ȷ!" << endl;
}


#endif