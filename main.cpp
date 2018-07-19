#include "Menus.h"
#include "User.h"
#include "ConsoleUtils.h"


int main()
{

	//注册一个用户
	CUser user;

	//通过一系列更新来实现用户的相关操作
	while (true)
	{
		user.Update();

		Sleep(20);
	}

	return 0;
}