#pragma once
#include <winsock.h>

#include <mysql.h>

#pragma comment(lib,"libmySQL.lib")//���������Ҳ�����ڹ�������������

#pragma comment(lib,"mysqlclient.lib")
static int connectsql(MYSQL* p) {
	mysql_init(p);
	//mysql_options(p, MYSQL_SET_CHARSET_NAME, "gbk");
	mysql_options(p, MYSQL_SET_CHARSET_NAME, "gbk");
	/*if (!mysql_real_connect(p, "dbwork.mysql.polardb.rds.aliyuncs.com", "dbwork_admin",
		"123456lC", "dbwork", 3306, NULL, 0))
	{*/
	if (!mysql_real_connect(p, "localhost", "root",
		"123456", "booksystem", 3306, NULL, 0))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}