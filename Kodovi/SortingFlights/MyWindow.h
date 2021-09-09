//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description :  GUI prozor - odabir podrazumevanih parametara ili ih sam korisnik unosi
//============================================================================
#pragma once
#include "GUI.h"    
#include "Graph.h"
#include "Window.h"

using namespace Graph_lib;

struct MyWindow : Window {
	//deklaracija konstruktora i destruktora
	MyWindow(Point xy, int width, int height, const string& title, char *argv[]);
	~MyWindow();
private:
	string inputPath;
	string outputPath;

	//deklaracija dugmica
	Button defaultButton;
	Button chooseButton;

	//deklaracija bool vrednosti za dugmice, za proveru da li su pritisnuti
	bool defaultButtonPushed;
	bool chooseButtonPushed;

	//deklaracija callback funkcija
	static void cb_default(Address, Address);
	static void cb_choose(Address, Address);

	//funkcije koje poziva callback
	void defaultParameter();
	void chooseParameter();

	//funkcija za odabir prametara - podrazumevani ili korisnik unosi sam
	void chooseModeOfInteraction();
};