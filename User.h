#ifndef MINER_H
#define MINER_H
//------------------------------------------------------------------------
//
//  �ļ���:   CUser.h
//
//  ����:  һ�������û���ͷ�ļ�
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
	//��ǰ������״̬
	CState * m_pCurrentCState;
	//��ǰ�����Ĳ˵�
	enum_menu         m_Menu;
	//һ����¼������ѧ����vector
	//vector<CStudent>g_vStudent;
	//һ����¼�����пγ̵�vector
	//vector<CSubject>g_vSubject;
public:
	CUser();
	//����ִ�еĸ��º���
	void Update();

	//�����������ǰ״̬��Ϊ��״̬���ȵ��õ�ǰ����
	//��Exit()�������ٽ���״ָ̬��Ϊ��ǰ״̬������
	//����״̬��Entry()����
	void ChangeCState(CState* new_state);

	//���vector�е�ѧ��
	void AddStudent(const string&Name,const string&Number);
	//ɾ��vector�е�ѧ��
	bool DeleteStudent(const string&s);

	//���vector�еĿγ�
	void AddSubject(const string&Name, const string&Number);
	//ɾ��vector�еĿγ�
	/*bool DeleteSubject(const string&s);*/

	//����ѧ���ҵ�һ��ѧ���±�
	size_t FindStudent(const string&s);
	//���ݿγ̺��ҵ�һ�ſγ��±�
	size_t FindSubject(const string&s);
	//�����û���ǰ�����Ĳ˵�λ��
	enum_menu Menu()const;
	//�ı��û���ǰ�����Ĳ˵�λ��
	void ChangeCurrentMenu(const enum_menu loc);

};
#endif
