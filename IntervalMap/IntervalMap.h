#pragma once

#include <map>
#include <limits>

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
			V                                 begin_value;
			V                                 end_value;
			V                                 begin_previous_value;
			V                                 end_next_value;
			typename std::map<K, V>::iterator it_begin_lower;
			typename std::map<K, V>::iterator it_begin_upper;
			typename std::map<K, V>::iterator it_end_lower;
			typename std::map<K, V>::iterator it_end_upper;
			typename std::map<K, V>::iterator begin;
			typename std::map<K, V>::iterator end;


			if (key_begin >= key_end)
			{
				return;
			}

			it_begin_lower = _Map.lower_bound(key_begin);

			it_begin_upper = _Map.upper_bound(key_begin);
			it_begin_upper--;
			begin_value = it_begin_upper->second;

			if (it_begin_lower == _Map.end())
			{
				if (begin_value != value)
				{
					_Map[key_begin] = value;
					_Map[key_end]   = begin_value;
				}

				return;
			}

			it_end_lower = _Map.lower_bound(key_end);

			if (it_end_lower != _Map.begin())
			{
				it_end_lower--;
			}

			end_value = it_end_lower->second;

			if ((begin_value == value) && (end_value == value))
			{
				it_begin_upper++;
				it_end_lower++;
				_Map.erase(it_begin_upper, it_end_lower);

				return;
			}

			if (it_begin_lower != _Map.begin())
			{
				it_begin_lower--;
			}

			begin_previous_value = it_begin_lower->second;

			it_end_upper =  _Map.upper_bound(key_end);
			it_end_upper--;
			end_next_value = it_end_upper->second;

			if ((begin_previous_value == value) && (end_next_value == value))
			{
				it_begin_lower++;
				it_end_upper++;
				_Map.erase(it_begin_lower, it_end_upper);

				return;
			}

			if (!((begin_value == value) || (begin_previous_value == value)))
			{
				_Map[key_begin] = value;
			}

			if (end_value == end_next_value)
			{
				_Map[key_end] = end_value;
			}

			it_begin_upper    = _Map.upper_bound(key_begin);
			it_end_lower      = _Map.lower_bound(key_end);

			it_begin_lower = _Map.lower_bound(key_begin);

			if (it_begin_lower != _Map.begin())
			{
				it_begin_lower--;
			}

			begin_previous_value = it_begin_lower->second;

			it_end_upper = _Map.upper_bound(key_end);
			it_end_upper--;
			end_next_value = it_end_upper->second;

			if (begin_previous_value == value)
			{
				it_begin_lower++;
				begin = it_begin_lower;
			}
			else
			{
				begin = it_begin_upper;
			}

			if (end_next_value == value)
			{
				it_end_upper++;
				end = it_end_upper;
			}
			else
			{
				end = it_end_lower;
			}

			_Map.erase(begin, end);
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

