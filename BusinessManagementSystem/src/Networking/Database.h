#pragma once

#include <mysql/jdbc.h>

#include "../Core.h"

/**
 * @file Database.h
 * @author 0xChristopher
 * @brief 
 */

namespace BMS
{

	class BMS_API Database
	{

	private:
		std::string m_db = "tcp://127.0.0.1:3306";		// MySQL database address
		std::string m_user = "ChristopherTest";			// Username
		std::string m_pass = "Test123!";				// Password
		sql::mysql::MySQL_Driver* driver = nullptr;		// MySQL database driver
		sql::Connection* con = nullptr;					// MySQL database connection

	public:
		/**
		 * @brief Database constructors and destructor
		 */
		Database(std::string& db, std::string& user, std::string& pass);

		Database();

		~Database();

		/**
		 * @brief The ConnectDB() function returns the current database connection; if there is no
		 * connection, it attempts to reconnect
		 * @return Returns the current database connection
		 */
		sql::Connection* ConnectDB();

		/**
		 * @brief The DisconnectDB() function disconnects the server instance from the database
		 * @param con The current database connection
		 * @return Returns true if there is no longer a database connection 
		 */
		bool DisconnectDB(sql::Connection*& con);

	};

}