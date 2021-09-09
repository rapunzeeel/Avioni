//============================================================================
// Name        : Sort.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 08.01.2021.
// Copyright   : 
// Description : Implementation of the sort classes
//============================================================================

#include "Sort.h"
#include "Flight.h"
#include <iostream>
#include <map>

using namespace std;

//implementacija resetovanja brojanja
void Sort::resetNumCmps() {

	numCmps = 0;
}
void Sort::resetNumberOfSwap() {

	numberOfSwap = 0;
}
void Sort::resetNumberOfIteration() {

	numberOfIteration = 0;
}

//geteri za brojanje
unsigned long Sort::getNumCmps() {
	return numCmps;
}
int Sort::getNumberOFSwap() {
	return numberOfSwap;
}
int Sort::getNumberOfIteration() {
	return numberOfIteration;
}

//implementacija konstruktora i destruktora
SortDTO::SortDTO() {}
SortDTO::~SortDTO(){}
//implementacija setera
void SortDTO::setNumCmps(int number)
{
	numCmps = number;
}
void SortDTO::setNumOfSwap(int number) {
	numberOfSwap = number;
}
void SortDTO::setNumOfIter(int number) {
	numberOfIteration = number;
}
void SortDTO::setListOfFlight(vector<Flight>& list) {
	listOfFlight = list;
}
void SortDTO::setListOfParameter(vector<vector<string>>& list) {
	listOfParameter = list;
}
//implementacija getera
int SortDTO::getNumCmps() {
	return numCmps;
}
int SortDTO::getNumofSwap() {
	return numberOfSwap;
}
int SortDTO::getNumOfIter() {
	return numberOfIteration;
}
vector<Flight>& SortDTO::getListOfFlight() {
	return listOfFlight;
}
vector<vector<string>>& SortDTO::getListOfParameter() {
	return listOfParameter;
}

int Sort::compare(int criteria, Flight f1, Flight f2) {
	if (criteria == 1) {
		return f1.getDestination().compare(f2.getDestination());

	}
	if (criteria == 2) {
		return f1.getDeparture().compare(f2.getDeparture());

	}
	if (criteria == 3) {
		return f1.getFlightNo().compare(f2.getFlightNo());

	}
	if (criteria == 4) {
		return f1.getGateNo().compare(f2.getGateNo());

	}

}
//funkcija koja cuva listu letova - tj pojedinacnu listu izabranog parametra za sortiranje u jednoj iteraciji
vector<string> saveListOfChange(vector<Flight>&list, int parameter) {
	vector<string> listOfChange;
	for (int j = 0; j < 10; j++) {
		switch (parameter)
		{
		case 1://ako je izabrani parametar destinacija
			listOfChange.push_back(list.at(j).getDestination());
			break;
		case 2://ako je izabrani parametar vreme
			listOfChange.push_back(list.at(j).getDeparture());
			break;
		case 3://ako je izabrani parametar broj leta
			listOfChange.push_back(list.at(j).getFlightNo());
			break;
		case 4://ako je izabrani parametar broj izlaza
			listOfChange.push_back(list.at(j).getGateNo());
			break;
		default:
			break;
		}
	}
	return listOfChange; 
}

