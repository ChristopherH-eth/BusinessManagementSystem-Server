#pragma once

#include <time.h>
#include "../Core.h"

/**
 * @file TimeClock.h
 * @author 0xChristopher
 */

namespace BMS
{

	class BMS_API TimeClock
	{

		bool ClockIn();

		bool ClockOut();

	};

}