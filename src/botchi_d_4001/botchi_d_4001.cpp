#include <iostream>

#ifndef USE_LIBSUNDAOWEN
#define USE_LIBSUNDAOWEN 0
#endif

#if USE_LIBSUNDAOWEN != 0
#include <sdw.h>
#else
#define SDW_COMPILER_MSC   1
#define SDW_COMPILER_GNUC  2
#define SDW_COMPILER_CLANG 3

#if defined(_MSC_VER)
#define SDW_COMPILER SDW_COMPILER_MSC
#define SDW_COMPILER_VERSION _MSC_VER
#elif defined(__clang__)
#define SDW_COMPILER SDW_COMPILER_CLANG
#define SDW_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#elif defined(__GNUC__)
#define SDW_COMPILER SDW_COMPILER_GNUC
#define SDW_COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#error "compiler no support"
#endif

#define SDW_PLATFORM_WINDOWS 1
#define SDW_PLATFORM_LINUX   2
#define SDW_PLATFORM_MACOS   3
#define SDW_PLATFORM_CYGWIN  4

#if defined(_WIN32)
#define SDW_PLATFORM SDW_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#define SDW_PLATFORM SDW_PLATFORM_MACOS
#elif defined(__linux__)
#define SDW_PLATFORM SDW_PLATFORM_LINUX
#elif defined(__CYGWIN__)
#define SDW_PLATFORM SDW_PLATFORM_CYGWIN
#else
#error "platform no support"
#endif

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <direct.h>
#include <io.h>
#if defined(SDW_MAIN)
#include <shellapi.h>
#endif
#else
#if SDW_PLATFORM == SDW_PLATFORM_MACOS
#include <mach-o/dyld.h>
#endif
#if (SDW_COMPILER == SDW_COMPILER_GNUC && SDW_COMPILER_VERSION < 50400) || SDW_PLATFORM == SDW_PLATFORM_CYGWIN || defined(SDW_XCONVERT)
#include <iconv.h>
#endif
#include <dirent.h>
#include <unistd.h>
#endif
#include <sys/stat.h>

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfloat>
#if SDW_COMPILER != SDW_COMPILER_MSC || (SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION >= 1800)
#include <cinttypes>
#else
#ifndef _PFX_8
#define _PFX_8 "hh"
#endif
#ifndef _PFX_16
#define _PFX_16 "h"
#endif
#ifndef _PFX_32
#define _PFX_32 "l"
#endif
#ifndef _PFX_64
#define _PFX_64 "ll"
#endif
#ifndef PRId8
#define PRId8 _PFX_8 "d"
#endif
#ifndef PRId16
#define PRId16 _PFX_16 "d"
#endif
#ifndef PRId32
#define PRId32 _PFX_32 "d"
#endif
#ifndef PRId64
#define PRId64 _PFX_64 "d"
#endif
#ifndef PRIu8
#define PRIu8 _PFX_8 "u"
#endif
#ifndef PRIu16
#define PRIu16 _PFX_16 "u"
#endif
#ifndef PRIu32
#define PRIu32 _PFX_32 "u"
#endif
#ifndef PRIu64
#define PRIu64 _PFX_64 "u"
#endif
#ifndef PRIx8
#define PRIx8 _PFX_8 "x"
#endif
#ifndef PRIx16
#define PRIx16 _PFX_16 "x"
#endif
#ifndef PRIx32
#define PRIx32 _PFX_32 "x"
#endif
#ifndef PRIx64
#define PRIx64 _PFX_64 "x"
#endif
#ifndef PRIX8
#define PRIX8 _PFX_8 "X"
#endif
#ifndef PRIX16
#define PRIX16 _PFX_16 "X"
#endif
#ifndef PRIX32
#define PRIX32 _PFX_32 "X"
#endif
#ifndef PRIX64
#define PRIX64 _PFX_64 "X"
#endif
#endif
#include <climits>
#include <clocale>
#include <cmath>
#include <cstdarg>
#include <cstddef>
#if SDW_COMPILER != SDW_COMPILER_MSC || (SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION >= 1600)
#include <cstdint>
#else
typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
#ifndef UINT32_MAX
#define UINT32_MAX       0xffffffffU
#endif
#ifndef UINT32_C
#define UINT32_C(x)  (x ## U)
#endif
#ifndef UINT64_C
#define UINT64_C(x)  (x ## ULL)
#endif
#endif
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>
#include <algorithm>
#include <bitset>
#if SDW_COMPILER == SDW_COMPILER_CLANG || (SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION >= 1600) || (SDW_COMPILER == SDW_COMPILER_GNUC && SDW_COMPILER_VERSION >= 50400)
#include <codecvt>
#endif
#include <deque>
#include <functional>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <queue>
#include <random>
#include <regex>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
#if SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION < 1600
using namespace std::tr1;
#endif

typedef int8_t n8;
typedef int16_t n16;
typedef int32_t n32;
typedef int64_t n64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#if SDW_COMPILER == SDW_COMPILER_MSC
#if SDW_COMPILER_VERSION < 1600
#define nullptr NULL
#endif
#if SDW_COMPILER_VERSION < 1600
typedef wchar_t Char16_t;
typedef wstring U16String;
#elif SDW_COMPILER_VERSION >= 1900
typedef u16 Char16_t;
typedef basic_string<Char16_t> U16String;
#else
typedef char16_t Char16_t;
typedef u16string U16String;
#endif
#else
typedef wchar_t Char16_t;
typedef wstring U16String;
#endif
typedef wchar_t UChar;
typedef wstring UString;
typedef wregex URegex;
typedef struct _stat64 Stat;
#else
typedef char16_t Char16_t;
typedef u16string U16String;
typedef char UChar;
typedef string UString;
typedef regex URegex;
typedef struct stat Stat;
#endif

n32 SToN32(const string& a_sString, int a_nRadix = 10)
{
	return static_cast<n32>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

template<typename T>
vector<T> Split(const T& a_sString, const T& a_sSeparator)
{
	vector<T> vString;
	for (typename T::size_type uOffset = 0; uOffset < a_sString.size(); uOffset += a_sSeparator.size())
	{
		typename T::size_type uPos = a_sString.find(a_sSeparator, uOffset);
		if (uPos != T::npos)
		{
			vString.push_back(a_sString.substr(uOffset, uPos - uOffset));
			uOffset = uPos;
		}
		else
		{
			vString.push_back(a_sString.substr(uOffset));
			break;
		}
	}
	if (vString.empty())
	{
		vString.push_back(a_sString);
	}
	return vString;
}

template<typename T>
vector<T> Split(const T& a_sString, const typename T::value_type* a_pSeparator)
{
	if (a_pSeparator == nullptr)
	{
		vector<T> vString;
		vString.push_back(a_sString);
		return vString;
	}
	else
	{
		return Split(a_sString, T(a_pSeparator));
	}
}
#endif

int main(int argc, char* argv[])
{
	string sLine;
	getline(cin, sLine);
	vector<string> vValue = Split(sLine, " ");
	int nSum = 0;
	for (vector<string>::iterator it = vValue.begin(); it != vValue.end(); ++it)
	{
		nSum += SToN32(*it);
	}
	printf("%d\n", nSum % 10);
	return 0;
}
