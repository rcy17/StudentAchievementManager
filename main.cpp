#include "Menus.h"
#include "User.h"
#include "ConsoleUtils.h"

//一个用来标记是否继续运行的全局变量
bool g_bRunFlag = true;
int main()
{
	//注册一个用户
	CUser user;

	//通过一系列更新来实现用户的相关操作
	while (g_bRunFlag)
	{
		user.Update();
	}
	return 0;
}