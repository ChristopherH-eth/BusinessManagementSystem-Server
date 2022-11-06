#include "bmspch.h"

#include "Database.h"
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
		try
		{
			// Setup MySQL driver and connection to database
			this->driver = sql::mysql::get_mysql_driver_instance();
			this->con = driver->connect(m_db, m_user, m_pass);
		}
		catch (std::string& error) {
			BMS_ERROR(error);
		}
	}

	Database::Database()
	{
		try
		{
			// Setup MySQL driver and connection to database
			this->driver = sql::mysql::get_mysql_driver_instance();
			this->con = driver->connect(this->m_db, this->m_user, this->m_pass);
		}
		catch (std::string& error) {
			BMS_ERROR(error);
		}
	}

	Database::~Database()
	{
		
	}

	/**
	 * @brief The ConnectDB() function returns the current database connection; if there is no
	 * connection, it attempts to reconnect
	 */
	sql::Connection* Database::ConnectDB()
	{
		try
		{
			// Check our connection
			if (!this->con->isValid())
				// Try to connect to database
				this->con = driver->connect(this->m_db, this->m_user, this->m_pass);

			// Return valid connection or log error
			if (this->con->isValid())
				return this->con;
			else
				BMS_ERROR("Could not establish connection to database");
		}
		catch (std::string& error) {
			BMS_ERROR(error);
		}
	}

	/**
	 * @brief The DisconnectDB() function disconnects the server instance from the database
	 */
	bool Database::DisconnectDB(sql::Connection*& con)
	{
		try
		{
			// Clean up connection if we still have one
			if (this->con->isValid())
			{
				delete con;

				BMS_WARN("Database connection closed");

				return true;
			}
			else
				return false;
		}
		catch (std::string& error) {
			BMS_ERROR(error);
		}
	}

}