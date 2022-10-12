#pragma once

#include <string>
#include "../Core.h"

/**
 * @file Employee.h
 * @author 0xChristopher
 * @brief 
 */

namespace BMS 
{

	class BMS_API Employee 
	{

	private:
		std::string m_firstName, m_lastName, m_birthDate, m_position;
		int m_age, m_id;
		float m_wage;

	public:
		Employee(std::string& firstName, std::string& lastName, std::string& birthDate, std::string& position,
			int age, int id)
			: m_firstName(firstName), m_lastName(lastName), m_birthDate(birthDate), m_position(position),
			m_age(age), m_id(id) 
		{

		}

		~Employee() 
		{

		}

		void AddEmployee(std::string& firstName, std::string& lastName, std::string& birthDate,
			std::string& position, int age, int id);

		void RemoveEmployee(int id);

	};

}