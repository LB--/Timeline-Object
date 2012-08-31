#ifndef _BinFileIO_Header
#define _BinFileIO_Header

#include <fstream>
#include <string>
using namespace std;

/* ******* ******* ******* Outward File Stream Manager Class ******* ******* ******* */
class OFS
{
	ofstream Out;

	OFS(const OFS&);
	OFS& operator=(const OFS&);

	template<typename Typ>
	void Write(const Typ& Data)
	{
		Out.write(reinterpret_cast<const char*>(&Data), sizeof(Typ));
	}

public:
	OFS(){} //Constructor

	void Open(const string& FilePath)
	{
		Out.open(FilePath.c_str(), ios_base::out|ios_base::binary|ios_base::trunc);
	}

	bool Is_Open()
	{
		return(Out.is_open());
	}
	bool Fail()
	{
		return(Out.fail());
	}

	void Close()
	{
		Out.close();
	}

	OFS& operator()(const string& Str) //String (w/o Null Temination)
	{
		Out.write(Str.c_str(), Str.length());
		return((*this));
	}
	OFS& operator<<(const string& Str) //String (Null Terminated)
	{
		Out.write(Str.c_str(), Str.length() + 1);
		return((*this));
	}
	OFS& operator<<(const unsigned long& UL) //Unsigned Long
	{
		Write<unsigned long>(UL);
		return((*this));
	}
	OFS& operator<<(const signed long& SL) //Signed Long
	{
		Write<signed long>(SL);
		return((*this));
	}
	OFS& operator<<(const unsigned char& UC) //Unsigned Char
	{
		Write<unsigned char>(UC);
		return((*this));
	}
};


/* ******* ******* ******* Inward File Stream Manager Class ******* ******* ******* */
class IFS
{
	ifstream In;

	IFS(const OFS&);
	IFS& operator=(const OFS&);

	template<typename Typ>
	void Read(Typ& To)
	{
		In.read(reinterpret_cast<char*>(&To), sizeof(Typ));
	}

public:
	IFS(){} //Constructor

	void Open(const string& FilePath)
	{
		In.open(FilePath.c_str(), ios_base::in|ios_base::binary);
	}

	bool Is_Open()
	{
		return(In.is_open());
	}
	bool Fail()
	{
		return(In.fail());
	}

	void Close()
	{
		In.close();
	}

	IFS& operator()(string& Str, const unsigned long& Length) //String (w/o Null Temination)
	{
		Str = "";
		while(Str.length() < Length && In.good())
		{
			Str += (char)In.get();
		}
		return((*this));
	}
	IFS& operator>>(string& Str) //String (Null Teminated)
	{
		Str = "";
		while(In.good())
		{
			char Ch = (char)In.get();
			if(Ch != '\0')
			{
				Str += Ch;
			}
			else
			{
				break;
			}
		}
		return((*this));
	}
	IFS& operator>>(unsigned long& UL) //Unsigned Long
	{
		UL = 0;
		Read<unsigned long>(UL);
		return((*this));
	}
	IFS& operator>>(signed long& SL) //Signed Long
	{
		SL = 0;
		Read<signed long>(SL);
		return((*this));
	}
	IFS& operator>>(unsigned char& UC) //Unsigned Char
	{
		UC = 0;
		Read<unsigned char>(UC);
		return((*this));
	}
};

#endif