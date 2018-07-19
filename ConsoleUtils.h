#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H
//------------------------------------------------------------------------
//
//  Name:   ConsoleUtils.h
//
//  Desc:   �������̨һЩ�������
//
//------------------------------------------------------------------------
#include"Menus.h"

#include <windows.h>
#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;

//�޸������ɫ
inline void SetTextColor(WORD colors)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ��׼������

	SetConsoleTextAttribute(hConsole, colors);//������ɫ
}

//�������������ָ��������
inline bool PressAnyKeyToContinue(const char exception = '\0', const char *s = NULL)
{
	//����ɫ��Ϊ��ɫ
	/*SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);*/

	

	if (exception == '\0')
		std::cout << "\n�����������" << std::endl;
	else
		std::cout << s << std::endl;
	//while (!_kbhit())	{}

	//��������Ԥ����������򷵻���
	char c = _getch();
	if (c == exception)
		return true;
	//һ������·��ؼ�
	return false;
}

//�����ض��˵��������Ϣ
inline void CoutMenu(enum_menu MenuNow)
{
	system("cls");
	switch (MenuNow)
	{
	case WELCOME:
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"(
*********************************************
��ӭʹ��ѧ���ɼ�����ϵͳ��
���ߣ�����Ԫ
email:rcycyzh@163.com
(������Ϊ�������ҵ���κ��˲���������ҵ��;)
*********************************************
)";
		PressAnyKeyToContinue();
		break;
	case MAIN:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ���˵�!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************���˵�****************
1.¼��ɼ�
2.��ѯ/�޸�ѧ���ɼ�
3.��ѯ/�޸Ŀγ̳ɼ�
4.ѧ�����а�
5.ѧ����Ϣ���
6.�˳�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case PUTIN:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ¼��ɼ�����!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************¼��ɼ�****************
1.ѧ���ɼ�¼��
2.�γ̳ɼ�¼��
3.����¼��
4.����¼��
5.�����ϼ��˵�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case STUDENTS:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ���ѧ���ɼ��˵�!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
**************���ѧ���ɼ�**************
1.ѡ���ѯѧ���ɼ�
2.�޸�ѧ����Ϣ
3.�����ϼ��˵�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case SUBJECTS:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ��Ŀγ̳ɼ��˵�!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
***************��Ŀγ̳ɼ�*************
1.ѡ���ѯ�γ̳ɼ�
2.�޸Ŀγ���Ϣ
3.�����ϼ��˵�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case RANK:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ���а�!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************���а�****************
1.�鿴GPA����
2.�鿴ѧ������
3.�ҿ�ͳ��
4.�����ϼ��˵�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case CLEAR:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "�ѽ���ɼ�����ϵͳ���˵�!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
*****************����˵�***************
1.ѡ�����ѧ��
2.�����ϼ��˵�
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";
		break;
	case OVER:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "������ͼ�˳�ѧ���ɼ�����ϵͳ!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
�Ƿ�ȷ���˳���
****************************************
1.��(�浵�˳�)
2.��(�����ϼ��˵�)
****************************************
���밴���ּ�������Ӧ���ܣ�

)123";

		break;
	}
}

//������뻺����
inline void ClearInput()
{
	std::cin.clear();
	std::cin.sync();
}

#endif