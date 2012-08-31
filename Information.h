// --------------------
// Object information
// --------------------

// Basic object details
#define	ObjectName			"Timeline Object"
#define	ObjectAuthor		"LB"
#define	ObjectCopyright		"Copyright © 2011 LB-Stuff"
#define	ObjectComment		"This object allows you to trigger events by name via a timeline that can go forward and backward in time. Events can have values and strings attached, and there can be multiple events (even with the same name) in the same spot along the timeline (thus triggering the same event multiple times, but possibly with different values and strings each time)\nGeneral uses include recording, timed events, delayed events, and general timeline uses, of course."
#define	ObjectURL			"http://www.LB-Stuff.com/"
#define	ObjectHelp			"Help\\Timeline Object\\Help.chm"

// If you register your object with Clickteam, change this to the ID you were given
#define ObjectRegID			REGID_PRIVATE

// Change N,O,N,E to 4 unique characters (MMF currently still uses this to keep track)
#define	IDENTIFIER			MAKEID(T,L,O,J) //TimeLine ObJect

// --------------------
// Version information
// --------------------

// PRODUCT_VERSION_TGF or PRODUCT_VERSION_DEVELOPER
#define ForVersion			PRODUCT_VERSION_STANDARD

// Set this to the latest MMF build out when you build the object
#define	MinimumBuild		251

// --------------------
// Beta information
// --------------------

// #define BETA
// #define POPUP_ON_DROP
// #define POPUP_ON_EXE
// #define POPUP_ON_BUILD
// #define POPUP_MESSAGE	"This is a beta extension; use with caution!"

// --------------------
// Handling priority
// --------------------
// If this extension will handle windows messages, specify the priority
// of the handling procedure, 0 = low and 255 = very high

#define	WINDOWPROC_PRIORITY 100
