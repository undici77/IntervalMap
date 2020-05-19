#include "stdafx.h"
#include <iostream>
#include <time.h>

#include "Profiler.h"
#include "IntervalMap.h"

/*****************************************************************************/

#define PROFILER            1

/*****************************************************************************/

#define ASSERT(v)           \
	do       		        \
	{				        \
		if (!(v))	        \
			__debugbreak();	\
	} while(0)

/*****************************************************************************/

typedef uint8_t KEY_TYPE;
typedef uint8_t VALUE_TYPE;

/*****************************************************************************/

int main()
{
	KEY_TYPE key_interval;

	PROFILER_SETUP;
	PROFILER_INIT;

	key_interval = 0;
	while (true)
	{
		VALUE_TYPE test_reference[std::numeric_limits<KEY_TYPE>::max() + 1];
		IntervalMap<KEY_TYPE, VALUE_TYPE> interval_map('0');

		srand((unsigned int)time(NULL));

		key_interval++;
		if (key_interval == 0)
		{
			PROFILER_TRIG("End Cycle");
			PROFILER_INIT;
			key_interval = 1;
		}

		memset(test_reference, '0', sizeof(test_reference));

		//std::cout << "Interval: " << (size_t)key_interval << std::endl;

		for (size_t test_id = 0; test_id < ((size_t)std::numeric_limits<KEY_TYPE>::max() * 32); test_id++)
		{
			KEY_TYPE                                 begin_key;
			KEY_TYPE                                 end_key;
			VALUE_TYPE                               value;
			std::map<KEY_TYPE, VALUE_TYPE>::iterator it;
			std::map<KEY_TYPE, VALUE_TYPE>           test_map;

			do
			{
				value = rand();
				begin_key = rand() % (std::numeric_limits<KEY_TYPE>::max() + 1);
				end_key = (1 + begin_key + (rand() % key_interval));
			}
			while (begin_key >= end_key);

			memset(test_reference + begin_key, value, (end_key - begin_key));
			interval_map.Assign(begin_key, end_key, value);

			test_map = interval_map.GetMap(); 
			it = test_map.begin();
			value = it->second;
			it++;

			while (it != test_map.end())
			{
				ASSERT(value != it->second);

				value = it->second;

				it++;
			}

			for (size_t id = 0; id < ((size_t)std::numeric_limits<KEY_TYPE>::max() + 1); id++)
			{
				ASSERT(interval_map[(KEY_TYPE)id] == test_reference[id]);
			}
		}
	}
}

