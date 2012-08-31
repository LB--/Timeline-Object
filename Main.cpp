// ============================================================================
//
// This file contains the actions, conditions and expressions your object uses
// 
// ============================================================================

#include "Common.h"
#include "ParamHelp.h"

/* ******* Custom Function Definititions ******* */
	//To String
template<typename VT>
string String(VT Val)
{
	stringstream StrStream;
	StrStream << Val;
	return(StrStream.str());
}

	//From String
template<typename VT>
VT Number(string Str)
{
	istringstream StrStream;
	StrStream.str(Str);
	VT Ret;
	StrStream >>Ret;
	return(Ret);
}

	//String Functions
string Escape(const string& ToEsc)
{
	string Return;
	for(unsigned long i = 0; i < ToEsc.length(); ++i)
	{
		char Check = ToEsc[i];
		if(Check == '|' || Check == ':' || Check == '{' || Check == '=' || Check == ';' || Check == ',' || Check == '}' || Check == '\\')
		{
			Return += '\\'; //Escape from Problem Island: The Amazing Backslash
		}
		Return += Check;
	}
	return(Return);
}

inline char At(const string& Str, const unsigned long& at, const char& Else = '\0')
{
	if(at < Str.length())
	{
		return(Str[at]);
	}
	return(Else);
}

vector<string> Split(const string& Source, const char& By, const char& Escape = '\0')
{
	vector<string> Return;
	if(Source.length() > 0)
	{
		Return.push_back("");
		for(unsigned long i = 0; i < Source.length(); ++i)
		{
			if(Source[i] != By && (Escape != '\0' && Source[i] != Escape))
			{
				Return[Return.size() - 1] += Source[i];
			}
			else if(Escape != '\0' && (Source[i] == By && (At(Source, (i - 2)) != Escape && At(Source, (i - 1)) == Escape)))
			{
				Return[Return.size() - 1] += Source[i];
			}
			else if((i + 1) < Source.length())
			{
				Return.push_back("");
			}
		}
	}
	return(Return);
}

inline string At(const vector<string>& In, const unsigned long& at, const string& Else = "")
{
	if(at < In.size())
	{
		return(In[at]);
	}
	return(Else);
}

// ============================================================================
//
// CONDITIONS
// 
// ============================================================================

CONDITION(
	/* ID */			0,
	/* Name */			"%o: On Event %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_STRING,"Event Name")
) {
	return(rdPtr->Trigger && rdPtr->ToTrigger == StrParam());
}

CONDITION(
	/* ID */			1,
	/* Name */			"%o: Value %2 Exists in Event %1, Position %0",
	/* Flags */			EVFLAGS_ALWAYS|EVFLAGS_NOTABLE,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"Value Name")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string ValueName = StrParam();
	return(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end()
		&& EventID < (*rdPtr->Timeline)[Position].size()
		&& (*rdPtr->Timeline)[Position][EventID].Values.find(ValueName)
		!= (*rdPtr->Timeline)[Position][EventID].Values.end());
}

CONDITION(
	/* ID */			2,
	/* Name */			"%o: String %2 Exists in Event %1, Position %0",
	/* Flags */			EVFLAGS_ALWAYS|EVFLAGS_NOTABLE,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"Value Name")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string StringName = StrParam();
	return(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end()
		&& EventID < (*rdPtr->Timeline)[Position].size()
		&& (*rdPtr->Timeline)[Position][EventID].Strings.find(StringName)
		!= (*rdPtr->Timeline)[Position][EventID].Strings.end());
}

CONDITION(
	/* ID */			3,
	/* Name */			"%o: On Save/Load Error",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(true);
}

CONDITION(
	/* ID */			4,
	/* Name */			"%o: Position %0 Exists in Timeline",
	/* Flags */			EVFLAGS_ALWAYS|EVFLAGS_NOTABLE,
	/* Params */		(1,PARAM_NUMBER,"Position in Timeline")
) {
	unsigned long Position = (unsigned long)lParam();
	return(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end());
}

