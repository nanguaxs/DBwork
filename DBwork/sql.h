#pragma once
#include <winsock.h>

#include <mysql.h>

#pragma comment(lib,"libmySQL.lib")//���������Ҳ�����ڹ�������������

#pragma comment(lib,"mysqlclient.lib")
static int connectsql(MYSQL* p) {
	mysql_init(p);
	mysql_options(p, MYSQL_SET_CHARSET_NAME, "gbk");

	if (!mysql_real_connect(p, "localhost", "root",
		"123456", "docmanagement", 3306, NULL, 0))
	{
		
		return 0;
	}
	else//���ӳɹ�������������ݿ⣬֮�����ز�����������Ƿ����������
	{
		return 1;
	}
}