#pragma once

enum ReadStreamStatus
{
	STREAM_IDLE = 0,
	STREAM_READ,
	STREAM_WAIT,
	STREAM_BUFFFULL,
	STREAM_END,
};

typedef
int IREADSTREAMEXCEPTION;

enum ReadStreamError
{
	STREAMERR_SUCCESS			= 0,

	STREAMERR_INVALIDPARAM		= -1,
	STREAMERR_INCORRECTSTATUS	= -2,
	STREAMERR_ALLOCMEM			= -3,
	STREAMERR_NOTINITYET		= -4,

	STREAMERR_OPENSTREAM		= -5,
	STREAMERR_READSTREAM		= -6,

	STREAMERR_NOTENOUGH			= -7,
};

#define READSTREAM_MAXBLOCKSIZE 1024

class IReadStream
{
public:

	virtual void init(int nBlockSize) = 0;

	virtual ReadStreamStatus getStatus() = 0;

	virtual void startRead() = 0;
	virtual void stopRead() = 0;
	virtual void readBlock() = 0;

	virtual unsigned int getBuffer(unsigned char *pcopyto, unsigned int uSize) = 0;
	virtual void flushBuff() = 0;

	virtual ~IReadStream() {};
};
