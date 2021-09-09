//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : GUI prozor - u kome korisnik unosi parametre za dortiranje, ulazne i izlazne putanje - implementacija
//============================================================================
#include "ChooseWindow.h"
#include "DisplayWindow.h"
#include "Sort.h"

ChooseWindow::ChooseWindow(Point xy, int width, int height, const string& title, char *argv[]) :
	Window(xy, width, height, title),
	saveInputPathButton(Point(200, 90), 90, 30, "Sacuvaj", cb_saveInputPath),
	saveOutputPathButton(Point(200, 90), 90, 30, "Sacuvaj", cb_saveOutputPath),
	selectionSortButton(Point(200, 90), 120, 30, "Selection sort", cb_selectionSort),
	heapSortButton(Point(60, 90), 120, 30, "Heap sort", cb_heapSort),
	destinationButton(Point(80, 90), 120, 30, "Destinacija", cb_destination),
	departureTimeButton(Point(80, 140), 120, 30, "Vreme", cb_departureTime),
	flightNumberButton(Point(220, 90), 120, 30, "Broj leta", cb_flightNumber),
	gateNumberButton(Point(220, 140), 120, 30, "Broj izlaza", cb_gateNumber),
	inputPathBox(Point(40, 90), 120, 30, ""),
	outputPathBox(Point(40, 90), 120, 30, ""),
	AZsortButton(Point(200, 70), 120, 30, "A-Z poredak", cb_AZsort),
	ZAsortButton(Point(30, 70), 120, 30, "Z-A poredak", cb_ZAsort)

