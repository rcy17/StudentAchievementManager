#include "FileOperation.h"
#include "ConsoleUtils.h"

CFileOperation::CFileOperation()
{

}

CFileOperation::~CFileOperation()
{
	//清除文件名信息
	m_szFileName.clear();
}

//一系列文件操作
void CFileOperation::FileOpetate(string s, const char cLabel)
{
	m_szFileName = s;
	OpenFile(cLabel);

	if (!m_iError)
		switch (cLabel)
		{
		case 'r':
			ReadData();
			break;
		case 'w':
			WriteData();
			break;
		}
	CloseFile();
}

//打开文件
void CFileOperation::OpenFile(const char cLabel)
{
	switch (cLabel)
	{
	case 'r':
		m_ifstream.open(m_szFileName, ios_base::in || ios_base::_Nocreate);
		if (!m_ifstream)
			m_iError = IFSTREAM_OPEN_FAIL;
		break;
	case 'w':
		m_ofstream.open(m_szFileName, ios_base::out);
		if (!m_ofstream)
			m_iError = OFSTREAM_OPEN_FAIL;
		break;
	}
	if (m_iError)
		FileErrorReport();
}

//关闭文件
void CFileOperation::CloseFile()
{
	if (m_ofstream)
		m_ofstream.close();
	if (m_ifstream)
		m_ifstream.close();

}

//判断是否有错误
bool CFileOperation::Good()
{
	//若无错误，则返回值为真
	if (!m_iError)
		return true;
	//若右错，则错误清除并返回假
	else
	{
		m_iError = SMOOTH;
		return false;
	}
}

//错误报告
enum_error CFileOperation::FileErrorReport()
{
	switch (m_iError)
	{
	case SMOOTH:
		break;
	case OFSTREAM_OPEN_FAIL:
		system("cls");
		std::cout << "创建文件" << m_szFileName << "失败，是否重试?";
		if (PressAnyKeyToContinue('\r', "按Enter键重试，按其他任意键继续。"))
		{
			m_iError = SMOOTH;
			OpenFile('w');
		}
		else return OFSTREAM_OPEN_FAIL;
		break;
	case IFSTREAM_OPEN_FAIL:
		system("cls");
		cout << "未找到到文件" << m_szFileName << ",是否重试？";
		if (PressAnyKeyToContinue('\r', "按Enter键重试，按其他任意键继续。"))
		{
			m_iError = SMOOTH;
			OpenFile('r');
		}
		return IFSTREAM_OPEN_FAIL;
		break;
	}
	return SMOOTH;
}
