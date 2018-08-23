#include "GUIDGenerator.h"
#include <iomanip>
#include <sstream> 
//#include <guiddef.h>
//#include "Objbase.h"
//#include <winerror.h>
//= NAMESPACES =====
using namespace std;
//==================

namespace TmingEngine
{
	unsigned int GUIDGenerator::Generate()
	{
		hash<string> hasher;
		return (unsigned int)hasher(GenerateAsStr());
	}

	string GUIDGenerator::GenerateAsStr()
	{
		string guidString = "N/A";
		GUID guid;
		HRESULT hr = CoCreateGuid(&guid);
		if (SUCCEEDED(hr))
		{
			stringstream stream;
			stream << hex << uppercase
				<< setw(8) << setfill('0') << guid.Data1
				<< "-" << setw(4) << setfill('0') << guid.Data2
				<< "-" << setw(4) << setfill('0') << guid.Data3
				<< "-";

			for (int i = 0; i < sizeof(guid.Data4); ++i)
			{
				if (i == 2)
					stream << "-";
				stream << hex << setw(2) << setfill('0') << int(guid.Data4[i]);
			}
			guidString = stream.str();
		}

		return guidString;
	}

	string GUIDGenerator::ToStr(unsigned int guid)
	{
		return to_string(guid);
	}

	unsigned int GUIDGenerator::ToUnsignedInt(const string& guid)
	{
		stringstream sstream(guid);
		unsigned int guidSizeT;
		sstream >> guidSizeT;

		return guidSizeT;
	}
}
