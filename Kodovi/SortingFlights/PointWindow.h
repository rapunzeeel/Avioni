//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 08.01.2021.
// Copyright   :
// Description : GUI prozor - u kome se korisniku prikazuje rezultat sortiranja (tackice)
//============================================================================
#pragma once
#include "GUI.h"   
#include "Graph.h"
#include "Window.h"
#include "Flight.h"

using namespace Graph_lib;

struct PointWindow : Window {
	//deklaracija konstruktora i destruktora
	PointWindow(Point xy, int width, int height, const string& title, int parameter, int sort, int orderParameter);
	~PointWindow();
	enum sort { selction, heap };
	
private:

	//deklaracija dugmeta
	Button quitButton;

	//deklaracija bool vresnosti za dugme
	bool quitPushed;

	//deklaracija callback funkcije
	static void cb_quit(Address, Address);

	//deklaracija funkcije koje pozivaja callback
	void quit();

	//deklaracija funkcija koje iscrtavaju elemente prozora
	void drawWindow(Vector_ref<Line>& listOfLine, Vector_ref<Mark>&listOfMark, vector<vector<string>>listOfChange, int i);
	void drawLine(vector<vector<int>> listOfIndex, int i, int j, Vector_ref<Line>& listOfLine);
	vector<vector<int>> compareFlight(vector<string> list1, vector<string> list2);
};