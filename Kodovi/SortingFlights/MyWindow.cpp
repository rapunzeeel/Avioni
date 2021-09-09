//============================================================================
// Name        : main.cpp
// Author      : Nevena Prokic SW6/2019
// Date        : 06.01.2021.
// Copyright   :
// Description : GUI prozor - odabir podrazumevanih parametara ili ih sam korisnik unosi - implementacija
//============================================================================
#include "MyWindow.h"
#include "ChooseWindow.h"
#include "DisplayWindow.h"

MyWindow::MyWindow(Point xy, int width, int height, const string& title, char *argv[]) :
	Window(xy, width, height, title),
	defaultButton(Point(50, 100), 110, 30, "Podrazumevani", cb_default),
	chooseButton(Point(250, 100), 110, 30, "Izaberi sam", cb_choose)
{
	string inputPath = argv[1];
	string outputPath = argv[2];
	//postavljanje dugmica i boje prozora
	color(Color::white);
	attach(defaultButton);
	attach(chooseButton);
	//u ovoj funkciji korisnik pritiskom na neko od dugmadi bira kakve parametre zeli
	chooseModeOfInteraction();
}
MyWindow::~MyWindow() {

}
//implementacija callback funkcija
void MyWindow::cb_default(Address, Address pw)
{
	reference_to<MyWindow>(pw).defaultParameter();
}
void MyWindow::cb_choose(Address, Address pw)
{
	reference_to<MyWindow>(pw).chooseParameter();
}
//implementacija funkcija koje callback poziva - menjanje bool vrednosti
void MyWindow::defaultParameter()
{
	defaultButtonPushed = true;
}
void MyWindow::chooseParameter()
{
	chooseButtonPushed = true;
}
void MyWindow::chooseModeOfInteraction() {
	//postavljenje teksta
	Text *choose = new Text(Point(130, 50), "Izaberite parametre: ");
	choose->set_color(Color::black);//odabir boje teksta
	choose->set_font(Font::helvetica_italic);//odabir fonta teksta
	attach(*choose);//kacenje teksta na prozor

	//postavljanje slika
	Image* defaultImage = new Image(Point(160, 120), "slika1.jpg", Suffix::none);
	attach(*defaultImage);//kacenje slike na prozor

	Image* chooseImage = new Image(Point(360, 120), "slika2.jpg", Suffix::none);
	attach(*chooseImage);

	show();
	while (true) {
		defaultButtonPushed = false;
		chooseButtonPushed = false;
		int parameter = 1;
		int sort = 0;
		int orderParameter = 0;

		while (!defaultButtonPushed && !chooseButtonPushed) Fl::wait();
		//provera koje dugme je kliknuo korisnik
		if (chooseButtonPushed) {
			//prozor se zatvara i otvara mu se prozor gde moze da unese parametre kao i ulaznu i izlaznu putanju
			hide();
			ChooseWindow choose(Point(100, 100), 500, 200, "Izbori", __argv);
		}
		if (defaultButtonPushed) {
			//prozor se zatvara i orvara mu se prozor sa prikazom sortiranih letova po podrazumevanim parametrima
			hide();
			//oslobadjanje memorije
			delete(defaultImage);
			delete(chooseImage);
			delete(choose);
			DisplayWindow display(Point(50, 50), 1000, 550, "Sortirani letovi", parameter, sort,orderParameter, inputPath,outputPath);
		}
	}
}