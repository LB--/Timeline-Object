// Include guard
#ifndef COMMON_H
#define COMMON_H

// Suppress the deprecated warnings for VC2005
#define _CRT_SECURE_NO_WARNINGS

// General includes
#include	"TemplateInc.h"

#include <sstream>
#include <string>
#include <vector>
#include <map>
//#include <utility>
#include <fstream>
using namespace std;
//#include <windows.h>
//#define DB(String) MessageBox(0,#String,"Debug",MB_OK);

#include "BinFileIO.h"

struct Event
{
	string Name;
	map<string, signed long> Values;
	map<string, string> Strings;

	Event(){}
	Event(const string& name){ Name = name; }
};

// Specific to this extension
#include	"Resource.h"
#include	"FlagsPrefs.h"
#include	"Information.h"
#include	"Data.h"

// rTemplate include
#include	"rTemplate.h"

// Globals and prototypes
extern HINSTANCE hInstLib;
extern short * conditionsInfos;
extern short * actionsInfos;
extern short * expressionsInfos;
extern long (WINAPI ** ConditionJumps)(LPRDATA rdPtr, long param1, long param2);
extern short (WINAPI ** ActionJumps)(LPRDATA rdPtr, long param1, long param2);
extern long (WINAPI ** ExpressionJumps)(LPRDATA rdPtr, long param);
extern PropData Properties[];
extern WORD DebugTree[];

// End include guard
#endif
