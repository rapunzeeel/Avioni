//============================================================================
// Name        : Flight.h
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : Klasa koja rukuje sa fajlovima
//============================================================================
#pragma once
#include "std_lib_facilities.h"
#include "Flight.h"

class FileWork
{
private:
	//deklaracija funkcije koja parsira linije
	void splitLine(string &line, vector<Flight> &listOfFlight);
public:
	//deklaracija funkcije za upis u fajl
	void writeOutputFile(string fileName, vector<Flight> &listOfFlight);
	//deklaracija funkcije koja ucitava fajl
	vector<Flight> readInputFile(string fileName);
};