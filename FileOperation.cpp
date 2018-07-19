#include "FileOperation.h"
#include "ConsoleUtils.h"

CFileOperation::CFileOperation()
{

}

CFileOperation::~CFileOperation()
{
	//����ļ�����Ϣ
	m_szFileName.clear();
}

//һϵ���ļ�����
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

//���ļ�
void CFileOperation::OpenFile(const char cLabel)
{
	switch (cLabel)
	{
	case 'r':
		m_ifstream.open(m_szFileName, ios_base::in|| ios_base::_Nocreate);
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

//�ر��ļ�
void CFileOperation::CloseFile()
{
	if (m_ofstream)
		m_ofstream.close();
	if (m_ifstream)
		m_ifstream.close();

}

//���󱨸�
enum_error CFileOperation::FileErrorReport()
{
	switch (m_iError)
	{
	case SMOOTH:
		break;
	case OFSTREAM_OPEN_FAIL:
		system("cls");
		std::cout << "�����ļ�" << m_szFileName << "ʧ�ܣ��Ƿ�����?";
		if (PressAnyKeyToContinue('\r', "��Enter�����ԣ������������������"))
		{
			m_iError = SMOOTH;
			OpenFile( 'w');
		}
		else return OFSTREAM_OPEN_FAIL;
		break;
	case IFSTREAM_OPEN_FAIL:
		system("cls");
		cout << "δ�ҵ����ļ�" << m_szFileName << ",�Ƿ����ԣ�";
		if (PressAnyKeyToContinue('\r', "��Enter�����ԣ������������������"))
		{
			m_iError = SMOOTH;
			OpenFile('r');
		}
		return IFSTREAM_OPEN_FAIL;
		break;
	}
	return SMOOTH;
}
