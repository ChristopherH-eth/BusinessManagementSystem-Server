#include <mysql/jdbc.h>

#include "database.h"

/**
 * @file Database.cpp
 * @author 0xChristopher
 * @brief Source file for the Database class
 */

Database::Database()
{

}

Database::~Database()
{

}

void Database::ConnectDB(bool& db)
{
	sql::mysql::MySQL_Driver *driver;
	sql::Connection *con;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://127.0.0.1:3306", "ChristopherTest", "Test123!");

	if (con->isValid())
	{
		delete con;
		db = true;
	}
	else
	{
		delete con;
		db = false;
	}
}