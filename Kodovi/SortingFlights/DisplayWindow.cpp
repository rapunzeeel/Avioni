//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 08.01.2021.
// Copyright   :
// Description : GUI prozor - u kome se korisniku prikazuje rezultat sortiranja - implementacija
//============================================================================
#include "DisplayWindow.h"
#include "Sort.h"
#include "FileWork.h"
#include "ChooseWindow.h"
#include "PointWindow.h"


DisplayWindow::DisplayWindow(Point xy, int width, int height, const string& title, int parameter, int sort, int orderParameter,string inputPath, string outputPath) :
	Window(xy, width, height, title),
	quitButton(Point(800, 500), 120, 30, "Zavrsi", cb_quit),
	nextButton(Point(660, 500), 120, 30, "Sledeca iteracija", cb_next),
	returnButton(Point(520, 500), 120, 30, "Sortiraj opet", cb_return),
	pointButton(Point(380, 500), 120, 30, "Tackasti prikaz", cb_point)
{
	//postavljanje prozora
	color(Color::white);
	attach(quitButton);
	//iscrtavanje ivica za tabelu
	Graph_lib::Rectangle rect(Point(20, 10), 310, 200);
	attach(rect);
	//iscrtavanje linije koja odvaja naslov od sortiranih letova
	Graph_lib::Line line(Point(20, 32), Point(328, 32));
	attach(line);
	attach(nextButton);
	attach(returnButton);
	attach(pointButton);
	sortMethod = sort;
	//funkcija za prikaz sortiranja
	displayFun(parameter, sort, orderParameter, inputPath, outputPath);
}
DisplayWindow::~DisplayWindow() {

}
//implementacija callback funkcija
void DisplayWindow::cb_quit(Address, Address pw)
{
	reference_to<DisplayWindow>(pw).quit();
}
void DisplayWindow::cb_next(Address, Address pw)
{
	reference_to<DisplayWindow>(pw).next();
}
void DisplayWindow::cb_return(Address, Address pw)
{
	reference_to<DisplayWindow>(pw).returnFunc();
}
void DisplayWindow::cb_point(Address, Address pw)
{
	reference_to<DisplayWindow>(pw).point();
}
//implementacija funkcija koje poziva callback funkcije
void DisplayWindow::quit() //sakrivanje prozora tj.zavrsetak
{
	quitPushed = true;
	hide();
	exit(0);
}
void DisplayWindow::returnFunc() //sakrivanje ovog prozora i pozivanje prozora za ponovni odabir parametara za sortiranje
{
	returnPushed = true;
	hide();
	ChooseWindow choose(Point(100, 100), 500, 200, "Izbori", __argv);
}
void DisplayWindow::next() {// funkcija za prikaz sledece iteracije kod sortiranja
	//l i m gde ce se nalaziti tekst po x,y koordinati
	int l = 280;
	m += 90;
	//vector u kome se nalaze svi ucitani letovi
	vector<Flight>list = FileWork().readInputFile(inputFile);
	//DTO objekat 
	SortDTO sortDTO;
	//formiranje DTO objekta na osnovu sorta koji je izabran
	if (sortMethod == sort::selction) {
		sortDTO = SelectionSort().sort(list, sortParametar, orderParameter1);
	}
	else if (sortMethod == sort::heap) {
		sortDTO = Heap(list, sortParametar, orderParameter1).sort(list, sortParametar, orderParameter1);
	}
	//vektor u kome se nalise vektori sa pojedinacnim elementima u iteracijama - samo parametar koji je izabran da se dortira
	vector<vector<string>>listOfChange = sortDTO.getListOfParameter();

	//ukoliko je broj iteracija veci ili jednak sa duzinom liste promena bice zaustavljeno ispisivanje jer smo dosli
	//do kraja liste
	if (numberOfIteration >= listOfChange.size()) {
		nextPushed = true;
		detach(nextButton);
		return;
	}
	//ispisivanje elemenata iz liste u odredjenoj iteraciji
	for (int j = 0; j < 10; j++) {
		//ukoliko je element drugaciji u odnosu na prethodnu listu bice obojen
		if (listOfChange.at(numberOfIteration).at(j) != listOfChange.at(numberOfIteration + 1).at(j)) {
			Text *textParameter1;
			textParameter1 = new Text(Point(m, l), "|" + listOfChange.at(numberOfIteration + 1).at(j));
			textParameter1->set_color(Color::dark_blue);
			textParameter1->set_font(Font::helvetica);
			textParameter1->set_font_size(10);
			attach(*textParameter1);
		}
		//ako nije ostaje crn
		else
		{
			Text *textParameter2;
			textParameter2 = new Text(Point(m, l), "|" + listOfChange.at(numberOfIteration).at(j));
			textParameter2->set_color(Color::black);
			textParameter2->set_font(Font::helvetica);
			textParameter2->set_font_size(10);
			attach(*textParameter2);
		}
		l += 20;
	}
	//povecavanja broja iteracije
	numberOfIteration++;
	if (numberOfIteration >= listOfChange.size()-1) {
		nextPushed = true;
		detach(nextButton);
		return;
	}
	redraw();
}
void DisplayWindow::point()
{
	//iscrtavanje tackica
	pointPushed = true;
	if (sortMethod == sort::selction) {
		PointWindow point(Point(100, 100), 800, 300, "Tackasti prikaz", sortParametar, sortMethod, orderParameter1);
	}
}
//funkcija za prikaz sortiranih elemenata
void DisplayWindow::displayFun(int parameter, int sort, int order, string inputPath, string outputPath) {
	sortParametar = parameter;
	orderParameter1 = order;
	inputFile = inputPath;
	sortMethod = sort;
	vector<vector<string>>listOfChange;
	vector<Flight>listOfFlight;
	//ucitavanje letova iz ulaznog fajla
	vector<Flight>list = FileWork().readInputFile(inputPath + ".txt");

	//formiranje DTO objekta na osnovu izabranog metoda za sortiranje 
	if (sort == sort::selction) {
		SortDTO sortDTO = SelectionSort().sort(list, parameter, orderParameter1);
		listOfChange = sortDTO.getListOfParameter();
		listOfFlight = sortDTO.getListOfFlight();
		numberOfCompare = sortDTO.getNumCmps();
		numberOfIter = sortDTO.getNumOfIter();
		numberOfSwap = sortDTO.getNumofSwap();
	}
	else if (sort == sort::heap) {

		SortDTO sortDTO = Heap(list, parameter, orderParameter1).sort(list, parameter, orderParameter1); 
		listOfChange = sortDTO.getListOfParameter();
		listOfFlight = sortDTO.getListOfFlight();
		numberOfCompare = sortDTO.getNumCmps();
		numberOfIter = sortDTO.getNumOfIter();
		numberOfSwap = sortDTO.getNumofSwap();
	}
	//upisivanje sortiranih letova u izlazni fajl
	FileWork().writeOutputFile(outputPath + ".txt",listOfFlight);

	//funkcija koja ispisuje broj iteracija, pomeranja i promena na prozor
	displayNumberPrameters();
	
	//funkcija koja ispisuje sortirane letove u tabelu
	displayTable(parameter, listOfFlight);

	//funkcija ispisuje prvi red u iteraciji
	displayFirstTable(listOfChange);


	while (true) {
		returnPushed = false;
		pointPushed = false;

		while (!returnPushed) Fl::wait();

		//za povratak na ponovno biranje parametara za sortiranje
		if (returnPushed) {
			ChooseWindow choose(Point(100, 100), 500, 200, "Izbori", __argv);
		}
		//iscrtavanje tackica
		if (pointPushed) {
			PointWindow point(Point(100, 100), 500, 200, "Tackasti prikaz", sortParametar, sortMethod, orderParameter1);
		}
	}
	while (true) {
		quitPushed = false;

		while (!quitPushed) Fl::wait();

		//za izlazak iz aplikacije
		if (quitPushed) {
			hide();
		}
	}
}

