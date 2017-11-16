#pragma once
class IReadStream
{
public:
	
	virtual void Init() = 0;

	virtual void startRead() = 0;
	virtual void readBlock() = 0;

	virtual ~IReadStream() {};
};

enum
{

};