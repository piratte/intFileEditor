#ifndef RADEK
#define RADEK

#include <string>

struct radek
{
	int number;
	double energy, dEnergy, intenz, dIntenz, ka, dKa;
	std::string zbytek;

	friend std::fstream & operator << (std::fstream& fstr, const radek &);

	radek(std::string);
	radek();

	std::string ToString();
};

std::fstream & operator << (std::fstream& fstr, const radek &);

#endif