{
	//postavljanje prvog prikaza u prozoru
	color(Color::white);

	Image* image = new Image(Point(380, 5), "slika3.jpg", Suffix::none);
	attach(*image);

	attach(saveInputPathButton);
	attach(inputPathBox);
	//unos ulazne putanje od strane korisnika
	writeInputPath();

	delete(image);

}
ChooseWindow::~ChooseWindow() {
}
//implementacija callback funkcija
void ChooseWindow::cb_saveInputPath(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).saveInputPath();
}
void ChooseWindow::cb_saveOutputPath(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).saveOutputPath();
}
void ChooseWindow::cb_selectionSort(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).selectionSort();
}
void ChooseWindow::cb_heapSort(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).heapSort();
}
void ChooseWindow::cb_destination(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).destinationFun();
}
void ChooseWindow::cb_departureTime(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).departureTimeFun();
}
void ChooseWindow::cb_flightNumber(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).flightNumberFun();
}
void ChooseWindow::cb_gateNumber(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).gateNumberFun();
}
void ChooseWindow::cb_AZsort(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).AZsort();
}
void ChooseWindow::cb_ZAsort(Address, Address pw)
{
	reference_to<ChooseWindow>(pw).ZAsort();
}
//implementacija funkcija koje callback pozivaju - menjanje bool vrednosti dugmica
void ChooseWindow::saveInputPath()
{
	saveInputPathPushed = true;
}
void ChooseWindow::saveOutputPath() {

	saveOutputPathPushed = true;
}
void ChooseWindow::selectionSort()
{
	selectionSortPushed = true;
}
void ChooseWindow::heapSort()
{
	heapSortPushed = true;
}
void ChooseWindow::destinationFun()
{
	destinationPushed = true;
}
void ChooseWindow::departureTimeFun()
{
	departureTimePushed = true;
}
void ChooseWindow::flightNumberFun()
{
	flightNumberPushed = true;
}
void ChooseWindow::gateNumberFun()
{
	gateNumberPushed = true;
}
void ChooseWindow::AZsort()
{
	AZsortPushed = true;
}
void ChooseWindow::ZAsort()
{
	ZAsortPushed = true;
}
//funkcija u kojoj se preuzima unesena ulazna putanja
void ChooseWindow::writeInputPath()
{
	Text *textInput = new Text(Point(30, 50), "~ Unesite ulazni fajl (bez ekstenzije) : ");
	textInput->set_color(Color::black);
	textInput->set_font(Font::helvetica);
	attach(*textInput);

	show();
	while (true) {
		saveInputPathPushed = false;

		while (!saveInputPathPushed) Fl::wait();

		if (saveInputPathPushed) {
			//preuzimanje ulzazne putanje
			inputPath = inputPathBox.get_string();
			//menjanje izgleda prozora
			detach(inputPathBox);
			detach(saveInputPathButton);
			detach(*textInput);
			attach(saveOutputPathButton);
			attach(outputPathBox);

			delete(textInput);//oslobadjenje memorije

			writeOutputPath();
		}
	}
}
//funkcija u kojoj se preuzima izlazna putanja
void ChooseWindow::writeOutputPath() {
	Text *textInput = new Text(Point(10, 20), "! Prethodno se uneli neispravan fajl, bice uzet podrazumevani !");
	textInput->set_color(Color::dark_red);
	textInput->set_font(Font::helvetica);
	//provera da li je ulazna putanja ista kao i putanja iz komadnih argumenata
	if (inputPath != "inputFileExample") {
		//ukoliko nije bice ispisana poruka, uzima se podrazumevana putanja
		attach(*textInput);
		inputPath = __argv[1];
	}

	//ispis teksta
	Text *textOutput = new Text(Point(30, 50), "~ Unesite izlazni fajl (bez ekstenzije) : ");
	textOutput->set_color(Color::black);
	textOutput->set_font(Font::helvetica);
	attach(*textOutput);

	while (true) {
		saveOutputPathPushed = false;

		while (!saveOutputPathPushed) Fl::wait();

		if (saveOutputPathPushed) {
			//preuzimanje imena izlazne putanje 
			outputPath = outputPathBox.get_string();
			//promena izgleda prozora
			detach(saveOutputPathButton);
			detach(*textOutput);
			detach(outputPathBox);
			detach(*textInput);

			attach(selectionSortButton);
			attach(heapSortButton);

			//oslobadjenje memorije
			delete(textInput);
			delete(textOutput);

			chooseSortMethod();
		}
	}
}
//funkcija u kojoj se preuzima izabrani metod za sortiranje
void ChooseWindow::chooseSortMethod() {
	//postavljanje teksta
	Text *textSort = new Text(Point(30, 50), "~ Izaberite metod sortiranja: ");
	textSort->set_color(Color::black);
	textSort->set_font(Font::helvetica);
	attach(*textSort);
	//postavljanje slika
	Image* image1 = new Image(Point(80, 130), "heap.jpg", Suffix::none);
	attach(*image1);
	Image* image2 = new Image(Point(210, 130), "selection sort.jpg", Suffix::none);
	attach(*image2);

	while (true) {
		selectionSortPushed = false;
		heapSortPushed = false;

		while (!selectionSortPushed && !heapSortPushed) Fl::wait();

		//postavljanje parametra sort na odgovarajucu vrednost na osnovu enumeracije
		if (selectionSortPushed) {
			sort = sort::selction;
		}
		else if (heapSortPushed) {
			sort = sort::heap;
		}
		if (selectionSortPushed || heapSortPushed) {
			//menjanje izgleda prozora
			detach(*textSort);
			detach(selectionSortButton);
			detach(heapSortButton);
			detach(*image1);
			detach(*image2);

			attach(AZsortButton);
			attach(ZAsortButton);

			//oslobadjenje memorije
			delete(image1);
			delete(image2);
			delete(textSort);

			chooseOrder();
		}
	}
}
//funkcija u kojoj se bira poredak sortiranja
void ChooseWindow::chooseOrder() {
	//postavljanje teksta
	Text *textSort = new Text(Point(30, 40), "~ Izaberite poredak sortiranja: ");
	textSort->set_color(Color::black);
	textSort->set_font(Font::helvetica);
	attach(*textSort);

	//postavljanje slika
	Image* image1 = new Image(Point(70, 110), "sortZA.jpg", Suffix::none);
	attach(*image1);
	Image* image2 = new Image(Point(210, 110), "sortAZ.jpg", Suffix::none);
	attach(*image2);

	while (true) {
		AZsortPushed = false;
		ZAsortPushed = false;

		while (!AZsortPushed && !ZAsortPushed) Fl::wait();
		//na osnovu pritisnutih dugmica postavlja se vrednost parametra za poredan=k na osnovu enumeracije
		if (AZsortPushed) {
			orderParameter = order::AZ;
		}
		else if (ZAsortPushed) {
			orderParameter = order::ZA;
		}
		if (AZsortPushed || ZAsortPushed) {
			// menjanje izgleda prozora
			detach(AZsortButton);
			detach(ZAsortButton);
			detach(*textSort);
			detach(*image1);
			detach(*image2);


			attach(departureTimeButton);
			attach(destinationButton);
			attach(flightNumberButton);
			attach(gateNumberButton);

			//oslobadjenje memorije
			delete(image1);
			delete(image2);
			delete(textSort);

			chooseParameter();
		}
	}
}
//funkcija za biranja kriterijuma po kome ce se sortirati
void ChooseWindow::chooseParameter() {
	//postavljanje teksta
	Text *textParameter = new Text(Point(30, 30), "~ Izaberite parametar sortiranja: ");
	textParameter->set_color(Color::black);
	textParameter->set_font(Font::helvetica);
	attach(*textParameter);

	//postavljenje slika
	Image* image2 = new Image(Point(10, 60), "mesto.jpg", Suffix::none);
	attach(*image2);
	Image* image1 = new Image(Point(10, 140), "vreme.jpg", Suffix::none);
	attach(*image1);
	Image* image3 = new Image(Point(360, 100), "skener.jpg", Suffix::none);
	attach(*image3);

	while (true) {
		destinationPushed = false;
		departureTimePushed = false;
		flightNumberPushed = false;
		gateNumberPushed = false;

		while (!destinationPushed && !departureTimePushed && !flightNumberPushed && !gateNumberPushed) Fl::wait();
		//postavljanje vrednosti parameter na osnovu enumeracije
		if (destinationPushed) {
			parameter = parameter::destination;
		}
		else if (departureTimePushed) {
			parameter = parameter::depatureTime;
		}
		else if (flightNumberPushed) {
			parameter = parameter::flightNumber;
		}
		else if (gateNumberPushed) {
			parameter = parameter::gateNumber;
		}
		if (destinationPushed || departureTimePushed || flightNumberPushed || gateNumberPushed) {
			//sakrivanje prozora i pozivanje krajnjeg prozora za prikaz sortiranja
			hide();

			//oslobadjenje memorije
			delete(image1);
			delete(image2);
			delete(image3);
			delete(textParameter);

			DisplayWindow display(Point(50, 50), 1000, 550, "Sortirani letovi", parameter,sort, orderParameter,inputPath,outputPath); 
		}
	}
}