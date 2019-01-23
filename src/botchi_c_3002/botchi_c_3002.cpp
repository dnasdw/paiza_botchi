#include <iostream>

#ifndef USE_LIBSUNDAOWEN
#define USE_LIBSUNDAOWEN 0
#endif

#if USE_LIBSUNDAOWEN != 0
#include <sdw.h>
#else
#include <string>

using namespace std;
#endif

int main(int argc, char* argv[])
{
	string sLine;
	getline(cin, sLine);
	bool bValid = true;
	do
	{
		int nSize = static_cast<int>(sLine.size());
		if (nSize < 6)
		{
			bValid = false;
			break;
		}
		if (sLine.find_first_of("0123456789") == string::npos)
		{
			bValid = false;
			break;
		}
		if (sLine.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") == string::npos)
		{
			bValid = false;
			break;
		}
		for (int i = 0; i < nSize - 2; i++)
		{
			if (sLine[i + 1] == sLine[i] && sLine[i + 2] == sLine[i])
			{
				bValid = false;
				break;
			}
		}
		if (!bValid)
		{
			break;
		}
	} while (false);
	printf("%s\n", bValid ? "Valid" : "Invalid");
	return 0;
}
