#include "radek.h"
#include <string>
//using namespace std;

radek::radek(std::string)
{
}

radek::radek()
{
}

std::string radek::ToString()
{
	return "";
}

std::fstream & operator << (std::fstream& fstr, const radek &)
{
	return fstr;
}