CONDITION(
	/* ID */			5,
	/* Name */			"%o: Event(s) %1 Exist(s) at Position %0",
	/* Flags */			EVFLAGS_ALWAYS|EVFLAGS_NOTABLE,
	/* Params */		(2,PARAM_NUMBER,"Position in Timeline",PARAM_STRING,"Event(s) Name")
) {
	unsigned long Position = (unsigned long)lParam();
	string EventName = StrParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end())
	{
		for(unsigned long i = 0; i < (*rdPtr->Timeline)[Position].size(); ++i)
		{
			if((*rdPtr->Timeline)[Position][i].Name == EventName)
			{
				return(true);
			}
		}
	}
	return(false);
}

CONDITION(
	/* ID */			6,
	/* Name */			"%o: On Position Change",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(true);
}


// ============================================================================
//
// ACTIONS
// 
// ============================================================================

ACTION(
	/* ID */			0,
	/* Name */			"Add Event %1 at %0",
	/* Flags */			0,
	/* Params */		(2,PARAM_NUMBER,"Position in Timeline",PARAM_STRING,"Event Name")
) {
	unsigned long Position = (unsigned long)lParam();
	string EventName = StrParam();
	(*rdPtr->Timeline)[Position].push_back(Event(EventName));
}

ACTION(
	/* ID */			1,
	/* Name */			"Set Value %2 to %3 in Event %1 at %0",
	/* Flags */			0,
	/* Params */		(4,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"Value Name",PARAM_NUMBER,"Value")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string ValueName = StrParam();
	signed long Value = lParam();
	if(EventID < (*rdPtr->Timeline)[Position].size())
	{
		(*rdPtr->Timeline)[Position][EventID].Values[ValueName] = Value;
	}
}

ACTION(
	/* ID */			2,
	/* Name */			"Set String %2 to %3 in Event %1 at %0",
	/* Flags */			0,
	/* Params */		(4,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"String Name",PARAM_STRING,"String")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string StringName = StrParam();
	string String = StrParam();
	if(EventID < (*rdPtr->Timeline)[Position].size())
	{
		(*rdPtr->Timeline)[Position][EventID].Strings[StringName] = String;
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			3,
	/* Name */			"Copy Event %1 Position %0 to before %3 Position %2",
	/* Flags */			0,
	/* Params */		(4,PARAM_NUMBER,"Position in Timeline (Source)",PARAM_NUMBER,"Event Index (Source)",PARAM_NUMBER,"Position in Timeline (Target)",PARAM_NUMBER,"Event Index to Insert Before (Target)")
) {
	unsigned long PositionA = (unsigned long)lParam(); //Source
	unsigned long EventIDA = (unsigned long)lParam(); //Source
	unsigned long PositionB = (unsigned long)lParam(); //Target
	unsigned long EventIDB = (unsigned long)lParam(); //Target to Insert Before

	if(rdPtr->Timeline->find(PositionA) != rdPtr->Timeline->end() && rdPtr->Timeline->find(PositionB) != rdPtr->Timeline->end()
		&& EventIDA < (*rdPtr->Timeline)[PositionA].size() && EventIDB <= (*rdPtr->Timeline)[PositionB].size())
	{
		(*rdPtr->Timeline)[PositionB].insert(((*rdPtr->Timeline)[PositionB].begin() + EventIDB), (*rdPtr->Timeline)[PositionA][EventIDA]);
	}
}

ACTION(
	/* ID */			4,
	/* Name */			"Move Event %1 Position %0 to before %3 Position %2",
	/* Flags */			0,
	/* Params */		(4,PARAM_NUMBER,"Position in Timeline (Source)",PARAM_NUMBER,"Event Index (Source)",PARAM_NUMBER,"Position in Timeline (Target)",PARAM_NUMBER,"Event Index to Insert Before (Target)")
) {
	unsigned long PositionA = (unsigned long)lParam(); //Source
	unsigned long EventIDA = (unsigned long)lParam(); //Source
	unsigned long PositionB = (unsigned long)lParam(); //Target
	unsigned long EventIDB = (unsigned long)lParam(); //Target to Insert Before

	if(rdPtr->Timeline->find(PositionA) != rdPtr->Timeline->end() && rdPtr->Timeline->find(PositionB) != rdPtr->Timeline->end()
		&& EventIDA < (*rdPtr->Timeline)[PositionA].size() && EventIDB <= (*rdPtr->Timeline)[PositionB].size())
	{
		if(PositionA == PositionB && EventIDB < EventIDA) //Same Position, Event to delete is offset
		{
			(*rdPtr->Timeline)[PositionB].insert(((*rdPtr->Timeline)[PositionB].begin() + EventIDB), (*rdPtr->Timeline)[PositionA][EventIDA]); //Must be in both
			(*rdPtr->Timeline)[PositionA].erase((*rdPtr->Timeline)[PositionA].begin() + 1 + EventIDA);
		}
		else if(EventIDA != EventIDB) //Otherwise delete as normal.
		{
			(*rdPtr->Timeline)[PositionB].insert(((*rdPtr->Timeline)[PositionB].begin() + EventIDB), (*rdPtr->Timeline)[PositionA][EventIDA]); //Must be in both
			(*rdPtr->Timeline)[PositionA].erase((*rdPtr->Timeline)[PositionA].begin() + EventIDA);
		}
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			5,
	/* Name */			"Remove Event %1 at %0",
	/* Flags */			0,
	/* Params */		(2,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		(*rdPtr->Timeline)[Position].erase((*rdPtr->Timeline)[Position].begin() + EventID);
	}
}

ACTION(
	/* ID */			6,
	/* Name */			"Remove Position %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Position in Timeline")
) {
	unsigned long Position = (unsigned long)lParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end())
	{
		rdPtr->Timeline->erase(Position);
	}
}

