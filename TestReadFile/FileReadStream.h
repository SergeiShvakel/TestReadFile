#pragma once
#include "IReadStream.h"

class FileReadStream :
	public IReadStream
{
public:
	FileReadStream(const TCHAR *lpszFileName);
	virtual ~FileReadStream();

	void Init();
	void startRead() {};
	void readBlock() {};

private:
	TCHAR m_FileName[FILENAME_MAX + 1];


	
};

