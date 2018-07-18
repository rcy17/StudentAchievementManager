#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  文件名:   CUser.h
//
//  简述:  一个定义用户的头文件
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include<vector>
#include<map>
#include "Menus.h"
#include "Subject.h"
#include "Student.h"


class CState;
class CUser
{
private:
	//当前所处的状态
	CState * m_pCurrentCState;
	//当前所处的菜单
	enum_menu         m_Menu;
	//一个记录了所有学生的vector
	//vector<CStudent>g_vStudent;
	//一个记录了所有课程的vector
	//vector<CSubject>g_vSubject;
public:
	CUser();
	//不断执行的更新函数
	void Update();

	//这个函数将当前状态改为新状态，先调用当前函数
	//的Exit()函数，再将新状态指定为当前状态，并调
	//用新状态的Entry()函数
	void ChangeCState(CState* new_state);

	//添加vector中的学生
	void AddStudent(const string&Name,const string&Number);
	//删除vector中的学生
	bool DeleteStudent(const string&s);

	//添加vector中的课程
	void AddSubject(const string&Name, const string&Number);
	//删除vector中的课程
	/*bool DeleteSubject(const string&s);*/

	//根据学号找到一个学生下标
	size_t FindStudent(const string&s);
	//根据课程号找到一门课程下标
	size_t FindSubject(const string&s);
	//返回用户当前所处的菜单位置
	enum_menu Menu()const;
	//改变用户当前所处的菜单位置
	void ChangeCurrentMenu(const enum_menu loc);

};
#endif