ACTION(
	/* ID */			7,
	/* Name */			"Remove Value %2 from %1 at %0",
	/* Flags */			0,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"Value Name")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string ValueName = StrParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		(*rdPtr->Timeline)[Position][EventID].Values.erase(ValueName);
	}
}

ACTION(
	/* ID */			8,
	/* Name */			"Remove String %2 from %1 at %0",
	/* Flags */			0,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline",PARAM_NUMBER,"Event Index",PARAM_STRING,"String Name")
) {
	unsigned long Position = (unsigned long)lParam();
	unsigned long EventID = (unsigned long)lParam();
	string StringName = StrParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		(*rdPtr->Timeline)[Position][EventID].Strings.erase(StringName);
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			9,
	/* Name */			"Copy Position %0 onto %1 (Replace = %2)",
	/* Flags */			0,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline (Source)",PARAM_NUMBER,"Position in Timeline (Target)",PARAM_NUMBER,"Replace (erase original content of) Target Position? 1 = yes, anything else = no")
) {
	unsigned long PositionA = (unsigned long)lParam();
	unsigned long PositionB = (unsigned long)lParam();
	if(rdPtr->Timeline->find(PositionA) != rdPtr->Timeline->end() && PositionA != PositionB)
	{
		if(lParam() == 1 && rdPtr->Timeline->find(PositionB) != rdPtr->Timeline->end())
		{
			(*rdPtr->Timeline)[PositionB] = (*rdPtr->Timeline)[PositionA];
		}
		else
		{
			for(unsigned long i = 0; i < (*rdPtr->Timeline)[PositionA].size(); ++i)
			{
				(*rdPtr->Timeline)[PositionB].push_back((*rdPtr->Timeline)[PositionA][i]);
			}
		}
	}
}

