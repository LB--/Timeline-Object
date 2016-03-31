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
	//
}

void Extension::SetValue(int position, int index, TCHAR const *name, float value)
{
	//
}

void Extension::SetString(int position, int index, TCHAR const *name, TCHAR const *value)
{
	//
}

void Extension::CopyEvent(int source_position, int source_index, int target_position, int target_index)
{
	//
}

void Extension::MoveEvent(int source_position, int source_index, int target_position, int target_index)
{
	//
}

void Extension::RemoveEvent(int position, int index)
{
	//
}

void Extension::ClearPosition(int position)
{
	//
}

void Extension::RemoveValue(int position, int index, TCHAR const *name)
{
	//
}

void Extension::RemoveString(int position, int index, TCHAR const *name)
{
	//
}

void Extension::CopyPosition(int source_position, int target_position, int replace)
{
	//
}

void Extension::MovePosition(int source_position, int target_position, int replace)
{
	//
}

void Extension::SetTime(int position)
{
	//
}

void Extension::SetTimeSpeed(int speed)
{
	//
}

void Extension::SetEventTriggering(int enabled)
{
	//
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
	//
}
