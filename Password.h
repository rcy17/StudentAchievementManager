#ifndef PASSWORD_H
#define PASSWORD_H
//------------------------------------------------------------------------
//
//  Name:   Password.h
//
//  Desc:   定义密码类，给出了关于读写密码的操作
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
	//用户需要输入两次相同密码后方可继续
	while (true)
	{
		m_KeyInput.clear();
		do
		{
			//若输入了不符合长度的，则提示重新输入
			if (m_KeyInput.length())
			{
				cout << "密码应当在6到16位之间,请重新输入:";
			}
			else
			{
				cout << "请输入设定的(不能包含空格)密码:";
			}
			ClearInput();
			cin >> m_KeyInput;
		} while (m_KeyInput.length() < 6 || m_KeyInput.length() > 16);


		string ForSure;
		cout << "请再次输入密码:";
		ClearInput();
		cin >> ForSure;
		if (m_KeyInput == ForSure)
		{
			break;
		}
		else
		{
			cout << "两次密码输入不一致，请重新输入！\n";
		}
	}
	m_Key.clear();

	//采用自己编写的随机数算法进行加密
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
			cout << "密码错误，请重新输入!" << endl;
		}
	}
	cout << "密码正确!" << endl;
}


#endif