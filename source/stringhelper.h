#ifndef STRINGHELPER_H_H
#define STRINGHELPER_H_H
#include <string>
#include <windows.h>
#include <vector>
//¿í×Ö·û×ª»»
#ifdef _UNICODE
#define S2WS(x) StringHelper::s2ws(x)
#define WS2S(x) StringHelper::ws2s(x)
#define TString(x) wstring(x)
#define StringT std::wstring
#else
#define S2WS(x) x
#define WS2S(x) x
#define TString(x) string(x)
#define StringT std::string
#endif
using namespace std;
class StringHelper
{
public:
	static std::string WChar2Ansi(LPCWSTR pwszSrc);
	static string ws2s(wstring& inputws);
	static std::wstring Ansi2WChar(LPCSTR pszSrc, int nLen);
	static std::wstring s2ws(const string& s);
	static double toDouble(const string& s);
	static string toString(double);
	static string parseDouble(const string& s);
	static bool isDouble(const string& s);
	static vector<string> split(string s,char c);
	//static AcString toAcString(const string& s);
};
#endif