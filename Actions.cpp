/* Actions.cpp
 * This is where you should define the
 * behavior of your actions. Make sure
 * the parameters match those in the JSON
 * exactly! Double check Extension.h
 * as well.
 */

#include "Common.h"

void Extension::AddEvent(int position, TCHAR const *type)
{
	timeline[position].emplace_back(type);
}

void Extension::SetValue(int position, int index, TCHAR const *name, float value)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		if(index < pos->second.size())
		{
			pos->second[index].values.emplace(name, value);
		}
	}
}

void Extension::SetString(int position, int index, TCHAR const *name, TCHAR const *value)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		if(index < pos->second.size())
		{
			pos->second[index].strings.emplace(name, value);
		}
	}
}

void Extension::CopyEvent(int source_position, int source_index, int target_position, int target_index)
{
	auto const &source_pos = timeline.find(source_position);
	if(source_pos != std::end(timeline))
	{
		auto const &source_events = source_pos->second;
		if(source_index < source_events.size() && !source_events.empty())
		{
			if(source_index < 0)
			{
				insert_event(target_position, target_index, source_events.back());
			}
			else
			{
				insert_event(target_position, target_index, source_events[source_index]);
			}
		}
	}
}

void Extension::MoveEvent(int source_position, int source_index, int target_position, int target_index)
{
	auto &source_pos = timeline.find(source_position);
	if(source_pos != std::end(timeline))
	{
		auto &source_events = source_pos->second;
		if(source_index < source_events.size() && !source_events.empty())
		{
			if(source_index < 0)
			{
				insert_event(target_position, target_index, std::move(source_events.back()));
				source_events.pop_back();
			}
			else
			{
				insert_event(target_position, target_index, std::move(source_events[source_index]));
				source_events.erase(std::begin(source_events)+source_index);
			}
		}
	}
}

void Extension::RemoveEvent(int position, int index)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		auto &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			events.erase(std::begin(events)+index);
		}
	}
}

void Extension::ClearPosition(int position)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		timeline.erase(pos);
	}
}

void Extension::RemoveValue(int position, int index, TCHAR const *name)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		auto &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			events[index].values.erase(name);
		}
	}
}

void Extension::RemoveString(int position, int index, TCHAR const *name)
{
	auto &pos = timeline.find(position);
	if(pos != std::end(timeline))
	{
		auto &events = pos->second;
		if(index < events.size() && index >= 0)
		{
			events[index].strings.erase(name);
		}
	}
}

void Extension::CopyPosition(int source_position, int target_position, int replace)
{
	auto const &source_pos = timeline.find(source_position);
	if(source_pos != std::end(timeline))
	{
		auto const &source_events = source_pos->second;
		auto &target_pos = timeline.find(target_position);
		if(replace || target_pos == std::end(timeline))
		{
			timeline.emplace(target_position, source_events);
		}
		else
		{
			auto &target_events = target_pos->second;
			target_events.reserve(target_events.size() + source_events.size());
			for(auto const &e : source_events)
			{
				target_events.emplace_back(e);
			}
		}
	}
}

void Extension::MovePosition(int source_position, int target_position, int replace)
{
	auto &source_pos = timeline.find(source_position);
	if(source_pos != std::end(timeline))
	{
		auto &source_events = source_pos->second;
		auto &target_pos = timeline.find(target_position);
		if(replace || target_pos == std::end(timeline))
		{
			timeline.emplace(target_position, std::move(source_events));
		}
		else
		{
			auto &target_events = target_pos->second;
			target_events.reserve(target_events.size() + source_events.size());
			for(auto &e : source_events)
			{
				target_events.emplace_back(std::move(e));
			}
		}
		timeline.erase(source_pos);
	}
}

void Extension::SetTime(int position)
{
	time = position;
}

void Extension::SetTimeSpeed(int speed)
{
	this->speed = speed;
}

void Extension::SetEventTriggering(int enabled)
{
	trigger_events = (enabled? true : false);
}

void Extension::LoadTimelineString(TCHAR const *timeline, int merge)
{
	//
}

void Extension::SaveTimelineFile(TCHAR const *filename)
{
	//
}

void Extension::LoadTimelineFile(TCHAR const *filename, int merge)
{
	//
}

void Extension::MoveTime(int position)
{
	//
}

void Extension::SetPositionTriggering(int enabled)
{
	trigger_positions = (enabled? true : false);
}
