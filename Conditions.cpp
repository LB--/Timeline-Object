/* Conditions.cpp
 * This is where you should define the
 * behavior of your conditions. Make sure
 * the parameters and return types match those
 * in the JSON exactly! Double check Extension.h
 * as well.
 */

#include "Common.h"

bool Extension::OnEvent(TCHAR const *type)
{
	return trigger_events && current_event_type == type;
}

bool Extension::ValueExists(int position, int index, TCHAR const *name)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		if(index < pos->second.size())
		{
			auto const &values = pos->second[index].values;
			return values.find(name) != std::cend(values);
		}
	}
	return false;
}

bool Extension::StringExists(int position, int index, TCHAR const *name)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		if(index < pos->second.size())
		{
			auto const &strings = pos->second[index].strings;
			return strings.find(name) != std::cend(strings);
		}
	}
	return false;
}

bool Extension::OnError()
{
	return true;
}

bool Extension::PositionExists(int position)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		if(pos->second.empty()) //shouldn't happen
		{
			timeline.erase(pos); //oops
			return true;
		}
		return false;
	}
	return true;
}

bool Extension::EventExists(int position, TCHAR const *type)
{
	auto const pos = std::as_const(timeline).find(position);
	if(pos != std::cend(timeline))
	{
		for(auto const &e : pos->second)
		{
			if(e.type == type)
			{
				return true;
			}
		}
	}
	return false;
}

bool Extension::OnTick()
{
	return trigger_positions;
}

