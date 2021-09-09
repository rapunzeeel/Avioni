//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : Pokretanje aplikacije
//============================================================================
#include "MyWindow.h"
#include "DisplayWindow.h"

#include "Flight.h"
#include "FileWork.h"


int main(int argc, char* argv[])
{	
	if (argc == 1) {
		//izvrsava se prozor sa krajnjim rezultatima uz podrazumevane parametre
		DisplayWindow display(Point(50, 50), 1000, 550, "Sortirani letovi",(int) argv[3], (int)argv[4], (int)argv[5], argv[1],argv[2]);
		return 0;
	}
	else {
		//izvrsava se porozor u kojem korisnik ima mogucnost da bira
		MyWindow win(Point(100, 200), 500, 200, "Pocetni meni", argv);
	}
	return 0;
} 
