#include "Menus.h"
#include "User.h"
#include "ConsoleUtils.h"


int main()
{

	//ע��һ���û�
	CUser user;

	//ͨ��һϵ�и�����ʵ���û�����ز���
	while (true)
	{
		user.Update();

		Sleep(20);
	}

	return 0;
}