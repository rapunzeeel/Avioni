//============================================================================
// Name        : Flight.h
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : Implementacija klase koja rukuje sa fajlovima
//============================================================================
#pragma once
#include "std_lib_facilities.h"
#include "Flight.h"
#include "FileWork.h"


//funkcija koja ucitava fajl
vector<Flight> FileWork::readInputFile(string fileName) {
	//provera da li je uneti fajl isti kao i u komandnim argumentima
	if (fileName != __argv[1]) {
		fileName = __argv[1];
	}
	string fileNameInput = "../" + fileName;
	vector<Flight>listOfFlight;
	string line;

	//ucitavanje fajla
	ifstream inputFile(fileNameInput);
	if (inputFile.is_open()) { 
		while (getline(inputFile, line)) {//ucitavanje linije po linije
			if (line.find(";") != -1) { //ukoliko se u liniji nalazi ; ucitaj je - time ne ucitavamo zaglavlje
				splitLine(line, listOfFlight);//parsiranje linije
			}
			else {
				continue;
			}
		}
		inputFile.close();//zatvaranje fajla
	}
	return listOfFlight; //vraca se lista ucitanih letova
}
//funkcija za parsiranje linije
void FileWork::splitLine(string &line, vector<Flight> &listOfFlight)
{
	string delimiter = ";";
	string token;
	size_t pos1 = 0;
	size_t pos2 = 0;
	vector<string>flight;//lista stringova koji predstavljaju jedan let

	while ((pos2 = line.find(delimiter)) != string::npos) { //parsiranje linije po ; i dodavanje u listu
		token = line.substr(pos1, pos2);
		flight.push_back(token);
		line.erase(pos1, pos2 + delimiter.length() + 1);
	}
	Flight f(flight.at(0), flight.at(1), flight.at(2), flight.at(3)); //elementi liste su atributi klase Flight
	listOfFlight.push_back(f);// dodavanje u listu svih letova
}
//funkcija za upisivanje letova u fajl
void FileWork::writeOutputFile(string fileName, vector<Flight> &listOfFlight) {
	string fileNameOutput = "../" + fileName;

	ofstream outputFile;
	outputFile.open(fileNameOutput); //otvaranje fajla
	for (int i = 0; i < listOfFlight.size(); i++) {
		outputFile << listOfFlight.at(i); //upis linije po liniju
	}
	outputFile.close();//zatvarnje fajla
}
