//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : GUI prozor - u kome se korisniku prikazuje rezultat sortiranja
//============================================================================
#pragma once
#include "GUI.h"   
#include "Graph.h"
#include "Window.h"
#include "Flight.h"

using namespace Graph_lib;

struct DisplayWindow : Window {
	//deklaracija konstruktora i destruktora
	DisplayWindow(Point xy, int width, int height, const string& title, int parameter, int sort, int orderParameter, string inputPath, string outputPath);
	~DisplayWindow();
	//enumeracija parametara za metod sortiranja
	enum sort { selction, heap };
	//enumeracija parametara za kriterijum po kom se sortira
	enum parameter { destination = 1, depatureTime, flightNumber, gateNumber };
	//enumeracija za poredak sortiranja
	enum order { AZ, ZA };
	//deklaracija funkcije za prikaz elemenata prozora
	void displayFun(int parameter, int sort, int orderParameter, string inputPath, string outputPath);

private:
	//uneti parametri - deklaracija
	int sortParametar;
	int sortMethod;
	int m;
	int orderParameter1;
	int numberOfIteration = 0;
	//vector<vector<string>>& listForPoint;
	string inputFile;

	//deklaracija prebrojavanja
	int numberOfSwap;
	int numberOfIter;
	int numberOfCompare;

	//deklaracija dugmica
	Button quitButton;
	Button nextButton;
	Button returnButton;
	Button pointButton;
	//deklaracija teksta
	Text *textParameter;

	//deklaracija bool vresnosti za dugmice
	bool quitPushed;
	bool nextPushed;
	bool returnPushed;
	bool pointPushed;

	//deklaracija callback funkcija
	static void cb_quit(Address, Address);
	static void cb_next(Address, Address);
	static void cb_return(Address, Address);
	static void cb_point(Address, Address);

	//deklaracija funkcija koje pozivaju callback
	void quit();
	void next();
	void returnFunc();
	void point();

	//deklaracija funkcija koje poziva displayFun()
	void displayFirstTable(vector<vector<string>> &listOfChange);
	void displayTable(int parameter, vector<Flight> &listOfFlight);
	void displayNumberPrameters();

};