ACTION(
	/* ID */			10,
	/* Name */			"Move Position %0 onto %1 (Replace = %2)",
	/* Flags */			0,
	/* Params */		(3,PARAM_NUMBER,"Position in Timeline (Source)",PARAM_NUMBER,"Position in Timeline (Target)",PARAM_NUMBER,"Replace (erase original content of) Target Position? 1 = yes, anything else = no")
) {
	unsigned long PositionA = (unsigned long)lParam();
	unsigned long PositionB = (unsigned long)lParam();
	if(rdPtr->Timeline->find(PositionA) != rdPtr->Timeline->end() && PositionA != PositionB)
	{
		if(lParam() == 1 && rdPtr->Timeline->find(PositionB) != rdPtr->Timeline->end())
		{
			(*rdPtr->Timeline)[PositionB] = (*rdPtr->Timeline)[PositionA];
		}
		else
		{
			for(unsigned long i = 0; i < (*rdPtr->Timeline)[PositionA].size(); ++i)
			{
				(*rdPtr->Timeline)[PositionB].push_back((*rdPtr->Timeline)[PositionA][i]);
			}
		}
		rdPtr->Timeline->erase(PositionA);
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			11,
	/* Name */			"Set Time to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Time to Set to (in frames) (positive only)")
) {
	rdPtr->Time = (unsigned long)lParam();
}

