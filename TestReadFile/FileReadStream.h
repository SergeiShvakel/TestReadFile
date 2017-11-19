#pragma once
#include "IReadStream.h"

class FileReadStream :
	public IReadStream
{
public:
	FileReadStream(const TCHAR *lpszFileName, unsigned int nSizeCash);
	virtual ~FileReadStream();

	void init(int nBlockSize);

	ReadStreamStatus getStatus();

	void startRead();
	void stopRead();
	void readBlock();

	unsigned int
	getBuffer(unsigned char *pcopyto, unsigned int uSize);

	void flushBuff();

private:
	TCHAR m_FileName[FILENAME_MAX + 1];

	HANDLE m_handleFile;
	OVERLAPPED m_overlapped;
	DWORD m_dwBytesRead;

	unsigned int	m_SizeCash;
	unsigned char	*m_BuffCash;
	unsigned int    m_nCurPos;

	int m_nBlockSize;

	ReadStreamStatus m_Status;
	
	void clearCashBuff();
};

