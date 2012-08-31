// --------------------------------
// Condition menu
// --------------------------------

#ifdef CONDITION_MENU

	SEPARATOR
	ITEM(0,"On Event")
	ITEM(6,"On Position Change")
	SEPARATOR
	ITEM(4,"Position Exists in Timeline")
	ITEM(5,"Event (Name) Exists at Position")
	ITEM(1,"Value Exists in Event")
	ITEM(2,"String Exists in Event")
	SEPARATOR
	ITEM(3,"On Save/Load Error")

#endif

// --------------------------------
// Action menu
// --------------------------------

#ifdef ACTION_MENU

	// You have access to edPtr and you can throw in normal C++
	// code wherever you want in any of these menus. If you want to
	// show certain conditions based on a property (a la OINC socket)
	// use the property's value stored in edPtr:

	// if(edPtr->ShowAdvancedOptions)
	// {
	//		SUB_START("Bake pie")
	//			ITEM(0, "Apple pie")
	//			ITEM(1, "Mince pie")
	//		SUB_END
	// }
	// else
	// {
	//		ITEM(0, "Bake apple pie")
	// }

	// You could do some pretty cool stuff with this, like loading a
	// menu from an external source (ActiveX object?)

	// for(int i=0;i<edPtr->ActionCount;i++)
	//		ITEM(i,edPtr->Actions[i])

	// This will run every time the menu is opened in MMF2, so don't
	// make it too slow or it could get annoying

	SEPARATOR
	ITEM(0,"Add Event")
	ITEM(1,"Set Value in Event")
	ITEM(2,"Set String in Event")
	SEPARATOR
	ITEM(3,"Copy Event")
	ITEM(4,"Move Event")
	SEPARATOR
	ITEM(5,"Remove Event")
	ITEM(6,"Remove Position")
	ITEM(7,"Remove Value from Event")
	ITEM(8,"Remove String from Event")
	SEPARATOR
	ITEM(9,"Copy Position")
	ITEM(10,"Move Position")
	SEPARATOR
	ITEM(11,"Set Time")
	ITEM(12,"Set Time Speed")
	ITEM(17,"Move to Position")
	SEPARATOR
	ITEM(13,"Enable/Disable Event Triggering")
	ITEM(18,"Enable/Disable Position Change Triggering")
	SEPARATOR
	ITEM(14,"Load Timeline from String")
	SEPARATOR
	ITEM(15,"Save Timeline to File")
	ITEM(16,"Load Timeline from File")
	SEPARATOR

#endif


// --------------------------------
// Expression menu
// --------------------------------

#ifdef EXPRESSION_MENU

	SEPARATOR
	ITEM(0,"Get Time")
	ITEM(1,"Get Time Speed")
	SEPARATOR
	ITEM(2,"Get Current Event Name")
	ITEM(3,"Get Current Event Index")
	SEPARATOR
	ITEM(4,"Get Number of Events at Position")
	ITEM(5,"Get Event Name At Position && Index")
	SEPARATOR
	ITEM(6,"Get Attached Value")
	ITEM(7,"Get Attached String")
	SUB_START("Advanced")
		ITEM(10,"Get Number of Values at Position && Index")
		ITEM(11,"Get Number of Strings at Position && Index")
		SEPARATOR
		ITEM(12,"Get Value Name by ID at Position && Index")
		ITEM(13,"Get String Name by ID at Position && Index")
	SUB_END
	SEPARATOR
	ITEM(8,"Get Timeline as String")
	SEPARATOR
	ITEM(9,"Get Error String")
	SEPARATOR

#endif