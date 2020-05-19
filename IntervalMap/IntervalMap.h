#pragma once

#include <map>
#include <limits>

#define ENABLE_OPTIMIZATION  1

template<typename K, typename V>
class IntervalMap
{
	// Function
	public:
		IntervalMap(V const &value)
		{
			_Map[std::numeric_limits<K>::lowest()] = value;
		}

		void Assign(K const &key_begin, K const &key_end, V const &value)
		{
			V begin_value;
			V end_value;
			V begin_previous_value;
			V end_next_value;
			typename std::map<K, V>::iterator it_begin_lower;
			typename std::map<K, V>::iterator it_begin_upper;
			typename std::map<K, V>::iterator it_end_lower;
			typename std::map<K, V>::iterator it_end_upper;
			typename std::map<K, V>::iterator it_begin;
			typename std::map<K, V>::iterator it_end;

			// Validating keys
			if (key_begin >= key_end)
			{
				return;
			}

			// Getting begin key top reference
			it_begin_lower = _Map.lower_bound(key_begin);

			// Getting begin key value
			it_begin_upper = _Map.upper_bound(key_begin);
			it_begin_upper--;
			begin_value = it_begin_upper->second;

			// If begin key top reference is end, add new interval at the end of the map
			if (it_begin_lower == _Map.end())
			{
				// Checking if value already exist
				if (begin_value != value)
				{
					_Map[key_begin] = value;
					_Map[key_end]   = begin_value;
				}

				return;
			}

			// Getting end key value
			it_end_lower = _Map.lower_bound(key_end);
			if (it_end_lower != _Map.begin())
			{
				it_end_lower--;
			}

			end_value = it_end_lower->second;
			#if (ENABLE_OPTIMIZATION == 1)
			// If begin value and end value are equal to new interval value
			// simply expand current interval deleting intervals in the middle
			if ((begin_value == value) && (end_value == value))
			{
				it_begin_upper++;
				it_end_lower++;
				_Map.erase(it_begin_upper, it_end_lower);

				return;
			}
			#endif

			// Getting previous begin key value
			if (it_begin_lower != _Map.begin())
			{
				it_begin_lower--;
			}
			begin_previous_value = it_begin_lower->second;

			// Getting next end key value
			it_end_upper = _Map.upper_bound(key_end);
			it_end_upper--;
			end_next_value = it_end_upper->second;

			#if (ENABLE_OPTIMIZATION == 1)
			// If previous begin value and next end value are equal to new interval value
			// simply expand current interval deleting intervals in the middle
			if ((begin_previous_value == value) && (end_next_value == value))
			{
				it_begin_lower++;
				it_end_upper++;
				_Map.erase(it_begin_lower, it_end_upper);

				return;
			}
			#endif

			// New interval involvs more than on interval, so add nel key if necessary
			// and delete intervals in the middle
			if (!((begin_value == value) || (begin_previous_value == value)))
			{
				_Map[key_begin] = value;
			}

			if (end_value == end_next_value)
			{
				_Map[key_end] = end_value;
			}

			// Getting new boundaries
			it_begin_upper = _Map.upper_bound(key_begin);
			it_end_lower   = _Map.lower_bound(key_end);
			it_begin_lower = _Map.lower_bound(key_begin);

			if (it_begin_lower != _Map.begin())
			{
				it_begin_lower--;
			}
			begin_previous_value = it_begin_lower->second;

			it_end_upper = _Map.upper_bound(key_end);
			it_end_upper--;
			end_next_value = it_end_upper->second;

			// If previous begin key is equal to inserted value, delete also previous key
			if (begin_previous_value == value)
			{
				it_begin_lower++;
				it_begin = it_begin_lower;
			}
			else
			{
				it_begin = it_begin_upper;
			}

			// If next end key is equal to inserted value, delete also next key
			if (end_next_value == value)
			{
				it_end_upper++;
				it_end = it_end_upper;
			}
			else
			{
				it_end = it_end_lower;
			}

			_Map.erase(it_begin, it_end);
		}

		V const &operator[](K const &key)
		{
			typename std::map<K, V>::iterator it;

			it = _Map.upper_bound(key);
			it--;

			return (it->second);
		}

		std::map<K, V> GetMap(void) 
		{
			return(_Map);
		}

	protected:

	private:

	// Variables
	public:

	protected:

	private:
		std::map<K, V> _Map;
};

