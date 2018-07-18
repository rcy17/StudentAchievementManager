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



//记录错误信息
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
	//进行文件操作
	void FileOpetate(string s, const char cLabel);
private:
	
	//读取数据
	virtual void ReadData() = 0;
	//写入数据
	virtual  void WriteData()=0;
	//打开数据文件
	void OpenFile(const char cLabel);
	//关闭数据文件
	void CloseFile();
	//报告错误
	enum_error FileErrorReport();
	//文件名
	string m_szFileName;
	//输出流
	ofstream m_ofstream;
	//输入流
	ifstream m_ifstream;
	//保存最后一次错误信息
	enum_error m_iError;
};


#endif