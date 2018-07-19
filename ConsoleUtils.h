#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H
//------------------------------------------------------------------------
//
//  Name:   ConsoleUtils.h
//
//  Desc:   处理控制台一些输出问题
//
//------------------------------------------------------------------------
#include"Menus.h"

#include <windows.h>
#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;

//修改输出字色
inline void SetTextColor(WORD colors)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄

	SetConsoleTextAttribute(hConsole, colors);//设置字色
}

//按任意键继续或按指定键继续
inline bool PressAnyKeyToContinue(const char exception = '\0', const char *s = NULL)
{
	//把字色改为白色
	/*SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN);*/

	

	if (exception == '\0')
		std::cout << "\n按任意键继续" << std::endl;
	else
		std::cout << s << std::endl;
	//while (!_kbhit())	{}

	//若输入了预定的例外键则返回真
	char c = _getch();
	if (c == exception)
		return true;
	//一般情况下返回假
	return false;
}

//给出特定菜单的输出信息
inline void CoutMenu(enum_menu MenuNow)
{
	system("cls");
	switch (MenuNow)
	{
	case WELCOME:
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"(
*********************************************
欢迎使用学生成绩管理系统！
作者：饶淙元
email:rcycyzh@163.com
(本内容为程设大作业，任何人不得用于商业用途)
*********************************************
)";
		PressAnyKeyToContinue();
		break;
	case MAIN:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统主菜单!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************主菜单****************
1.录入成绩
2.查询/修改学生成绩
3.查询/修改课程成绩
4.学生排行榜
5.学生信息清除
6.退出
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case PUTIN:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统录入成绩界面!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************录入成绩****************
1.学生成绩录入
2.课程成绩录入
3.自由录入
4.批量录入
5.返回上级菜单
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case STUDENTS:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统查改学生成绩菜单!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
**************查改学生成绩**************
1.选择查询学生成绩
2.修改学生信息
3.返回上级菜单
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case SUBJECTS:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统查改课程成绩菜单!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
***************查改课程成绩*************
1.选择查询课程成绩
2.修改课程信息
3.返回上级菜单
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case RANK:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统排行榜!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
******************排行榜****************
1.查看GPA排行
2.查看学分排行
3.挂科统计
4.返回上级菜单
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case CLEAR:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "已进入成绩管理系统主菜单!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
*****************清除菜单***************
1.选择清除学生
2.返回上级菜单
****************************************
（请按数字键进入相应功能）

)123";
		break;
	case OVER:
		
		SetTextColor(FOREGROUND_BLUE | FOREGROUND_RED);
		cout << "正在试图退出学生成绩管理系统!\n";
		SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		cout << R"123(
是否确认退出？
****************************************
1.是(存档退出)
2.否(返回上级菜单)
****************************************
（请按数字键进入相应功能）

)123";

		break;
	}
}

//清空输入缓冲区
inline void ClearInput()
{
	std::cin.clear();
	std::cin.sync();
}

#endif