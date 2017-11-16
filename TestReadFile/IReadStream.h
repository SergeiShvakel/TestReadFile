#pragma once
class IReadStream
{
public:

	virtual void startRead() = 0;
	virtual void readBlock() = 0;

	virtual ~IReadStream() {};
};

enum ReadStreamStatus
{
	STREAM_IDLE = 0,
	STREAM_READ,
	STREAM_WAIT,
	STREAM_BUFFFULL,
};