class rRundata;
typedef rRundata * LPRRDATA;

// --------------------------------
// RUNNING OBJECT DATA STRUCTURE
// --------------------------------
// If you want to store anything between actions/conditions/expressions
// you should store it here

typedef struct tagRDATA
{
	#include "MagicRDATA.h"

	unsigned long Time;
	signed long TimeDir;
	map<unsigned long, vector<Event> >* Timeline;

	string ToTrigger;
	unsigned long TriggerID;
	bool Trigger;
	bool TimeTrigger;

	string ErrorStr;



} RUNDATA;
typedef	RUNDATA	* LPRDATA;

// --------------------------------
// EDITION OF OBJECT DATA STRUCTURE
// --------------------------------
// These values let you store data in your extension that will be saved in the MFA
// You should use these with properties

typedef struct tagEDATA_V1
{
	extHeader		eHeader;
//	short			swidth;
//	short			sheight;
	unsigned long StartTime;
	signed long StartTimeDir;
	bool TriggerDef;
	bool TriggerChange;

} EDITDATA;
typedef EDITDATA * LPEDATA;
