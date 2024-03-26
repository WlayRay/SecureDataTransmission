#ifndef SECKEYMODEL_H
#define SECKEYMODEL_H

#include "ServerSecKeyShm.h"

class SecKeyModel
{
public:
    // 获取秘钥ID
    int getKeyID();

    // 更新秘钥ID给下个一个存储的秘钥使用
    bool updateKeyID(int keyID);

    // 写入秘钥以及秘钥相关信息
    bool writeSecKey(NodeSHMInfo *pNode);

    std::string getCurTime();
};

#endif