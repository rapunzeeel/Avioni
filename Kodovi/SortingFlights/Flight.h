//============================================================================
// Name        : Flight.h
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : Deklaracije klase Flight
//============================================================================
#pragma once
#include "std_lib_facilities.h"

class Flight
{
private: //atributi klase
	string destination;
	string departure;
	string flightNo;
	string gateNo;

public:
	//deklaracija getera za atribute
	string getDestination() const;
	string getDeparture() const;
	string getFlightNo() const;
	string getGateNo() const;
	//deklaracija setera za atribute
	void setDestination(string destination);
	void setDeparture(string departure);
	void setFlightNo(string flightNo);
	void setGateNo(string gateNo);

	//deklaracija konstruktora i destruktora
	Flight();
	Flight(string destination, string departure, string flightNo, string gateNo);
	~Flight();

	//deklaracija funkcija za ispis i upis letova
	friend istream& operator >> (istream& is, Flight& flight);
	friend ostream & operator <<(std::ostream & output, Flight const& s);
};