ACTION(
	/* ID */			12,
	/* Name */			"Set Time Speed to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Time Speed (0 = stopped, negative numbers = backwards in time (until 0), positive = forward in time")
) {
	rdPtr->TimeDir = lParam();
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			13,
	/* Name */			"Allow Event Triggering = %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"1 = allow, anything else = disable")
) {
	switch(lParam())
	{
	case 1:
		rdPtr->Trigger = true;
		break;
	default:
		rdPtr->Trigger = false;
		break;
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			14,
	/* Name */			"Load Timeline from String %0 (Keep Current Timeline = %1)",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"Enter the Timeline as a String",PARAM_NUMBER,"Keep Current Timeline Data? 1 = yes, anything else = no")
) {
	string TimeString = StrParam();
	if(lParam() != 1)
	{
		rdPtr->Timeline->clear();
	}

	/* ******* Split Positions ******* */
	vector<string> PositionsA = Split(TimeString, '|', '\\');//Primary Split
	map<unsigned long, string> Positions; //Secondary Split
	for(unsigned long i = 0; i < PositionsA.size(); ++i)
	{
		Positions[Number<unsigned long>(At(Split(PositionsA[i], ':', '\\'), 0))] = At(Split(PositionsA[i], ':', '\\'), 1);
	}

	/* ******* Split Events ******* */
	for(map<unsigned long, string>::iterator PosIt = Positions.begin(); PosIt != Positions.end(); ++PosIt)
	{
		vector<string> EventsA = Split(PosIt->second, '}', '\\'); //Primary Split
		map<string, string> Events; //Secondary Split
		for(unsigned long i = 0; i < EventsA.size(); ++i)
		{
			Events[At(Split(EventsA[i], '{', '\\'), 0)] = At(Split(EventsA[i], '{', '\\'), 1);
		}

		/* ******* Split Values & Strings ******* */
		for(map<string, string>::iterator EvtIt = Events.begin(); EvtIt != Events.end(); ++EvtIt)
		{
			string ValuesA = At(Split(EvtIt->second, ';', '\\'), 0); //Primary Split
			string StringsA = At(Split(EvtIt->second, ';', '\\'), 1); //Primary Split

			vector<string> Values = Split(ValuesA, ',', '\\'); //Secondary Split
			vector<string> Strings = Split(StringsA, ',', '\\'); //Secondary Split

			/* ******* Magic ******* */
			(*rdPtr->Timeline)[PosIt->first].push_back(Event(EvtIt->first));
			for(unsigned long i = 0; i < Values.size(); ++i)
			{
				(*rdPtr->Timeline)[PosIt->first][(*rdPtr->Timeline)[PosIt->first].size() - 1].Values[At(Split(Values[i], '=', '\\'), 0)] = Number<signed long>(At(Split(Values[i], '=', '\\'), 1));
			}
			for(unsigned long i = 0; i < Strings.size(); ++i)
			{
				(*rdPtr->Timeline)[PosIt->first][(*rdPtr->Timeline)[PosIt->first].size() - 1].Strings[At(Split(Strings[i], '=', '\\'), 0)] = At(Split(Strings[i], '=', '\\'), 1);
			}
		}
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			15,
	/* Name */			"Save Timeline to File %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_STRING,"Enter the Filepath to Save to")
) {
	string FilePath = StrParam();

	OFS Write;
	Write.Open(FilePath);
	if(!Write.Is_Open())
	{
		rdPtr->ErrorStr = "Could not open file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\" for save output.";
		rdPtr->rRd->GenerateEvent(3);
		Write.Close();
		return;
	}
	if(Write.Fail())
	{
		rdPtr->ErrorStr = "Could not save to file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\".";
		rdPtr->rRd->GenerateEvent(3);
		Write.Close();
		return;
	}

	#define CS (const string)
	#define CUL (const unsigned long)
	#define CSL (const signed long)

	/* ******* Save Code!! ******* */
	const string Identifier = "Timeline"; //8-character Identifier
	const unsigned char Version = 0; //File Format Version Number
	Write (Identifier) << Version;

	Write << CUL rdPtr->Timeline->size(); //Number of Positions
	for(map<unsigned long, vector<Event> >::iterator EvtIt = rdPtr->Timeline->begin(); EvtIt != rdPtr->Timeline->end(); ++EvtIt) //For Each Position
	{
		Write << CUL EvtIt->first; //Current Position
		Write << CUL EvtIt->second.size(); //Number of Events
		for(unsigned long i = 0; i < EvtIt->second.size(); ++i) //For Each Event
		{
			Write << CS EvtIt->second[i].Name; //Event Name
			Write << CUL EvtIt->second[i].Values.size(); //Number of Values
			for(map<string, signed long>::iterator ValIt = EvtIt->second[i].Values.begin(); ValIt != EvtIt->second[i].Values.end(); ++ValIt) //For Each Value
			{
				Write << CS ValIt->first; //Value Name (As String)
				Write << CSL ValIt->second; //Value of Value
			}

			Write << CUL EvtIt->second[i].Strings.size(); //Number of Strings
			for(map<string, string>::iterator StrIt = EvtIt->second[i].Strings.begin(); StrIt != EvtIt->second[i].Strings.end(); ++StrIt) //For Each String
			{
				Write << CS StrIt->first; //String Name (As String)
				Write << CS StrIt->second; //Content of String
			}
		}
	}

	/* ******* All Done! ******* */
	Write.Close();
}

ACTION(
	/* ID */			16,
	/* Name */			"Load Timeline from File %0 (Keep Current Timeline = %1)",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"Enter the Filepath to Load from",PARAM_NUMBER,"Keep Current Timeline Data? 1 = yes (append), anything else = no")
) {
	string FilePath = StrParam();
	if(lParam() != 1)
	{
		rdPtr->Timeline->clear();
	}

	IFS Read;
	Read.Open(FilePath);
	if(!Read.Is_Open())
	{
		rdPtr->ErrorStr = "Could not open file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\" for loading.";
		rdPtr->rRd->GenerateEvent(3);
		Read.Close();
		return;
	}
	if(Read.Fail())
	{
		rdPtr->ErrorStr = "Could not load from file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\".";
		rdPtr->rRd->GenerateEvent(3);
		Read.Close();
		return;
	}

	string Identifier;
	unsigned char Version;
	Read (Identifier, 8) >> Version;
	if(Identifier != "Timeline")
	{
		rdPtr->ErrorStr = "The file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\" is not a valid Timeline file.";
		rdPtr->rRd->GenerateEvent(3);
		Read.Close();
		return;
	}

	unsigned long Positions;
	switch(Version)
	{
	case 0:
		/* ******* Format 0 - The Original Format ******* */
		Read >> Positions;
		for(unsigned long i = 0; i < Positions; ++i)
		{
			unsigned long Position;
			unsigned long Events;
			Read >> Position >> Events;
			for(unsigned long l = 0; l < Events; ++l)
			{
				string EventName;
				Read >> EventName;
				(*rdPtr->Timeline)[Position].push_back(Event(EventName));

				unsigned long Values;
				Read >> Values;
				for(unsigned long I = 0; I < Values; ++I)
				{
					string ValueName;
					signed long Value;
					Read >> ValueName >> Value;
					(*rdPtr->Timeline)[Position][(*rdPtr->Timeline)[Position].size() - 1].Values[ValueName] = Value;
				}

				unsigned long Strings;
				Read >> Strings;
				for(unsigned long L = 0; L < Values; ++L)
				{
					string StringName;
					string Content;
					Read >> StringName >> Content;
					(*rdPtr->Timeline)[Position][(*rdPtr->Timeline)[Position].size() - 1].Strings[StringName] = Content;
				}
			}
		}

		//Done
		break;

	default: //Unkown Version/Format
		rdPtr->ErrorStr = "The file \"";
		rdPtr->ErrorStr += FilePath;
		rdPtr->ErrorStr += "\" is a valid Timeline file, but it is saved in a newer or unknown version/format, and cannot be opened.";
		rdPtr->rRd->GenerateEvent(3);
		break;
	}
	Read.Close();
}

