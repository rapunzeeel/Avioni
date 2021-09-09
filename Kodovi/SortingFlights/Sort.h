//============================================================================
// Name        : Sort.h
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   : 
// Description : Sort interface class and various sorting algorithms in C++
//============================================================================
#pragma once

#include "Flight.h"
#include <vector>
#include <map>


//deklaracija DTO klase
class SortDTO {
private: //atributi DTO klase - sluzi samo za prenos obradjenih podataka u GUI klase
	unsigned long numCmps; 
	int numberOfSwap;
	int numberOfIteration;
	vector<Flight> listOfFlight;
	vector<vector<string>> listOfParameter;
public:
	//deklaracija konstruktora i destruktora
	SortDTO();
	~SortDTO();

	//deklaracija setera
	void setNumCmps(int number);
	void setNumOfSwap(int number);
	void setNumOfIter(int number);
	void setListOfFlight(vector<Flight>& list);
	void setListOfParameter(vector<vector<string>>& list);
	//deklaracija getera
	int getNumCmps();
	int getNumofSwap();
	int getNumOfIter();
	vector<Flight>& getListOfFlight();
	vector<vector<string>>& getListOfParameter();


};
// Sort class
class Sort
{
protected:
	// number of comparisons performed in sort function
	unsigned long numCmps; //broj poredjenja
	int numberOfSwap; //broj zamena elemenata
	int numberOfIteration; //broj iteracija
public:
	// main entry point
	virtual SortDTO sort(std::vector<Flight>& data, int parametar, int order) = 0;
	// returns number of comparisons, iteration, swap
	unsigned long getNumCmps(); 
	int getNumberOFSwap();
	int getNumberOfIteration();
	// resets the number of comparisons, iteration, swap
	void resetNumCmps();
	void resetNumberOfSwap();
	void resetNumberOfIteration();

	int compare(int criteria, Flight f1, Flight f2);
};

// SelectionSort class
class SelectionSort : public Sort
{
public:
	// sortira vreme
	SortDTO sortTime(vector<Flight>&data, int parameter, int order);
	// sortira ostale atribute klase Flight
	SortDTO sortString(vector<Flight>&data, int parameter, int order);
	//deklaracija funkcije koja ce implementirati apstraktnu funkciju iz klase Sort 
	SortDTO sort(std::vector<Flight>& data, int parameter, int order);
};

class Heap: public Sort
{
private:
	vector<Flight>& list;//lista u kojoj se vrse promene prilikom sortiranja
	vector<vector<string>>listOfChange;//lista u kojoj se cuvaju promene
	//duzina heap-a
	int HeapSize;
	int sortParameter; //po kom parametru se sortira
	int order; //u kom poretku se sortira

public:
	//deklaracija kostruktora i destruktora
	Heap(vector<Flight>&list, int parameter, int order);
	~Heap();

	//deklaracija funkcije koja vraca indeks levog deteta
	int left(int index);
	//deklaracija funkcije koja vraca indeks desnog deteta
	int right(int index);
	//deklaracija funkcije koja menja elemente u heap-u
	void swap(int index1, int index2);
	//deklaracija funkcije koja izvrsava downheap ili unheap
	void maxHeapify(int index_node);
	//deklaracija funkcije koja pravi heap
	void buildMaxHeap();
	//deklaracija funkcije koja ce implementirati apstraktnu funkciju iz klase Sort 
	SortDTO sort(vector<Flight>& data, int parameter, int order);
};


