/* Extension.h
 * This is where you define your extension
 * class. Runtime variables and function
 * declarations go in here; A/C/E function
 * definitions go in their respective .cpp
 * files, other function definitions go in
 * Extension.cpp. This header is included
 * at the bottom of Common.h, so you have
 * access to everything included by it.
 */

#include <map>
#include <vector>

class Extension final
{
public:
	/* rd
	 * This is a pointer to the classic
	 * RunData structure. Some things still
	 * have to be stored there for MMF2's
	 * sake, so you need to have acces to
	 * that data. You should not modify
	 * the rundata structure, however,
	 * as it is global to all extensions.
	 */
	RD *rd;

	/* rh
	 * This is a pointer to the RunHeader
	 * structure, which contains some
	 * application information.
	 */
	RunHeader *rh;

	/* Runtime
	 * This is EDIF's compendium of useful
	 * functions for every day life as an
	 * extension. You can trigger immediate
	 * events, read and write global data,
	 * etc. See the EDIF wiki for more
	 * information.
	 */
	Edif::Runtime Runtime;

	/* MinimumBuild
	 * Always set this to the latest build
	 * of MMF2 that has been released, unless
	 * you need to set it higher for a beta
	 * version of MMF2 to get access to some
	 * new SDK feature.
	 */
	static const int MinimumBuild = 257;

	/* Version
	 * This is the version of your extension
	 * that is stored in the editdata. You should
	 * only change this when your editdata structure
	 * changes, not just when you have a new version
	 * of your extension with new features.
	 */
	static const int Version = 1;

	/* OEFLAGS, OEPREFS
	 * These are settings for your extension
	 * that tell MMF2 how to treat your extension
	 * and what behaviors and responsibilities
	 * to add. Check the MMF2SDK Help file for
	 * more detailed information on the flags you
	 * can set and what they implicate.
	 */
	static const int OEFLAGS = OEFLAG_VALUES|OEFLAG_RUNBEFOREFADEIN|OEFLAG_NEVERKILL;
	static const int OEPREFS = 0;

	/* WindowProcPriority
	 * If your extension creates a Window
	 * and implements the WindowProc function,
	 * this is the priority for that stuff.
	 */
	static const int WindowProcPriority = 100;

	Extension(RD *rd, SerializedED *SED, createObjectInfo *COB); //defined & documented in Extension.cpp
	~Extension();                                                //defined & documented in Extension.cpp


	/* Add any data you want to store in your
	 * extension to this class (eg. what you'd
	 * normally store in the rundata). Unlike
	 * other SDKs, you can store real C++
	 * objects with constructors and destructors,
	 * without having to call them manually or
	 * store a pointer.
	 */

	stdtstring error_msg;
	std::int32_t time, velocity;
	bool trigger_events, trigger_positions;
	stdtstring current_event_type;
	std::int32_t current_event_index;

	struct Event final
	{
		stdtstring type;
		std::map<stdtstring, float> values;
		std::map<stdtstring, stdtstring> strings;

		Event() = default;
		Event(stdtstring const &type)
		: type{type}
		{
		}
	};
	using Position_t = std::vector<Event>;
	using Timeline_t = std::map<std::int32_t, Position_t>;
	Timeline_t timeline;


	void insert_event(int position, int index, Event e)
	{
		auto const pos = timeline.find(position);
		if(pos == std::end(timeline))
		{
			timeline.emplace(position, Position_t{std::move(e)});
		}
		else
		{
			auto &events = pos->second;
			if(index < 0 || static_cast<std::size_t>(index) >= events.size())
			{
				events.emplace_back(std::move(e));
			}
			else
			{
				events.emplace(std::begin(events)+index, std::move(e));
			}
		}
	}

	static stdtstring escape(stdtstring const &s)
	{
		//TODO
		return s;
	}
	static stdtstring unescape(stdtstring const &s)
	{
		//TODO
		return s;
	}

	/* Add your actions, conditions, and expressions
	 * as real class member functions here. The arguments
	 * (and return types for expressions/conditions)
	 * must match EXACTLY what you defined in the JSON.
	 * As a handy tip, all parameters will be either
	 * a pointer, an int, or a float (each only 4 bytes)
	 * and the same applies to return types. Remember to
	 * link the actions, conditions and expressions to their
	 * numeric IDs in the class constructor in Extension.cpp.
	 */

	//Actions - Defined in Actions.cpp
	void AddEvent(int position, TCHAR const *type);
	void SetValue(int position, int index, TCHAR const *name, float value);
	void SetString(int position, int index, TCHAR const *name, TCHAR const *value);
	void CopyEvent(int source_position, int source_index, int target_position, int target_index);
	void MoveEvent(int source_position, int source_index, int target_position, int target_index);
	void RemoveEvent(int position, int index);
	void ClearPosition(int position);
	void RemoveValue(int position, int index, TCHAR const *name);
	void RemoveString(int position, int index, TCHAR const *name);
	void CopyPosition(int source_position, int target_position, int replace);
	void MovePosition(int source_position, int target_position, int replace);
	void SetTime(int position);
	void SetTimeVelocity(int velocity);
	void SetEventTriggering(int enabled);
	void LoadTimelineString(TCHAR const *timeline, int merge);
	void SaveTimelineFile(TCHAR const *filename);
	void LoadTimelineFile(TCHAR const *filename, int merge);
	void MoveTime(int position);
	void SetPositionTriggering(int enabled);

	//Conditions - Defined in Conditions.cpp
	bool OnEvent(TCHAR const *type);
	bool ValueExists(int position, int index, TCHAR const *name);
	bool StringExists(int position, int index, TCHAR const *name);
	bool OnError();
	bool PositionExists(int position);
	bool EventExists(int position, TCHAR const *type);
	bool OnTick();

	//Expressions - Defined in Expressions.cpp
	int Time();
	int TimeVelocity();
	TCHAR const *CurrentEventType();
	int CurrentEventIndex();
	int NumEventsAt(int position);
	TCHAR const *EventTypeAt(int position, int index);
	float Value(int position, int index, TCHAR const *name);
	TCHAR const *String(int position, int index, TCHAR const *name);
	TCHAR const *Timeline();
	TCHAR const *ErrorMessage();
	int NumValuesAt(int position, int index);
	int NumStringsAt(int position, int index);
	float ValueById(int position, int index, int id);
	TCHAR const *StringById(int position, int index, int id);


	short Handle();         //defined & documented in Extension.cpp
	short Display();        //defined & documented in Extension.cpp

	short Pause();          //defined & documented in Extension.cpp
	short Continue();       //defined & documented in Extension.cpp

	bool Save(HANDLE File); //defined & documented in Extension.cpp
	bool Load(HANDLE File); //defined & documented in Extension.cpp

	//defined & documented in Extension.cpp
	void Action(int ID, RD *rd, long param1, long param2);
	long Condition(int ID, RD *rd, long param1, long param2);
	long Expression(int ID, RD *rd, long param);
};
