// TestReadFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileReadStream.h"


int main()
{
	FileReadStream fileStream1(_T("FileName.txt"));

	_tprintf(_T("%s"), _T("Object FileReadStream has been created\r\n"));

	IReadStream *pStream = NULL;
	pStream = &fileStream1;

	pStream->startRead();

	do {

		pStream->readBlock();

	} while (true);

	_tprintf(_T("%s"), _T("Press any key and Enter to exit...\r\n"));

	TCHAR ch = 0;
	_tscanf_s(_T("%c"), &ch, 1);

    return 0;
}

