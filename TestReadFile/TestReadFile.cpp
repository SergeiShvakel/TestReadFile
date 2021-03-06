// TestReadFile.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FileReadStream.h"


int main()
{
	FileReadStream fileStream1(_T("C:\\TEMP\\FileToRead\\CHAP000.TXT"), 2048);
	unsigned char *pReadBuff = NULL;

	_tprintf(_T("%s"), _T("Object FileReadStream has been created\r\n"));

	try
	{
		IReadStream *pStream = NULL;
		pStream = &fileStream1;

		bool bExit = true;

		pReadBuff = new unsigned char[2048];
		unsigned int nBytesRead = 0;

		pStream->init(1024); // init with 1k block size

		do {

			Sleep(250);

			ReadStreamStatus status = pStream->getStatus();

			switch (status)
			{
			case STREAM_IDLE:	// start reading
				pStream->startRead();
				break;
			case STREAM_READ:	// read next block
				pStream->readBlock();
				break;
			case STREAM_WAIT:
				pStream->readBlock();
				break;
			case STREAM_BUFFFULL:
				nBytesRead = pStream->getBuffer(pReadBuff, 2048);
				pStream->flushBuff();

				pReadBuff[32] = 0;
				_tprintf(_T("...read %d bytes, text: %s\r\n"), nBytesRead, (LPSTR)pReadBuff);

				break;
			case STREAM_END:
				nBytesRead = pStream->getBuffer(pReadBuff, 2048);
				pStream->stopRead();

				pReadBuff[32] = 0;
				_tprintf(_T("...read %d bytes, text: %s\r\n"), nBytesRead, (LPSTR)pReadBuff);

				bExit = false;
			default:
				break;
			}

		} while (bExit);

		throw IREADSTREAMEXCEPTION(0); // exit without errors
	}
	catch (IREADSTREAMEXCEPTION exitCode)
	{
		if (pReadBuff) delete[] pReadBuff;

		if (exitCode < 0)
		{
			_tprintf(_T("Exit with error: %d\r\n"), exitCode);
		}
	}
	catch (...)
	{
	}

    return 0; 
}