ACTION(
	/* ID */			17,
	/* Name */			"Move to Positition %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Position in Timeline to Move to")
) {
	unsigned long To = lParam();
	bool First = false;
	while(rdPtr->Time != To)
	{
		if(First && rdPtr->Timeline->find(rdPtr->Time) != rdPtr->Timeline->end())
		{
			for(unsigned long i = 0; i < (*rdPtr->Timeline)[rdPtr->Time].size(); i++)
			{
				rdPtr->ToTrigger = (*rdPtr->Timeline)[rdPtr->Time][i].Name;
				rdPtr->TriggerID = i;
				rdPtr->rRd->GenerateEvent(0);
			}
		}

		if(rdPtr->Time < To)
		{
			++rdPtr->Time;
		}
		else if(rdPtr->Time > To)
		{
			--rdPtr->Time;
		}
		else
		{
			break;
		}
		First = true;
	}
}

/* ******* ******* ******* ******* ******* ******* ******* */

ACTION(
	/* ID */			18,
	/* Name */			"Allow Position Change Triggering = %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"1 = allow, anything else = disable")
) {
	switch(lParam())
	{
	case 1:
		rdPtr->TimeTrigger = true;
		break;
	default:
		rdPtr->TimeTrigger = false;
		break;
	}
}

// ============================================================================
//
// EXPRESSIONS
// 
// ============================================================================

EXPRESSION(
	/* ID */			0,
	/* Name */			"Time(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(rdPtr->Time);
}

EXPRESSION(
	/* ID */			1,
	/* Name */			"TimeSpeed(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(rdPtr->TimeDir);
}

EXPRESSION(
	/* ID */			2,
	/* Name */			"CurrentEvent$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	ReturnStringSafe(rdPtr->ToTrigger.c_str());
}

EXPRESSION(
	/* ID */			3,
	/* Name */			"CurrentEvent(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(rdPtr->TriggerID);
}

EXPRESSION(
	/* ID */			4,
	/* Name */			"EventsAt(",
	/* Flags */			0,
	/* Params */		(1,EXPPARAM_LONG,"Position in Timeline")
) {
	unsigned long Position = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end())
	{
		return((*rdPtr->Timeline)[Position].size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			5,
	/* Name */			"EventIDAt$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(2,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index")
) {
	unsigned long Pos = (unsigned long)xlParam();
	unsigned long Index = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Pos) != rdPtr->Timeline->end() && Index < (*rdPtr->Timeline)[Pos].size())
	{
		ReturnStringSafe((*rdPtr->Timeline)[Pos][Index].Name.c_str());
	}
	ReturnString("");
}