void DisplayWindow::displayFirstTable(std::vector<std::vector<std::string>> &listOfChange)
{
	m = 20;
	int l = 280;
	//ispisivanje prvog reda sortiranog parametra
	for (int j = 0; j < 10; j++) {
		Text *textParameter = new Text(Point(m, l), "|" + listOfChange.at(0).at(j) + "            ");
		textParameter->set_color(Color::black);
		textParameter->set_font(Font::helvetica);
		textParameter->set_font_size(10);
		attach(*textParameter);
		l += 20;
	}

	//za dugme koje prikazuje sledece iteracije
	while (true) {
		nextPushed = false;
		while (!nextPushed) Fl::wait();
		if (numberOfIteration >= listOfChange.size()) {
			detach(nextButton);
		}
		if (nextPushed) {
		}
	}
}
void DisplayWindow::displayTable(int parameter, vector<Flight> &listOfFlight)
{
	//ispis zaglavlja tabele
	string heared[] = { " ", "Destinacija", "Vreme", "Broj leta", "Broj izlaza" };
	int x[] = { 0,30, 130, 190,260 };
	for (int i = 1; i < 5; i++) {
		string text = "| " + heared[i];
		Text *textParameter = new Text(Point(x[i], 25), text);
		//izabrani parametar ce se obojiti u plavo
		if (parameter == i) {
			textParameter->set_color(Color::dark_blue);
		}
		else
		{
			textParameter->set_color(Color::black);
		}
		textParameter->set_font(Font::helvetica);
		textParameter->set_font_size(12);
		attach(*textParameter);
	}
	//ispis poruke
	Text *textInput = new Text(Point(40, 230), "~ Prikaz tabele svih sortiranih letova!");
	textInput->set_color(Color::black);
	textInput->set_font(Font::helvetica);
	attach(*textInput);
	//ispis slika
	Image* image1 = new Image(Point(880, 2), "karte.jpg", Suffix::none);
	attach(*image1);
	Image* image2 = new Image(Point(400, 50), "putokazi.jpg", Suffix::none);
	attach(*image2);
	Image* image3 = new Image(Point(920, 450), "karta.jpg", Suffix::none);
	attach(*image3);

	//ispis tabele po redovima - izabrani parametar ce biti drugacije obojen
	int s = 50;
	for (int i = 0; i < listOfFlight.size(); i++) {
		string text1 = "| " + listOfFlight.at(i).getDestination();
		Text *textParameter1 = new Text(Point(30, s), text1);
		textParameter1->set_color(Color::black);
		textParameter1->set_font(Font::helvetica);
		textParameter1->set_font_size(12);
		attach(*textParameter1);

		string text2 = "| " + listOfFlight.at(i).getDeparture();
		Text *textParameter2 = new Text(Point(130, s), text2);
		textParameter2->set_color(Color::black);
		textParameter2->set_font(Font::helvetica);
		textParameter2->set_font_size(12);
		attach(*textParameter2);

		string text = "| " + listOfFlight.at(i).getFlightNo();
		Text *textParameter = new Text(Point(190, s), text);
		textParameter->set_color(Color::black);
		textParameter->set_font(Font::helvetica);
		textParameter->set_font_size(12);
		attach(*textParameter);


		string text3 = "| " + listOfFlight.at(i).getGateNo();
		Text *textParameter3 = new Text(Point(260, s), text3);
		textParameter3->set_color(Color::black);
		textParameter3->set_font(Font::helvetica);
		textParameter3->set_font_size(12);
		attach(*textParameter3);
		switch (parameter)
		{
		case 1:
			textParameter1->set_color(Color::dark_blue);
			break;
		case 2:
			textParameter2->set_color(Color::dark_blue);
			break;
		case 3:
			textParameter->set_color(Color::dark_blue);
			break;
		case 4:
			textParameter3->set_color(Color::dark_blue);
			break;
		default:
			break;
		}
		s += 17;
	}
}

void DisplayWindow::displayNumberPrameters()
{
	//ispis broja iteracija
	Text *textNumOfIter = new Text(Point(550, 75), "Broj iteracija je: " + to_string(numberOfIter));
	textNumOfIter->set_color(Color::black);
	textNumOfIter->set_font(Font::helvetica);
	textNumOfIter->set_font_size(13);
	attach(*textNumOfIter);

	//ispis ukupnog broja poredjenja
	Text *textNumOfCompare = new Text(Point(550, 105), "Broj poredjenja je: " + to_string(numberOfCompare));
	textNumOfCompare->set_color(Color::black);
	textNumOfCompare->set_font(Font::helvetica);
	textNumOfCompare->set_font_size(13);
	attach(*textNumOfCompare);

	//ispis ukupnog broja zamena elemenata 
	Text *textNumOfSwap = new Text(Point(550, 135), "Broj zamena elemenata je: " + to_string(numberOfSwap));
	textNumOfSwap->set_color(Color::black);
	textNumOfSwap->set_font(Font::helvetica);
	textNumOfSwap->set_font_size(13);
	attach(*textNumOfSwap);
}
