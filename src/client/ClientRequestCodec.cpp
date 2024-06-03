#include "ClientRequestCodec.h"

// 编码对象的构造函数
RequestCodec::RequestCodec()
{
}

RequestCodec::RequestCodec(RequestMsg *msg)
{
	memcpy(&m_msg, msg, sizeof(RequestMsg));
}

RequestCodec::~RequestCodec()
{
}

int RequestCodec::msgEncode(char **outData, int &len)
{
	m_clientRequest.set_cmdtype(m_msg.cmdType);
	m_clientRequest.set_clientid(m_msg.clientId);
	m_clientRequest.set_authcode(m_msg.authCode);
	m_clientRequest.set_serverid(m_msg.serverId);
	m_clientRequest.set_r1(m_msg.r1);
	std::string serializedData;
	if (!m_clientRequest.SerializeToString(&serializedData))
	{
		std::cerr << "序列化数据失败！" << std::endl;
		return -1;
	}

	std::cout << std::endl
			  << "----------------------------------------------------------------" << std::endl << std::endl;
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
	std::string outData = inData;
	if (m_clientRequest.ParseFromString(outData))
	{
		m_msg.cmdType = m_clientRequest.cmdtype();
		strcpy(m_msg.clientId, m_clientRequest.clientid().c_str());
		strcpy(m_msg.authCode, m_clientRequest.authcode().c_str());
		strcpy(m_msg.serverId, m_clientRequest.serverid().c_str());
		strcpy(m_msg.r1, m_clientRequest.r1().c_str());
	}
	return &m_msg;
}
