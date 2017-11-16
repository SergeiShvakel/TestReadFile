#include "stdafx.h"
#include "FileReadStream.h"

FileReadStream::FileReadStream(const TCHAR *lpszFileName, unsigned int nSizeCash)
{
	_tcsncpy(m_FileName, lpszFileName, FILENAME_MAX);
	m_FileName[FILENAME_MAX] = 0;

	m_Status = STREAM_IDLE;
	m_SizeCash = 0;
	m_BuffCash = NULL;
}

FileReadStream::~FileReadStream()
{
	if (m_BuffCash != NULL)
		delete[] m_BuffCash;

	m_Status = STREAM_IDLE;
	m_SizeCash = 0;
	m_BuffCash = NULL;
}

void FileReadStream::startRead()
{
	m_Status = STREAM_READ;
	if (m_BuffCash != NULL)
		delete[] m_BuffCash;

	m_BuffCash = new unsigned char[m_SizeCash];
}

void FileReadStream::readBlock()
{

}