#ifndef SECKEYMODEL_H
#define SECKEYMODEL_H

#include "SecKeyShm.h"

class SecKeyModel
{
public:
    int getKeyID();
    bool updateKeyID(int keyID);
    bool writeSecKey(NodeSHMInfo *pNode);
    std::string getCurTime();
};

#endif