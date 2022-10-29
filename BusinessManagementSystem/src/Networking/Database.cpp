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
		try
		{
			// Setup MySQL driver and connection to database
			this->driver = sql::mysql::get_mysql_driver_instance();
			this->con = driver->connect(m_db, m_user, m_pass);
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
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
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
	}

	Database::~Database()
	{
		try
		{
			DisconnectDB(this->con);
		}
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
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
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
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
		catch (sql::SQLException& e) {
			BMS_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
			BMS_FILE_ERROR("# ERR: SQLException in {0} ({1}) on line {2}",
				__FILE__, __FUNCTION__, __LINE__);
			BMS_FILE_ERROR("# ERR: {0} (MySQL error code: {1}, SQLState: {2} )",
				e.what(), e.getErrorCode(), e.getSQLState());
		}
	}

}