#include "ClientRespondCodec.h"
#include <iostream>
using namespace std;

RespondCodec::RespondCodec()
{
}

RespondCodec::RespondCodec(RespondMsg *msg)
{
	memcpy(&m_msg, msg, sizeof(RespondMsg));
}

RespondCodec::~RespondCodec()
{
}

int RespondCodec::msgEncode(char **outData, int &len)
{
	m_clientRespond.set_rv(m_msg.rv);
	m_clientRespond.set_clientid(m_msg.clientId);
	m_clientRespond.set_serverid(m_msg.serverId);
	m_clientRespond.set_r2(m_msg.r2);
	m_clientRespond.set_seckeyid(m_msg.seckeyid);

	string serializedData;
	if (!m_clientRespond.SerializeToString(&serializedData))
	{
		cerr << "序列化数据失败！" << endl;
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

	// std::cout << std::endl
	// 		  << "----------------------------------------------------------------" << std::endl
	// 		  << std::endl;
	// std::cout << serializedData << std::endl
	// 		  << std::endl;
	// std::cout << "----------------------------------------------------------------" << std::endl;

	// 将unique_ptr的所有权转移给调用者
	*outData = buffer.release();
	return 0;
}

void *RespondCodec::msgDecode(char *inData, int inLen)
{
	string outData = inData;
	if (m_clientRespond.ParseFromString(outData))
	{
		m_msg.rv = m_clientRespond.rv();
		strcpy(m_msg.clientId, m_clientRespond.clientid().c_str());
		strcpy(m_msg.serverId, m_clientRespond.serverid().c_str());
		strcpy(m_msg.r2, m_clientRespond.r2().c_str());
		m_msg.seckeyid = m_clientRespond.seckeyid();
	}
	return &m_msg;
}
