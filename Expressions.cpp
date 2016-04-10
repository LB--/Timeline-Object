/* Expressions.cpp
 * This is where you should define the
 * behavior of your expressions. Make sure
 * the parameters and return types match those
 * in the JSON exactly! Double check Extension.h
 * as well.
 */

#include "Common.h"

#include <iterator>

int Extension::Time()
{
	return time;
}

int Extension::TimeVelocity()
{
	return velocity;
}

TCHAR const *Extension::CurrentEventType()
{
	return Runtime.CopyString(current_event_type.c_str());
}

int Extension::CurrentEventIndex()
{
	return current_event_index;
}

int Extension::NumEventsAt(int position)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		return pos->second.size();
	}
	return 0;
}

TCHAR const *Extension::EventTypeAt(int position, int index)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			return Runtime.CopyString(events[index].type.c_str());
		}
	}
	return _T("");
}

float Extension::Value(int position, int index, TCHAR const *name)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			auto const &values = events[index].values;
			auto const val = values.find(name);
			if(val != std::cend(values))
			{
				return val->second;
			}
		}
	}
	return 0.0f;
}

TCHAR const *Extension::String(int position, int index, TCHAR const *name)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			auto const &strings = events[index].strings;
			auto const str = strings.find(name);
			if(str != std::cend(strings))
			{
				return Runtime.CopyString(str->second.c_str());
			}
		}
	}
	return _T("");
}

TCHAR const *Extension::Timeline()
{
	stdtstring result;
	for(auto pos_it = std::cbegin(timeline); pos_it != std::cend(timeline); ++pos_it)
	{
		if(pos_it != std::cbegin(timeline))
		{
			result += '|';
		}
		result += std::to_wstring(pos_it->first);
		result += ':';
		auto const &events = pos_it->second;
		for(auto const &e : events)
		{
			result += escape(e.type);
			result += '{';
			for(auto val_it = std::cbegin(e.values); val_it != std::cend(e.values); ++val_it)
			{
				if(val_it != std::cbegin(e.values))
				{
					result += ',';
				}
				result += escape(val_it->first);
				result += '=';
				result += std::to_wstring(val_it->second);
			}
			result += ';';
			for(auto str_it = std::cbegin(e.strings); str_it != std::cend(e.strings); ++str_it)
			{
				if(str_it != std::cbegin(e.strings))
				{
					result += ',';
				}
				result += escape(str_it->first);
				result += '=';
				result += escape(str_it->second);
			}
			result += '}';
		}
	}
	return Runtime.CopyString(result.c_str());
}

TCHAR const *Extension::ErrorMessage()
{
	return Runtime.CopyString(error_msg.c_str());
}

int Extension::NumValuesAt(int position, int index)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			return events[index].values.size();
		}
	}
	return 0;
}

int Extension::NumStringsAt(int position, int index)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			return events[index].strings.size();
		}
	}
	return 0;
}

int Extension::ValueById(int position, int index, int id)
{
	auto const &pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			auto const &values = events[index].values;
			if(id < values.size() && id >= 0)
			{
				auto it = std::cbegin(values);
				std::advance(it, id);
				return it->second;
			}
		}
	}
	return 0.0f;
}

TCHAR const *Extension::StringById(int position, int index, int id)
{
	auto const &pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		auto const &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			auto const &strings = events[index].strings;
			if(id < strings.size() && id >= 0)
			{
				auto it = std::cbegin(strings);
				std::advance(it, id);
				return Runtime.CopyString(it->second.c_str());
			}
		}
	}
	return _T("");
}