EXPRESSION(
	/* ID */			6,
	/* Name */			"Value(",
	/* Flags */			0,
	/* Params */		(3,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index",EXPPARAM_STRING,"Value Name")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	string Name = EStrParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		return((*rdPtr->Timeline)[Position][EventID].Values[Name]);
	}
	return(0);
}

EXPRESSION(
	/* ID */			7,
	/* Name */			"String$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(3,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index",EXPPARAM_STRING,"String Name")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	string Name = EStrParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		ReturnStringSafe((*rdPtr->Timeline)[Position][EventID].Strings[Name].c_str());
	}
	ReturnString("");
}

EXPRESSION(
	/* ID */			8,
	/* Name */			"Timeline$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	string Final;
	for(map<unsigned long, vector<Event> >::iterator Tit = (*rdPtr->Timeline).begin(); Tit != (*rdPtr->Timeline).end(); ++Tit)
	{
		if(Tit != (*rdPtr->Timeline).begin())
		{
			Final += '|';
		}
		Final += String<unsigned long>((*Tit).first);
		Final += ':';
		for(unsigned long i = 0; i < (*Tit).second.size(); ++i)
		{
			Final += Escape((*Tit).second[i].Name);
			Final += '{';
			for(map<string, signed long>::iterator Vit = (*Tit).second[i].Values.begin(); Vit != (*Tit).second[i].Values.end(); ++Vit)
			{
				if(Vit != (*Tit).second[i].Values.begin())
				{
					Final += ',';
				}
				Final += Escape((*Vit).first);
				Final += '=';
				Final += String<signed long>((*Vit).second);
			}
			Final += ';';
			for(map<string, string>::iterator Sit = (*Tit).second[i].Strings.begin(); Sit != (*Tit).second[i].Strings.end(); ++Sit)
			{
				if(Sit != (*Tit).second[i].Strings.begin())
				{
					Final += ',';
				}
				Final += Escape((*Sit).first);
				Final += '=';
				Final += Escape((*Sit).second);
			}
			Final += '}';
		}
	}
	ReturnStringSafe(Final.c_str());
}

EXPRESSION(
	/* ID */			9,
	/* Name */			"Error$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	ReturnStringSafe(rdPtr->ErrorStr.c_str());
}

EXPRESSION(
	/* ID */			10,
	/* Name */			"ValCount(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		return((*rdPtr->Timeline)[Position][EventID].Values.size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			11,
	/* Name */			"StrCount(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size())
	{
		return((*rdPtr->Timeline)[Position][EventID].Strings.size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			12,
	/* Name */			"ValNameByID$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(3,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index",EXPPARAM_LONG,"Value ID")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	unsigned long ValueID = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size() && ValueID < (*rdPtr->Timeline)[Position][EventID].Values.size())
	{
		map<string, signed long>::iterator At = (*rdPtr->Timeline)[Position][EventID].Values.begin();
		for(unsigned long i = 0; i < ValueID; ++At, ++i){}
		ReturnStringSafe(At->first.c_str());
	}
	ReturnString("");
}

EXPRESSION(
	/* ID */			13,
	/* Name */			"StrNameByID$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(3,EXPPARAM_LONG,"Position in Timeline",EXPPARAM_LONG,"Event Index",EXPPARAM_LONG,"String ID")
) {
	unsigned long Position = (unsigned long)xlParam();
	unsigned long EventID = (unsigned long)xlParam();
	unsigned long StringID = (unsigned long)xlParam();
	if(rdPtr->Timeline->find(Position) != rdPtr->Timeline->end() && EventID < (*rdPtr->Timeline)[Position].size() && StringID < (*rdPtr->Timeline)[Position][EventID].Strings.size())
	{
		map<string, string>::iterator At = (*rdPtr->Timeline)[Position][EventID].Strings.begin();
		for(unsigned long i = 0; i < StringID; ++At, ++i){}
		ReturnStringSafe(At->first.c_str());
	}
	ReturnString("");
}