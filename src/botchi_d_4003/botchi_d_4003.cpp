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
	string sOutput;
	sOutput.reserve(sLine.size() / 2);
	for (int i = 0; i < static_cast<int>(sLine.size()); i += 2)
	{
		sOutput += sLine[i];
	}
	printf("%s\n", sOutput.c_str());
	return 0;
}
