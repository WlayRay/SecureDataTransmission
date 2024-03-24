#include "seckeymodel.h"
#include "db.h"
#include <string.h>
#include <time.h>
using namespace std;

int SecKeyModel::getKeyID()
{
    std::string sql = "select ikeysn from KEYSN";
    int n;
    MySQL mysql;
    if (mysql.connect())
    {
        MYSQL_RES *res = mysql.query(sql);
        if (res != nullptr)
        {
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                n = atoi(row[0]);
                mysql_free_result(res);
                return n;
            }
        }
    }
    return -101;
}

bool SecKeyModel::updateKeyID(int keyID)
{
    std::string sql = "UPDATE KEYSN SET ikeysn = ";
    sql += std::to_string(keyID);

    MySQL mysql;
    if (mysql.connect())
    {
        return mysql.update(sql);
    }
    return false;
}

bool SecKeyModel::writeSecKey(NodeSHMInfo *pNode)
{
    // 组织待插入的sql语句
    char sql[2048];
    snprintf(sql, sizeof(sql), "INSERT INTO SECKEYINFO(clientid, serverid, keyid, createtime, state, seckey) \
    VALUES ('%s', '%s', %d, NOW(), %d, '%s')",
             pNode->clientID, pNode->serverID, pNode->seckeyID,
             1, pNode->seckey);
    cout << "insert sql: " << sql << endl;
    MySQL mysql;
    bool flag;
    if (mysql.connect())
    {
        flag = mysql.update(sql);
    }
    return flag;
}

string SecKeyModel::getCurTime()
{
    time_t timep;
    time(&timep);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&timep));
    return std::string(tmp);
}