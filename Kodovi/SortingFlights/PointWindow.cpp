//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 08.01.2021.
// Copyright   :
// Description : GUI prozor - u kome se korisniku prikazuje rezultat sortiranja(tackice) - implementacija
//============================================================================
#include "DisplayWindow.h"
#include "PointWindow.h"
#include "FileWork.h"
#include "Sort.h"

PointWindow::PointWindow(Point xy, int width, int height, const string& title, int parameter, int sort, int orderParameter) :
	Window(xy, width, height, title),
	quitButton(Point(600, 220), 120, 30, "Zavrsi", cb_quit)
{
	//postavljanje prozora
	color(Color::white);
	attach(quitButton);
	//vectori za tekst, linije i tackice
	Vector_ref<Text> listOfText;
	Vector_ref<Line> listOfLine;
	Vector_ref<Mark> listOfMark;

	//za odredjivanje gde ce se nalaziti ispis poslednje promene u sortiranju
	int markCoodinate = 0;
	vector<vector<string>>listOfChange;
	vector<Flight>list = FileWork().readInputFile("inputFileExample.txt");
	//ukoliko je selection sort
	if (sort == sort::selction) {
		SortDTO sortDTO = SelectionSort().sort(list, parameter, orderParameter);
		listOfChange = sortDTO.getListOfParameter();
	}
	//ukoliko je heap sort
	else if (sort == sort::heap) {
		SortDTO sortDTO = Heap(list, parameter, orderParameter).sort(list, parameter, orderParameter);
		listOfChange = sortDTO.getListOfParameter();
	}
	//prolazak kroz sve iteracije
	for (int i = 0; i < listOfChange.at(0).size(); i++) {
		//crtanje prve promene
		listOfText.push_back(new Text(Point(50, 30 + 20 * i), listOfChange.at(0).at(i)));
		//funkcija za crtanje tackica i linija
		drawWindow(listOfLine, listOfMark, listOfChange, i);
		//racunjanje koordinata za ispis poslednje promene
		markCoodinate = 150 + 35 * (listOfChange.size() + 1);
		//crtanje poslednje tabelice - sortiran niz
		listOfText.push_back(new Text(Point(markCoodinate, 30 + 20 * i), listOfChange.at(listOfChange.size() - 1).at(i)));
	}
	//dodavanje teksta na prozor
	listOfText[0].set_font_size(11);
	listOfText[0].set_color(Color::black);
	attach(listOfText[0]);
	for (int i = 1; i < listOfText.size(); i++) {
		listOfText[listOfText.size() - i].set_font_size(11);
		listOfText[listOfText.size() - i].set_color(Color::black);
		attach(listOfText[listOfText.size() - i]);
	}

	

	while (true) {
		quitPushed = false;

		while (!quitPushed) Fl::wait();

		//za izlazak iz prozora
		if (quitPushed) {
			hide();
		}
	}


}
//destruktor
PointWindow::~PointWindow() {

}
//implementacija callback funkcije
void PointWindow::cb_quit(Address, Address pw)
{
	reference_to<PointWindow>(pw).quit();
}
//implementacija funkcije koje poziva callback funkcija
void PointWindow::quit()
{
	quitPushed = true;
	hide();
}
//funkcija koja poredi letove i vraca liste indeksa na kojima se razlikuju
vector<vector<int>> PointWindow::compareFlight(vector<string> list1, vector<string> list2) {
	vector<vector<int>> list;
	for (int i = 0; i < list1.size(); i++) { //prolazak kroz list1
		for (int j = 0; j < list2.size(); j++) { //prolazak kroz list2
			if (i == j) {
				vector<int> listOfIndex; //lista za smestanje indeksa na kojima se razlikuju letovi
				if (list1.at(i) == list2.at(j)) {//ukoliko su elementi isti nastavlja se dalje
					continue;
				}
				else
				{
					listOfIndex.push_back(i); //dodavanje prvog indeksa u listu indeksa
					for (int n = 0; n < list2.size(); n++) {
						if (list2.at(n) == list1.at(i)) {
							listOfIndex.push_back(n);  //dodavanje drugog indeksa u listu indeksa
							break;
						}
					}
				}
				list.push_back(listOfIndex); //lista sa indeksima se dodaje u listu svih indeksa
			}
		}
	}
	return list;
}
//funkcija koja iscrtava linije
void PointWindow::drawLine(vector<vector<int>> listOfIndex, int i, int j, Vector_ref<Line>& listOfLine) {
	//prolazak kroz listu u kojoj se nalaze liste sa razlicitim indeksima - tj elementi koji se razlikuju u odnosu na prethodnu iteraciju
	for (int n = 0; n < listOfIndex.size()-1; n++) {
		//spajanje gornjih i donjih tacaka
		if (listOfIndex.at(n).at(0) == i) {
			listOfLine.push_back(new Line(Point(160 + 35 * (j + 1), 25 + 20 * i), Point(160 + 35 * (j + 2), 25 + 20 * (listOfIndex.at(listOfIndex.size() - 1).at(0)))));
			break;
		}
		//spajanje donjih i gornjih tacaka
		if (listOfIndex.at(n + 1).at(0) == i) {
			listOfLine.push_back(new Line(Point(160 + 35 * (j + 1), 25 + 20 * i), Point(160 + 35 * (j + 2), 25 + 20 * (listOfIndex.at(0).at(0)))));
			break;
		}
		//stajanje tacaka u istoj ravni
		else
		{
			listOfLine.push_back(new Line(Point(160 + 35 * (j + 1), 25 + 20 * i), Point(160 + 35 * (j + 2), 25 + 20 * i)));
		}
		
	}
	

}
//funkcija koja iscrtava linije i tackice
void PointWindow::drawWindow(Vector_ref<Line>& listOfLine,Vector_ref<Mark>&listOfMark,vector<vector<string>>listOfChange, int i) {
	for (int j = 0; j < listOfChange.size() - 1; j++) {
		//iscrtavanje tackica
		listOfMark.push_back(new Mark(Point(160 + 35 * (j + 1), 25 + 20 * i), 'o'));
		listOfMark.push_back(new Mark(Point(160 + 35 * (j + 2), 25 + 20 * i), 'o'));

		//pravljenje liste indeksa na kojima se nalazi razlika
		vector<vector<int>> listOfIndex = compareFlight(listOfChange.at(j), listOfChange.at(j + 1));
		//ukoliko lista nije prazna poziva se funkcija za crtanje linija koje spajaju gornje i donje tacke i obrnuto
		if (!listOfIndex.empty()) {
			drawLine(listOfIndex, i, j, listOfLine);
		}
		//ukoliko je lista prazna crtace se prave linije
		else
		{
			listOfLine.push_back(new Line(Point(160 + 35 * (j + 1), 25 + 20 * i), Point(160 + 35 * (j + 2), 25 + 20 * i)));
		}
		
		//kacenje linija o tackica na prozor
		attach(listOfMark[listOfMark.size() - 1]);
		attach(listOfMark[listOfMark.size() - 2]);
		attach(listOfLine[listOfLine.size() - 1]);
	}
}