// intFileEditor.cpp : Defines the entry point for the console application.
//

#include "radek.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef vector<radek> vektorRadku;

bool Initialize(fstream&);
bool Accept(radek&, radek&, fstream&);
void Vypis(fstream&);

vektorRadku accepted, almostAcc, notAccepted;

int main(int argc, char** argv[])
{
	fstream soub;
	string line;

	if (!Initialize(soub)) return 1;

	getline(soub, line); 
	radek jeden(line), druhy;

	bool inv(false);
	while (! soub.eof())
	{
		getline(soub, line);
		if (inv) 
		{
			inv = false;
			druhy = radek(line);
		}
		else
		{
			inv = true;
			jeden = radek(line);
		}

		if (jeden.intenz == druhy.intenz)
		{
			if (!Accept(jeden, druhy, soub)) 
			{
				inv = true;
				continue;
			}
			getline(soub, line);
			inv = true;
			jeden = radek(line);
		}
	}

	Vypis(soub);

	return 0;
}


void NormalizujK(radek& jeden, radek& druhy, radek& treti, bool third, double ka, double dKa)
{
	jeden.ka /= ka; druhy.ka /= ka;
	if(third) treti.ka /= ka;

	jeden.dKa /= dKa; druhy.dKa /= dKa;
	if (third) treti.dKa /= dKa;
}

void NormalizujI(radek& jeden, radek& druhy, radek& treti, bool third, double intenz, double dIntenz)
{
	if (third)
	{
		jeden.intenz = intenz * (1 - druhy.ka - treti.ka);
		druhy.intenz = intenz * (1 - jeden.ka - treti.ka);
		treti.intenz = intenz * (1 - jeden.ka - druhy.ka);

		jeden.dIntenz = dIntenz * (1 - druhy.ka - treti.ka);
		druhy.dIntenz = dIntenz * (1 - jeden.ka - treti.ka);
		treti.dIntenz = dIntenz * (1 - jeden.ka - druhy.ka);
	}
	jeden.intenz = intenz * (1 - druhy.ka); druhy.intenz = intenz * (1 - jeden.ka);
	jeden.dIntenz = dIntenz * (1 - druhy.ka); druhy.dIntenz = dIntenz * (1 - jeden.ka);
}

void Zarad(radek& jeden, radek& druhy, radek& treti, bool third, vektorRadku vektor)
{
	vektor.push_back(jeden); vektor.push_back(druhy);
	if(third) vektor.push_back(treti);
}

//vraci true, pokud jsou 3 radky stejny. Pokud nejsou, dalsi radek je nactenej v 1. promenny
bool Accept(radek& jeden, radek& druhy, fstream& stream)
{
	string line; radek treti; bool third;
	double ka, dKa;
	getline(stream, line);
	treti = radek(line);
	if (treti.intenz == druhy.intenz)
	{
		ka = jeden.ka + druhy.ka + treti.ka;
		dKa = jeden.dKa + druhy.dKa + treti.dKa;
		third = true;
	}
	else
	{
		ka = jeden.ka + druhy.ka;
		dKa = jeden.dKa + druhy.dKa;
		third = false;

		jeden = treti;
	}

	if ((1 - 3*dKa <= 1) && (1 <= 1 + 3*dKa))
	{
		NormalizujK(jeden, druhy, treti, third, ka, dKa);
		NormalizujI(jeden, druhy, treti, third, jeden.intenz, jeden.dIntenz);
		Zarad(jeden, druhy, treti, third, accepted);
		return third;
	}
	if ((1 - 5*dKa <= 1) && (1 <= 1 + 5*dKa))
	{
		NormalizujK(jeden, druhy, treti, third, ka, dKa);
		NormalizujI(jeden, druhy, treti, third, jeden.intenz, jeden.dIntenz);
		Zarad(jeden, druhy, treti, third, almostAcc);
		return third;
	}
	else
	{
		Zarad(jeden, druhy, treti, third, notAccepted);
		return third;
	}

}

//kdyz se nepovede otevrit soubor vrati false
bool Initialize(fstream& soubor)
{
	string cesta, temp;
	int velikostHlavicky(5);


	cout << "Zadejte jmeno  vstupniho souboru" << endl;
	getline(cin,cesta);
	soubor.open(cesta);
	if (!soubor.good())
	{
		cerr << "Chyba v otevreni souboru" << endl;
		return false;
	}

	for (int i = 0; i < velikostHlavicky; i++)
	{
		getline(soubor, temp);
	}

	return true;

}

void Vypis(fstream& soub)
{
	soub << "\n" << "Accepted:" << endl;

	for (int i = 0; i < accepted.size(); i++)
	{	
		soub << accepted.at(i) << endl;
	}

	for (int i = 0; i < almostAcc.size(); i++)
	{
		soub << almostAcc.at(i) << endl;
	}

	for (int i = 0; i < notAccepted.size(); i++)
	{
		soub << notAccepted.at(i) << endl;
	}

}
