#ifndef __biblio_h
#define __biblio_h


#include<fstream>
#include <iterator>
#include <vector>
#include <sstream>
#include <list>
#include <opencv2/opencv.hpp>
#include "ftech.h"
#include "image.h"

using namespace cv;
using namespace std;

class Biblio {

	private:
		
	vector<Image> _bib;
 

	public:
		
		Biblio();
	        // Getters
		vector<Image> GetBib();
 		
		// Setters
void ChargerDecrip(short unsigned int prf);
void AffichDescips();
void TrierDescips();
void SupprimerImage();
void FichIndic();
void AffichePrix();
void SauvgardeDescrips(); 
void SousTrierPrix();
void SousTrierAcces();
void SousTrierDate();
void ModifDescrip();
void AjouterImage();
void SousTrier();
void AfficheImage();


/*vector<Biblio> ChargerDecrip();
void AffichDescipImage(Biblio & Bib);
void AfficheDecrip(vector<Biblio> & Bib);
void TrierCoutDcroi(vector<Biblio> Bib);
void TrierCoutDate(vector<Biblio> Bib);*/

};
void AfficheEntete();



#endif
