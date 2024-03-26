#pragma once

// 编解码的父类
class Codec 
{
public:
	Codec();
	virtual ~Codec();

	// 数据编码
	virtual int msgEncode(char **outData, int &len);
	// 数据解码
	virtual void *msgDecode(char *inData, int inLen);
};
