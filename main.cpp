#include "Menus.h"
#include "User.h"
#include "ConsoleUtils.h"

//һ����������Ƿ�������е�ȫ�ֱ���
bool g_bRunFlag = true;
int main()
{
	//ע��һ���û�
	CUser user;

	//ͨ��һϵ�и�����ʵ���û�����ز���
	while (g_bRunFlag)
	{
		user.Update();
	}
	return 0;
}