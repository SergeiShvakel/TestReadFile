#include "stdafx.h"
#include "FileReadStream.h"

FileReadStream::FileReadStream(const TCHAR *lpszFileName, unsigned int nSizeCash)
{
	_tcsncpy(m_FileName, lpszFileName, FILENAME_MAX);
	m_FileName[FILENAME_MAX] = 0;

	m_Status = STREAM_IDLE;
	m_SizeCash = nSizeCash;
	m_BuffCash = NULL;
	m_nCurPos = 0;

	m_nBlockSize = 0;

	m_handleFile = INVALID_HANDLE_VALUE;
	m_dwBytesRead = 0;
}

FileReadStream::~FileReadStream()
{
	stopRead();
}

void FileReadStream::clearCashBuff()
{
	if (m_BuffCash != NULL)
		delete[] m_BuffCash;
	m_BuffCash = NULL;
}

void FileReadStream::init(int nBlockSize)
{
	if (nBlockSize <= 0 || nBlockSize > READSTREAM_MAXBLOCKSIZE)
		throw IREADSTREAMEXCEPTION(STREAMERR_INVALIDPARAM);

	m_nBlockSize = nBlockSize;
}

ReadStreamStatus FileReadStream::getStatus()
{
	return m_Status;
}

void FileReadStream::startRead()
{
	if (m_Status != STREAM_IDLE)
		throw IREADSTREAMEXCEPTION(STREAMERR_INCORRECTSTATUS); // incorrect status

	if (m_nBlockSize == 0)
		throw IREADSTREAMEXCEPTION(STREAMERR_NOTINITYET); // should call init method

	m_Status = STREAM_READ;

	m_BuffCash = new unsigned char[m_SizeCash];
	if (m_BuffCash == NULL)
		throw IREADSTREAMEXCEPTION(STREAMERR_ALLOCMEM); // error creating buff cash
	m_nCurPos = 0;

	m_handleFile = ::CreateFile(m_FileName,
								GENERIC_READ,
								FILE_SHARE_READ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
								NULL);
	if (m_handleFile == INVALID_HANDLE_VALUE)
		throw IREADSTREAMEXCEPTION (STREAMERR_OPENSTREAM); // error open stream

	m_overlapped.Internal		= 0;
	m_overlapped.InternalHigh	= 0;
	m_overlapped.Offset			= 0;
	m_overlapped.OffsetHigh		= 0;
	m_overlapped.Pointer		= 0;
	m_overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void FileReadStream::stopRead()
{
	if (m_Status == STREAM_IDLE)
		return;

	m_Status = STREAM_IDLE;
	clearCashBuff();

	CloseHandle(m_handleFile);
	CloseHandle(m_overlapped.hEvent);
}

void FileReadStream::readBlock()
{
	if (m_Status == STREAM_WAIT)
	{
		// check if last read operation has been finished
		if (WaitForSingleObject(m_overlapped.hEvent, 0) == WAIT_OBJECT_0)
		{
			if (m_overlapped.InternalHigh < m_nBlockSize) // has read all data
			{
				m_nCurPos += m_overlapped.InternalHigh;

				m_Status = STREAM_END;
				return;
			}
			else
			{
				m_nCurPos += m_overlapped.InternalHigh;
				m_overlapped.Offset += m_overlapped.InternalHigh;

				m_Status = STREAM_READ; // continue reading
				return;
			}
		}
		else
		{
			return; // exit, last operation hasn't completed yet
		}
	}

	// Check for enough space for new block
	if ((m_nCurPos + m_nBlockSize) > m_SizeCash)
	{
		m_Status = STREAM_BUFFFULL;
		return;
	}

	if (ReadFile(m_handleFile,
			 m_BuffCash+m_nCurPos,
			 m_nBlockSize,
			 &m_dwBytesRead,
			 &m_overlapped) == FALSE)
	{
		DWORD dwError = GetLastError();
		if (dwError == ERROR_IO_PENDING)
		{
			m_Status = STREAM_WAIT;
		}
		else
		{
			throw IREADSTREAMEXCEPTION(STREAMERR_READSTREAM); // error read stream
		}
	}
	else
	{
		if (m_dwBytesRead < m_nBlockSize) // has read all data
			m_Status = STREAM_END;
		else
		{
			m_nCurPos += m_dwBytesRead;
		}
	}
}

unsigned int
FileReadStream::getBuffer(unsigned char *pcopyto, unsigned int uSize)
{
	if (uSize < m_nCurPos)
		throw IREADSTREAMEXCEPTION(STREAMERR_NOTENOUGH); // not enought space for data

	memcpy(pcopyto, m_BuffCash, m_nCurPos);

	return m_nCurPos;
}

void FileReadStream::flushBuff()
{
	if (m_Status != STREAM_BUFFFULL)
		throw IREADSTREAMEXCEPTION(STREAMERR_INCORRECTSTATUS); // incorrect status

	m_Status = STREAM_READ;
	m_nCurPos = 0;
}