// sortiranje vremena
SortDTO SelectionSort::sortTime(vector<Flight>&data, int parameter, int order) {
	//resetovanje brojaca
	resetNumCmps();
	resetNumberOfSwap();
	resetNumberOfIteration();

	Flight temp;
	SortDTO sortDTO;
	vector<vector<string>>listOfChange;
	int min;
	listOfChange.push_back(saveListOfChange(data, parameter)); //cuvanje promene parametra u iteraciji
	for (int i = 0; i < data.size()-1; i++) {
		numberOfIteration += 1; //povecavanje broja iteracija
		min = i;
		for (int j = i + 1; j < data.size(); j++) {
			//deljenje stringa po :
			int pos1 = data.at(i).getDeparture().find(":");
			int pos2 = data.at(j).getDeparture().find(":");
			//formiranje satnice - deo pre :
			int hour1 = stoi(data.at(i).getDeparture().substr(0, pos1));
			int hour2 = stoi(data.at(j).getDeparture().substr(0, pos2));
			//formiranje minuta - deo posel :
			int minute1 = stoi(data.at(i).getDeparture().substr(pos1 + 1, pos1 + 3));
			int minute2 = stoi(data.at(j).getDeparture().substr(pos2 + 1, pos2 + 3));
			if (order == 0) { //provera koji je poredak - ako je AZ - od manje do vece satnice
				if (hour1 > hour2) {
					numberOfSwap += 1; //povecavanje broja zamena
					//zamena mesta elementima
					min = j;
				}
				else if (hour1 == hour2) { // ukoliko su sati iste provericemo minute
					if (minute1 > minute2) {
						numberOfSwap += 1;
						min = j;
					}
				}
			}
			else //poredak - ako je ZA - od vece do manje satnice
			{
				if (hour1 < hour2) {
					numberOfSwap += 1;
					min = j;
				}
				else if (hour1 == hour2) {// ukoliko su sati iste provericemo minute
					if (minute1 < minute2) {
						numberOfSwap += 1;
						min = j;
					}
				}
			}
			numCmps++; //povecavanje broja poredjenja
		}
		temp = data.at(i);
		data.at(i) = data.at(min);
		data.at(min) = temp;
		listOfChange.push_back(saveListOfChange(data, parameter)); //cuvanje promene parametra u iteraciji
	}
	//setovanje atributa DTO objekta
	sortDTO.setListOfFlight(data);
	sortDTO.setListOfParameter(listOfChange);
	sortDTO.setNumCmps(getNumCmps());
	sortDTO.setNumOfIter(getNumberOfIteration());
	sortDTO.setNumOfSwap(getNumberOFSwap());
	return sortDTO; //vracanje DTO objekta
}
SortDTO SelectionSort::sortString(vector<Flight>&data, int parameter, int order) {
	//resetovanje brojaca
	resetNumCmps();
	resetNumberOfSwap();
	resetNumberOfIteration();

	Flight temp;
	SortDTO sortDTO;
	vector<vector<string>>listOfChange;
	int min;

	listOfChange.push_back(saveListOfChange(data, parameter));

	for (int i = 0; i < data.size() - 1; i++) {
		numberOfIteration += 1; //povecavanje broja iteracija
		min = i;
		for (int j = i + 1; j < data.size(); j++) {
			if (order == 0) { //AZ poredak
				if (compare(parameter, data[j], data[min]) < 0) { //poredjenje aviona u AZ poretku
					min = j;
				}
			numCmps++; //povecavanje broja poredjenja
			}
			else if (order == 1) {
				if (compare(parameter, data[j], data[min]) > 0) { //poredjenje aviona u ZA poretku
					min = j;

				}
				numCmps++;
			}
		}
		if (data[i].getFlightNo().compare(data[min].getFlightNo())) {
			numberOfSwap++;
		}
		temp = data.at(i);
		data.at(i) = data.at(min);
		data.at(min) = temp;
		listOfChange.push_back(saveListOfChange(data, parameter));//cuvanje promene parametra u iteraciji
		
	}
	//setovanje atributa DTO objekta
	sortDTO.setListOfFlight(data);
	sortDTO.setListOfParameter(listOfChange);
	sortDTO.setNumCmps(getNumCmps());
	sortDTO.setNumOfIter(getNumberOfIteration());
	sortDTO.setNumOfSwap(getNumberOFSwap());
	return sortDTO; //vracanje DTO objekta
}
SortDTO SelectionSort::sort(vector<Flight>&data, int parameter, int order) {
	SortDTO sortDTO;
	if (parameter == 2) { //ukoliko je paramatera vreme 
		sortDTO = sortTime(data, parameter, order); //sortiranje vremena
	}
	else
	{
		sortDTO = sortString(data, parameter, order);// sortiranje ostalih parametara
	}
	//sortDTO = sortString(data, parameter, order);// sortiranje ostalih parametara
	return sortDTO; //vracanje DTO objekta
}





int compareFlightHeap(const Flight& flightI, const Flight& flightJ, int parameter) {
	//deljenje stringa po :
	int pos1Heap = flightI.getDeparture().find(":");
	int pos2Heap = flightJ.getDeparture().find(":");
	//formiranje satnice - deo pre :
	int hour1Heap = stoi(flightI.getDeparture().substr(0, pos1Heap));
	int hour2Heap = stoi(flightJ.getDeparture().substr(0, pos2Heap));
	//formiranje minuta - deo posle :
	int minute1Heap = stoi(flightI.getDeparture().substr(pos1Heap + 1, pos1Heap + 3));
	int minute2Heap = stoi(flightJ.getDeparture().substr(pos2Heap + 1, pos2Heap + 3));

	switch (parameter)
	{
	case 1://poredjenje parametara ako su destinacije
		if (flightI.getDestination() > flightJ.getDestination()) {
			return 1; //1 je AZ poredak
		}
		return -1; //-1 je ZA poredak
	case 2: //poredjenje parametara ako je vreme
		if (hour1Heap > hour2Heap) {
			return 1;
		}
		else if (hour1Heap == hour2Heap) {
			if (minute1Heap > minute2Heap) {
				return 1;
			}
		}
		if (hour1Heap < hour2Heap) {
			return -1;
		}
		else if (hour1Heap == hour2Heap) {
			if (minute1Heap < minute2Heap) {
				return -1;
			}
		}
		return -1;
	case 3://poredjenje parametara ako je broj leta
		if (flightI.getFlightNo() > flightJ.getFlightNo()) {
			return 1;
		}
		return -1;
	case 4: //poredjenje parametara ako je broj izlaza
		if (flightI.getGateNo() > flightJ.getGateNo()) {
			return 1;
		}
		return -1;
	default:
		break;
	}
	return -1;
}

