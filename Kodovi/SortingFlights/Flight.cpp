//============================================================================
// Name        : Flight.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   : 
// Description : Implementation of the Flight class
//============================================================================

#include "Flight.h"
#include "std_lib_facilities.h"
#include <iostream>
using namespace std;

//implementacija konstruktora i destruktora
Flight::Flight() : destination(""), departure(""), flightNo(""), gateNo("") {}
Flight::Flight(string destination, string departure, string flightNo, string gateNo) : destination(destination), departure(departure), flightNo(flightNo), gateNo(gateNo) {}
Flight::~Flight() {

}
//implementacija getera
string Flight::getDestination() const
{
	return destination;
}
string Flight::getDeparture() const
{
	return departure;
}
string Flight::getFlightNo() const
{
	return flightNo;
}
string Flight::getGateNo() const
{
	return gateNo;
}
//implementacija setera
void Flight::setDestination(string d)
{
	destination = d;
}
void Flight::setDeparture(string d)
{
	departure = d;
}
void Flight::setFlightNo(string f)
{
	flightNo = f;
}
void Flight::setGateNo(string g)
{
	gateNo = g;
}
//implementacija za citanje letova
istream& operator >> (istream& is, Flight& flight) {
	char tmp;

	is >> noskipws;

	getline(is, flight.getDestination(), ';');
	is >> tmp;
	getline(is, flight.getDeparture(), ';');
	is >> tmp;
	getline(is, flight.getFlightNo(), ';');
	is >> tmp;
	getline(is, flight.getGateNo(), ';');
	return is;


}
//implementacija za pisanje letova
ostream & operator <<(std::ostream & output, Flight const& s)
{
	output << s.getFlightNo() + ";" + s.getDestination() + ";" + s.getDeparture() + ";" + s.getGateNo() + ";\n";

	return output;
}

