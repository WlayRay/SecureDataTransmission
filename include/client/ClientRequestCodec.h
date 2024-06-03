#pragma once
#include "Codec.h"
#include "clientrequest.pb.h"

struct RequestMsg
{
    int		cmdType;		// 报文类型: 1 密钥协商; 2 密钥校验; 3 密钥注销
	char	clientId[12];	// 客户端编号
	char	authCode[65];	// 认证码
	char	serverId[12];	// 服务器端编号 
	char	r1[64];			// 客户端随机数
};

class RequestCodec : public Codec
{
public:
	enum CmdType{NewOrUpdate=1, Check, Revoke, View};
	// 解码时候使用的构造
	RequestCodec();
	// 编码时候使用的构造函数
	RequestCodec(RequestMsg* msg);
	~RequestCodec();

	// 重写父类函数
	int msgEncode(char** outData, int &len);
	void* msgDecode(char *inData, int inLen);

private:
	RequestMsg m_msg;
	ClientRequest m_clientRequest;
};

