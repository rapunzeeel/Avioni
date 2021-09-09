//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : GUI prozor - u kome korisnik unosi parametre za dortiranje, ulazne i izlazne putanje
//============================================================================
#pragma once
#include "GUI.h"   
#include "Graph.h"
#include "Window.h"

using namespace Graph_lib;

struct ChooseWindow : Window {
	//deklaracija konstruktora i destruktora
	ChooseWindow(Point xy, int width, int height, const string& title, char *argv[]);
	~ChooseWindow();
	//enumeracija parametara za metod sortiranja
	enum sort { selction, heap };
	//enumeracija parametara za kriterijum po kom se sortira
	enum parameter { destination = 1, depatureTime, flightNumber, gateNumber };
	//enumeracija za poredak sortiranja
	enum order { AZ, ZA };
private:
	//deklaracija promenljivih za unete parametre
	int sort;
	int parameter;
	int orderParameter;

	string inputPath;
	string outputPath;
	//deklarisanje box-ova za unos
	In_box inputPathBox;
	In_box outputPathBox;

	//deklaracija dugmica
	Button saveInputPathButton;
	Button saveOutputPathButton;
	Button selectionSortButton;
	Button heapSortButton;
	Button destinationButton;
	Button departureTimeButton;
	Button flightNumberButton;
	Button gateNumberButton;
	Button AZsortButton;
	Button ZAsortButton;

	//deklaracija bool vrednosti za dugmice
	bool saveInputPathPushed;
	bool saveOutputPathPushed;
	bool selectionSortPushed;
	bool heapSortPushed;
	bool destinationPushed;
	bool departureTimePushed;
	bool flightNumberPushed;
	bool gateNumberPushed;
	bool AZsortPushed;
	bool ZAsortPushed;

	//deklaracija callback funkcija
	static void cb_saveInputPath(Address, Address);
	static void cb_saveOutputPath(Address, Address);
	static void cb_selectionSort(Address, Address);
	static void cb_heapSort(Address, Address);
	static void cb_destination(Address, Address);
	static void cb_departureTime(Address, Address);
	static void cb_flightNumber(Address, Address);
	static void cb_gateNumber(Address, Address);
	static void cb_AZsort(Address, Address);
	static void cb_ZAsort(Address, Address);

	//deklaracija funkcija koje callback funkcije pozivaju
	void saveInputPath();
	void saveOutputPath();
	void selectionSort();
	void heapSort();
	void destinationFun();
	void departureTimeFun();
	void flightNumberFun();
	void gateNumberFun();
	void AZsort();
	void ZAsort();

	//deklaracija ostalih funkcija clanica
	void writeInputPath();
	void writeOutputPath();
	void chooseSortMethod();
	void chooseOrder();
	void chooseParameter();
};

