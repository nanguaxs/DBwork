#pragma once
#include <winsock.h>

#include <mysql.h>

#pragma comment(lib,"libmySQL.lib")//附加依赖项，也可以在工程属性中设置

#pragma comment(lib,"mysqlclient.lib")
static int connectsql(MYSQL* p) {
	mysql_init(p);
	mysql_options(p, MYSQL_SET_CHARSET_NAME, "gbk");

	if (!mysql_real_connect(p, "localhost", "root",
		"123456", "docmanagement", 3306, NULL, 0))
	{
		
		return 0;
	}
	else//连接成功则继续访问数据库，之后的相关操作代码基本是放在这里面的
	{
		return 1;
	}
}