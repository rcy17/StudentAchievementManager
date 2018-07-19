#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H


#include<fstream>
#include<map>
#include<string>
#include<iostream>
using namespace std;

#include "Subject.h"
#include "Student.h"
#include "ConsoleUtils.h"



//��¼������Ϣ
enum enum_error
{
	SMOOTH,
	OFSTREAM_OPEN_FAIL,
	IFSTREAM_OPEN_FAIL,
};

class CFileOperation
{
public:
	
	CFileOperation();
	~CFileOperation();
	//�����ļ�����
	void FileOpetate(string s, const char cLabel);
	
protected:
	//�����
	ofstream m_ofstream;
	//������
	ifstream m_ifstream;
private:
	
	//��ȡ����
	virtual void ReadData() = 0;
	//д������
	virtual  void WriteData()=0;
	//�������ļ�
	void OpenFile(const char cLabel);
	//�ر������ļ�
	void CloseFile();
	//�������
	enum_error FileErrorReport();
	//�ļ���
	string m_szFileName;

	//�������һ�δ�����Ϣ
	enum_error m_iError;
};


#endif