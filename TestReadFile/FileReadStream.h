#pragma once
#include "IReadStream.h"

class FileReadStream :
	public IReadStream
{
public:
	FileReadStream(const TCHAR *lpszFileName, unsigned int nSizeCash);
	virtual ~FileReadStream();

	void startRead();
	void readBlock();

private:
	TCHAR m_FileName[FILENAME_MAX + 1];

	unsigned int	m_SizeCash;
	unsigned char	*m_BuffCash;

	ReadStreamStatus m_Status;
	
};

