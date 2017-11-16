#include "stdafx.h"
#include "FileReadStream.h"


FileReadStream::FileReadStream(const TCHAR *lpszFileName)
{
	_tcsncpy(m_FileName, lpszFileName, FILENAME_MAX);
	m_FileName[FILENAME_MAX] = 0;
}

FileReadStream::~FileReadStream()
{
}

void FileReadStream::Init()
{
	int i = 0;

	return;
}