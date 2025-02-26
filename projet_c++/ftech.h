
#ifndef __ftech_h
#define __ftech_h


#include <iostream>
#include <string> 

using namespace std;

class Ftech {
		string _titre;
		float _prix;
		string _auth;
		string _source;
		unsigned int _numero;
		char _acces;
		unsigned int _jour;
		unsigned int _mois;
		unsigned int _annee;
		string _chemin;


	public:
// Constructeur		
		Ftech(unsigned int num);
		Ftech();
		Ftech(unsigned int numero,string titre, string auteur, string source, char acces, float cout, unsigned int jour, unsigned int mois, unsigned int annee);
		
		
// Getters
		string GetTitre();
		string GetAuth();
		string GetSource();
		float GetPrix();
		unsigned int GetNum();
		char GetAcces();
		unsigned int GetJour();
		unsigned int GetMois();
		unsigned int GetAnnee(); 
		string GetChemin();

// Setters
		void SetTitre();
		void SetAuth();
		void SetSource();
		void SetPrix();
		void SetNum();
		void SetAcces(char acces);
		void SetDate();
		void SetChemin(string chemin);
		

		void SetTitre2(string tit);
		void SetAuth2(string aut);
		void SetSource2(string sou);
		void SetPrix2(float prix);
		void SetNum2(unsigned int num);
		void SetAcces2(char acces);
		void SetDate2(unsigned int jour, unsigned int mois, unsigned int annes);
		void SetChemin2(string chem);
		
		
//Autres Méthodes
		void AffichDate(); 
		void AffichDescip1();

};

#endif
