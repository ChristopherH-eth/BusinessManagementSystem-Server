#include "bmspch.h"

#include "database.h"
#include "Log/Log.h"

/**
 * @file Database.cpp
 * @author 0xChristopher
 * @brief Source file for the Database class
 */

namespace BMS
{

	/**
	 * @brief Database contrsuctors and destructors
	 */
	Database::Database(std::string& db, std::string& user, std::string& pass)
		: m_db(db), m_user(user), m_pass(pass)
	{
		this->driver = sql::mysql::get_mysql_driver_instance();
		this->con = driver->connect(m_db, m_user, m_pass);
	}

	Database::Database()
	{
		this->driver = sql::mysql::get_mysql_driver_instance();
		this->con = driver->connect(this->m_db, this->m_user, this->m_pass);
	}

	Database::~Database()
	{
		DisconnectDB(this->con);
	}

	/**
	 * @brief The ConnectDB() function returns the current database connection; if there is no
	 * connection, it attempts to reconnect
	 */
	sql::Connection* Database::ConnectDB()
	{
		if (!this->con->isValid())
			this->con = driver->connect(this->m_db, this->m_user, this->m_pass);

		return this->con;
	}

	/**
	 * @brief The DisconnectDB() function disconnects the server instance from the database
	 */
	bool Database::DisconnectDB(sql::Connection*& con)
	{
		if (this->con->isValid())
		{
			delete con;

			BMS_WARN("Database connection closed");

			return true;
		}
		else
			return false;
	}

}