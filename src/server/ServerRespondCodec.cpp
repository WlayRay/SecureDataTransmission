#include <stdio.h>
#include <string.h>
#include "ServerRespondCodec.h"
#include <iostream>
using namespace std;

RespondCodec::RespondCodec() : Codec()
{
}

RespondCodec::RespondCodec(RespondMsg *msg) : Codec()
{
	m_msg.rv = msg->rv;
	m_msg.seckeyid = msg->seckeyid;
	strcpy(m_msg.clientId, msg->clientId);
	strcpy(m_msg.serverId, msg->serverId);
	strcpy(m_msg.r2, msg->r2);
}

RespondCodec::~RespondCodec()
{
	cout << "RespondCodec destruct ..." << endl;
}

int RespondCodec::msgEncode(char **outData, int &len)
{
	m_serverRepond.set_rv(m_msg.rv);
	m_serverRepond.set_clientid(m_msg.clientId);
	m_serverRepond.set_serverid(m_msg.serverId);
	m_serverRepond.set_r2(m_msg.r2);
	m_serverRepond.set_seckeyid(m_msg.seckeyid);
	string serializedData;
	if (!m_serverRepond.SerializeToString(&serializedData))
	{
		cerr << "序列化数据失败！";
		return -1;
	}
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

	// std::cout << std::endl << "----------------------------------------------------------------" << std::endl
	// 		  << std::endl;
	// std::cout << serializedData << std::endl
	// 		  << std::endl;
	// std::cout << "----------------------------------------------------------------" << std::endl;

	// 将unique_ptr的所有权转移给调用者
	*outData = buffer.release();
}

void *RespondCodec::msgDecode(char *inData, int inLen)
{
	// unpackSequence((char *)inData, inLen);
	// readHeadNode(m_msg.rv);
	// readNextNode(m_msg.clientId);
	// readNextNode(m_msg.serverId);
	// readNextNode(m_msg.r2);
	// readNextNode(m_msg.seckeyid);

	string outData = inData;
	if (m_serverRepond.ParseFromString(outData))
	{
		m_msg.rv = m_serverRepond.rv();
		strcpy(m_msg.clientId, m_serverRepond.clientid().c_str());
		strcpy(m_msg.serverId, m_serverRepond.serverid().c_str());
		strcpy(m_msg.r2, m_serverRepond.r2().c_str());
		m_msg.seckeyid = m_serverRepond.seckeyid();
	}
	return &m_msg;
}