#include <string.h>
#include <iostream>
#include "ServerRequestCodec.h"

using namespace std;

RequestCodec::RequestCodec() : Codec()
{
}

RequestCodec::RequestCodec(RequestMsg *msg) : Codec()
{
	m_msg.cmdType = msg->cmdType;
	strcpy(m_msg.clientId, msg->clientId);
	strcpy(m_msg.authCode, msg->authCode);
	strcpy(m_msg.serverId, msg->serverId);
	strcpy(m_msg.r1, msg->r1);
}

RequestCodec::~RequestCodec()
{
	cout << "RequestCodec destruct ..." << endl;
}

int RequestCodec::msgEncode(char **outData, int &len)
{
	m_serverRequest.set_cmdtype(m_msg.cmdType);
	m_serverRequest.set_clientid(m_msg.clientId);
	m_serverRequest.set_authcode(m_msg.authCode);
	m_serverRequest.set_serverid(m_msg.serverId);
	m_serverRequest.set_r1(m_msg.r1);
	string serializedData;
	if (!m_serverRequest.SerializeToString(&serializedData))
	{
		cerr << "序列化失败！" << endl;
		return -1;
	}

	std::cout << std::endl << "----------------------------------------------------------------" << std::endl
			  << std::endl;
	std::cout << serializedData << std::endl
			  << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

	len = serializedData.length();
	// 分配内存并复制数据到输出指针
	// 使用unique_ptr来管理内存，确保在函数返回前释放内存
	std::unique_ptr<char[]> buffer(new char[len]);
	if (!buffer)
	{
		std::cerr << "内存分配失败！" << std::endl;
		return -1;
	}
	memcpy(buffer.get(), serializedData.c_str(), len);

	// 将unique_ptr的所有权转移给调用者
	*outData = buffer.release();
	return 0;
}

void *RequestCodec::msgDecode(char *inData, int inLen)
{
	// unpackSequence((char *)inData, inLen);
	// readHeadNode(m_msg.cmdType);
	// readNextNode(m_msg.clientId);
	// readNextNode(m_msg.authCode);
	// readNextNode(m_msg.serverId);
	// readNextNode(m_msg.r1);
	string outData = inData;
	if (m_serverRequest.ParseFromString(outData))
	{
		m_msg.cmdType = m_serverRequest.cmdtype();
		strcpy(m_msg.clientId, m_serverRequest.clientid().c_str());
		strcpy(m_msg.authCode, m_serverRequest.authcode().c_str());
		strcpy(m_msg.serverId, m_serverRequest.serverid().c_str());
		strcpy(m_msg.r1, m_serverRequest.r1().c_str());
	}
	cout << "MsgRequest 解码 ok ..." << endl;
	return &m_msg;
}
