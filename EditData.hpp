/* EditData.hpp
 * This is where you control what data
 * you want to have at edittime. You
 * are responsible for serializing and
 * deserializing (saving/loading) the
 * data to/from the SerializedED structure
 * as if it were a file on the hard drive.
 * It doesn't need to be efficient; this
 * is just at edittime and once at the
 * start of the runtime.
 */

struct EditData final
{
	std::int32_t time = 0, speed = 1;
	bool trigger_events = true, trigger_positions = true;

	/* <default constructor>
	 * This is where you provide default values for
	 * your editdata. This constructor is used
	 * when your extension is first created and
	 * default values are needed.
	 */
	EditData() = default;

	/* <copy constructor>
	 * As a convenience in other parts of your code,
	 * you should copy data from another instance
	 * of the EditData class. Make sure you deep-copy
	 * dynamically allocated memory e.g. with pointers.
	 */
	EditData(EditData const &) = default;

	/* operator=
	 * This is essentially the same as the copy
	 * constructor above, except you are working
	 * with an instance that is already
	 * constructed.
	 */
	EditData &operator=(EditData const &) = default;

#ifndef RUN_ONLY
	/* Serialize
	 * This is where you need to "write" data
	 * to SerializedED like a file. Make sure
	 * you can read the data back in the
	 * constructor below!
	 */
	bool Serialize(mv *mV, SerializedED *&SED) const
	{
		//Create an instance of EDOStream, a helper class
		EDOStream os (mV, SED);

		//Write the data you need to save in binary format
		//(you can use text format, but binary is recommended)
		os.write_value<std::int32_t>(time);
		os.write_value<std::int32_t>(speed);
		os.write_value<std::int32_t>(trigger_events? 1 : 0);
		os.write_value<std::int32_t>(trigger_positions? 1 : 0);

		//That's it! EDOStream automatically stores the data in your extension's editdata
		return true; //return false in the event of an error
	}
#endif

	/* <constructor>
	 * This is the primary constructor for the
	 * EditData class. Here you will have to
	 * "read" SerializedED like a file and
	 * load back everything that gets saved
	 * above in Serialize. Make sure you check
	 * the version information first, this
	 * constructor is used to update from
	 * older versions of your editdata as well.
	 */
	EditData(SerializedED *SED)
	{
		if(SED->Header.extVersion == 0) //current version
		{
			//Create an instance of EDIStream, a helper class
			EDIStream is (SED);
			//Read back the data in the same format that you stored it above
			time              =  is.read_value<std::int32_t>();
			speed             =  is.read_value<std::int32_t>();
			trigger_events    = (is.read_value<std::int32_t>()? true : false);
			trigger_positions = (is.read_value<std::int32_t>()? true : false);
		}
		else //the version is newer than current
		{
			//Either try to load the data anyway assuming your
			//future self was smart enough to keep the data in
			//the same format with new data at the end, or
			//make an error dialog and load some default data.
			MessageBox(NULL, _T("The MFA you are trying to load was saved")
			                 _T("with a newer version of Timeline Object."),
			                 _T("Error Loading Timeline Object"), MB_OK);
		}
	}

	/* <destructor>
	 * If you grabbed any memory e.g. with new,
	 * make sure to e.g. delete it in here.
	 */
	~EditData() = default;
};
