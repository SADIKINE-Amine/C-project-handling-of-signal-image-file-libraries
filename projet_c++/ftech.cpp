#include "ftech.h"
#include <sstream>


// Constructeurs
Ftech::Ftech(unsigned int num)
{
	_numero = num;
	_titre = "";
	_auth = "";
	_source = "";
	_acces = 'R';
	_jour = 01;
	_mois = 01;
	_annee = 2000;
	_chemin = "";

}

Ftech::Ftech()
  {
  	_numero=0;
  	_titre="Rien";
	_auth = "";
  	_source="";
  	_acces=' ';
  	_prix=0;
  	_jour=01;
  	_mois=01;
  	_annee=2000;
  	_chemin=" ";
  }	

 Ftech::Ftech(unsigned int numero,string titre, string auteur, string source, char acces, float cout, unsigned int jour, unsigned int mois, unsigned int annee)
  { 
  	_numero=numero;
	_auth = auteur;
  	_titre=titre;
  	_source=source;
  	_acces=acces;
  	_prix=cout;
  	_jour=jour;
  	_mois=mois;
  	_annee=annee;
  	_chemin=" ";
  }



// Setters

void Ftech::SetTitre()
{
	string titre; 

	cout << "Quel est le titre de l'image ? " << endl;

	cin >> titre;
	_titre = titre ;
	while(titre.size() >=20)
	{
		cout << "Votre titre est trop long, veuillez le resaisir : " << endl ;
		cin >> titre ;
		_titre = titre ;
		cout << endl ;
	}
	
	_titre = titre;
	

}


void Ftech::SetAuth()
{

	string auth; 

	cout << "Quel est le nom de l'auteur de l'image ? " << endl;	
	cin >> auth;
	_auth = auth ;

	while(_auth.size() >=10)
	{
		cout << "Votre nom d'auteur est trop long, veuillez le resaisir : " << endl;
		cin >> auth ;
		cout << endl ;
		_auth = auth ;
	}
	
	_auth = auth;
}


void Ftech::SetSource()
{
	string source;

	
	cout << "Quel est le nom de la source de l'image ? " << endl;
	cin >> source;
	_source = source ;
	
	while(_source.size() >=20)
	{
		cout << "Votre nom de source est trop long, veuillez le resaisir : " << endl;
		cin >> source ;
		_source = source ;
		cout << endl ;
	}
	
	_source = source;

}


void Ftech::SetChemin(string chemin)
{
	_chemin = chemin;
}


void Ftech::SetPrix()
{
	float prix ;
	cout << "Quel est le prix pour votre image ? " << endl;
	cin >> prix ;
	//test si caractères entrés à la place de nombre
	while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore() ;
	    cout << "Quel est le prix pour votre image ? " << endl;
	    cin >> prix ; 	
        } 
	_prix = prix ;
	while(int(_prix) >= 10000000 ) // verification que le prix n'excède pas 10 000 000 euros
	{
		cout << "Votre prix est trop important, veuillez le réduire : " << endl ;
		cin >> prix ;
		_prix = prix ;
	}
	
	_prix = prix ;
}

void Ftech::SetNum()
{
	unsigned int numero ;
	cout << "Quel est le numero de votre image ?" <<endl;
	cin >> numero ;

	_numero = numero ;		
}


void Ftech::SetDate()
{
	unsigned jour, mois, annee ;

	//test
	cout << "Quel est le jour JJ associé à l'image (JJ/MM/AAAA) ?" <<endl;
	cin >> jour ;
	//test si des caractères sont entrés à la place de nombres
	while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore(256,' ');
	    cout <<  "Quel est le jour JJ associé à l'image (JJ/MM/AAAA) ?" << endl;
	    cin >> jour; 	
        } 

	while(jour <= 0 || jour > 31)
	{
	cout << "Votre choix de jour (JJ) est erroné, il doit être compris entre 0 et 31" << endl ;
	cin >> jour ;
	}
	
	cout << "Quel est le mois (MM) associé à l'image (JJ/MM/AAAA) ?" <<endl;
	cin >> mois ;
	
	while(mois < 1 || mois > 12)
	{
	cout << "Votre choix de mois (MM) est erroné, il doit être compris entre 1 et 12" << endl ;
	cin >> mois ;
	}
	while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore(256,' ');
	    cout <<  "Quel est le jour JJ associé à l'image (JJ/MM/AAAA) ?" << endl;
	    cin >> mois; 	
        } 

	cout << "Quel est l'année (AAAA) associée à l'image (JJ/MM/AAAA) ?" <<endl;
	cin >> annee ;

	while(annee <= 1900 || annee > 2019)
	{
	cout << "Votre choix d'année (AAAA) est erroné, il doit être compris entre 1900 et 2019 (année courante)" << endl ;
	cin >> annee ;
	}
		while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore(256,' ');
	    cout <<  "Quel est le jour JJ associé à l'image (JJ/MM/AAAA) ?" << endl;
	    cin >> annee; 	
        } 


	//affectations
	_jour = jour ;
	_mois = mois ;
	_annee = annee ;
}


void Ftech::SetAcces(char acces)
{
	if(acces=='R' || acces =='O')
	{
		_acces = acces ;
	}
	
}


void Ftech::SetTitre2(string tit)
{
	_titre = tit;
}

void Ftech::SetAuth2(string aut)
{
	_auth = aut;
}

void Ftech::SetSource2(string sou)
{
	_source = sou;
}

void Ftech::SetPrix2(float prix)
{
	_prix = prix;
}

void Ftech::SetNum2(unsigned int num)
{
	_numero = num;
}

void Ftech::SetAcces2(char acces)
{
	_acces = acces;
}

void Ftech::SetDate2(unsigned int jour, unsigned int mois, unsigned int annee)
{
	_jour = jour;
	_mois = mois;
	_annee = annee;
}

void Ftech::SetChemin2(string chem)
{
	_chemin =chem;
}





// Getters


string Ftech::GetTitre()
{
	return _titre;
}


string Ftech::GetAuth()
{
	return _auth;
}

string Ftech::GetSource()
{
	return _source;
}


float Ftech::GetPrix()
{
	return _prix;
}

unsigned int Ftech::GetNum()
{
	return _numero;

}


char Ftech::GetAcces()
{
	return _acces;	
}

 unsigned int Ftech::GetMois()
{
	return _mois;
}

  
unsigned int Ftech::GetAnnee()
{
  	return _annee;
}
   
unsigned int Ftech::GetJour()
{	
	return _jour;
}

string Ftech::GetChemin()
{
	return _chemin;
}


void Ftech::AffichDate()
{
	cout << _jour << "/" << _mois << "/" << _annee << endl ;	
}

void Ftech::AffichDescip1()
{   ostringstream sprix;
    sprix << _prix;
    string prixs(sprix.str());
	cout<<_numero;
	//limitation du nombre de caractères d'affichage par caractéristiques (homogénisation de l'affichage)
	if(_numero < 10){ cout << " ";}
	cout<<" |"<<_titre;
	for(int k = _titre.size(); k < 20; k ++) { cout << " ";}
	cout<<"|"<<_source;
	for(int k = _source.size(); k < 20; k++) { cout << " ";}
	cout<<"|"<<_auth;
	for(int k = _auth.size(); k < 10; k++) { cout << " ";}
	cout<<"| "<<_acces<<"    | " << prixs;
	for(int k = prixs.size(); k < 7; k ++) { cout << " ";} 
	cout<<"|";	
    AffichDate();
	cout << endl;
    
}






