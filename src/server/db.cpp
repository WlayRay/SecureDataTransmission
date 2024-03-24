#include "db.h"
#include <iostream>

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "secure_transmission";

MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}

MySQL::~MySQL()
{
    if (_conn != nullptr)
    {
        mysql_close(_conn);
    }
}

// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        // 设置C/C++字符编码（默认为ASCII编码）
        mysql_query(_conn, "set name utf8mb4");
        std::cout << " 连接数据库成功！ ";
        return true;
    }
    else
    {
        std::cout << " 连接数据库失败！ ";
        return false;
    }
}

bool MySQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << mysql_error(_conn) << " 更新失败！";
        return false;
    }
    std::cout << "更新成功！";
    return true;
}

MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        std::cout << __FILE__ << ":" << __LINE__ << ":" << sql << "查询失败！";
        return nullptr;
    }
    MYSQL_RES *result = mysql_store_result(_conn); // 使用mysql_store_result()来获取查询结果集，如果查询结果集非常大，这个函数会返回nullptr。
    if (result == nullptr)
    {
        std::cout << "Query result is too large to handle!";
        return nullptr; // 如果查询结果太大，返回nullptr。
    }
    else
    { // 正常情况返回结果集。
        return result;
    }
}

MYSQL *MySQL::getConnection()
{
    return _conn;
}