//implementacija konstruktora i destruktora 
Heap::Heap(vector<Flight>& list, int parameter, int orderAZ) : list(list), HeapSize(list.size()), sortParameter(parameter), order(orderAZ)
{
	// odabir koji je poredak
	if (orderAZ == 0) {
		order = 1;
	}
	else {
		order = -1;
	}
	buildMaxHeap();//implementacija funkcije koja pravi heap
}

Heap::~Heap()
{
}
//implentacija funkcije koja daje indeks levog deteta
int Heap::left(int index) {
	return 2 * index + 1; //racunanje indeks levog deteta
}
//implentacija funkcije koja daje indeks desnog deteta
int Heap::right(int index) {
	return 2 * index + 2;//racunanje indeksa desnog deteta
}
//implementacija funkcije koja menja mesta elemntima u heap-u
void Heap::swap(int index1, int index2) {
	Flight temp = list.at(index1);
	list.at(index1) = list.at(index2);
	list.at(index2) = temp;
	numberOfSwap += 1;//povecavanje broja zamene elemenata
	//cout << numberOfSwap << " Iteracija broj: " << numberOfIteration << endl;
}
//implementacija funkcije koja izvrsava downheap i unheap
void Heap::maxHeapify(int node_index) {
	int largest;
	int left_node = left(node_index); //indeks levog deteta
	int right_node = right(node_index); //indeks desnog deteta

	if ((left_node < HeapSize) && (compareFlightHeap(list.at(left_node), list.at(node_index), sortParameter) == order)) { //provera da li je levo dete vece
		largest = left_node;
		numCmps += 1;//povecavanje broja poredjenja
	}
	else
	{
		largest = node_index;
		numCmps += 1;
	}
	if ((right_node < HeapSize) && (compareFlightHeap(list.at(right_node), list.at(largest), sortParameter) == order)) { //provera da li je desno dete vece
		largest = right_node;
		numCmps += 1;
	}
	else
	{
		numCmps += 1;
	}
	// zameni vrednosti ako nisu u max-heap redosledu
	if (largest != node_index) {
		swap(node_index, largest);
		maxHeapify(largest);
	}

}
//implementacija funkcije koja vrši formiranje max heapa
void Heap::buildMaxHeap() {
	int start = (HeapSize - 1) / 2;
	for (int i = start; i > -1; i--) {
		maxHeapify(i);
	}
}

SortDTO Heap::sort(vector<Flight>& data, int parameter, int orderAZ) {
	//resetovanje brojaca
	resetNumCmps();
	resetNumberOfSwap();
	resetNumberOfIteration();

	SortDTO sortDTO;
	sortParameter = parameter;
	//odabir poredka
	if (orderAZ == 0) {
		order = 1;
	}
	else {
		order = -1;
	}
	// heap sort algoritam
	for (int i = HeapSize - 1; i > 0; i--) {
		numberOfIteration += 1; // povecava se broj iteracija
		listOfChange.push_back(saveListOfChange(list, sortParameter)); //cuvanje promene parametra u iteraciji
		swap(0, i); // zameni prvi i poslednji 
		HeapSize--; //izbaci poslednji sa heap-a
		maxHeapify(0); //preostale elemente transformiši u max-heap
		
	}
	listOfChange.push_back(saveListOfChange(list, sortParameter)); //cuvanje poslednje promene
	
	//setovanje atributa DTO objekta
	sortDTO.setListOfFlight(data);
	sortDTO.setListOfParameter(listOfChange);
	sortDTO.setNumCmps(getNumCmps());
	sortDTO.setNumOfIter(getNumberOfIteration());
	sortDTO.setNumOfSwap(getNumberOFSwap());
	return sortDTO;//vracanje DTO objekta
}
