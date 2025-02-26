
#include <iostream>
#include <math.h>
#include <cstdlib>
#include <string>
#include <fstream>
#include "biblio.h"
#include "ftech.h"
#include "image.h"

using namespace std;
 

int Identification()
{
	int Profil=2;	
	string login;
	string log0 = "TF204", log1 = "CR081", log2 = "AM978";					// Codes Fonctionnels  TF204   CR081  AM978
	cout <<"	Bienvenue "<<endl;
	cout << "__________________________________________| Identification |__________________________________________"<<endl<<endl;

	cout << "Entrez votre identifiant (Deux lettres et trois chiffres) : ";
	
	cin.clear();
	getline(cin, login);
	
	while((login != log0) && (login != log1) && (login != log2))				// Vérification Code correct
	{
		cout<<"\033[31m";
		cout << "Cet identifiant n'est pas reconnu, réessayez : ";
		cin >> login;
		cout<<"\033[00m";

	}
	cout << "______________________________________________________________________________________________________"<<endl<<endl;

	if(login == log0)									// Reconnaissance du profil correspondant
		{
		Profil = 0;
		cout << "Vous êtes reconnu comme un utilisateur de niveau 0 (accès total)" << endl;
		return Profil;
		}
	else if(login == log1)
		{
		Profil = 1;
		cout << "Vous êtes reconnu comme un utilisateur de niveau 1 (accès restreint)" << endl;
		return Profil;
		}
	else 
		{
		Profil = 2;
		cout << "Vous êtes reconnu comme un utilisateur de niveau 2 (pas d'accès)" << endl;
		return Profil;
		}
}
 
int main() {

	Biblio b;
	Image m;
	int identif;
	identif=Identification();
	int choix_soustri = 0 ;
	int choix_trait = 0 ;
        int choix_lap = 0 ;
	int choix_ajout = 0 ;
	int choix_modif = 0 ;
	unsigned int num ;

	switch(identif){


      case 0 :
      int choix;
      b.ChargerDecrip(identif);
      do{
      	cout<<"\033[100;1m"<<endl;
  		cout <<"__________________________________________________________________________________________________________________________________________"<<endl<<endl;
  		cout <<"								Menu pricipal"<<endl;
  		cout <<"__________________________________________________________________________________________________________________________________________"<<endl;
  		cout << endl;
  		cout << "						Pour quitter la session tapez			: 0"<<endl; 
  		cout << "						Pour afficher les descripteurs des images tapez	: 1"<<endl;
  		cout << "						Pour afficher une ou des image(s) tapez		: 2"<<endl;    
  		cout << "						Pour trier les descripteurs des images tapez	: 3"<<endl;
  		cout << "						Pour supprimer une ou des images tapez		: 4"<<endl;
		cout << "						Pour sous trier des images tapez		: 5"<<endl;
		cout << "						Pour appliquer un traitement tapez              : 6"<<endl;
		cout << "                                                Pour ajouter une image tapez                    : 7"<<endl;
		cout << "                                                Pour modifier une image tapez                   : 8"<<endl;
  		cout <<"__________________________________________________________________________________________________________________________________________"<<endl;
  		cout<<"\033[00m"<<endl;
      	cout <<"--->  ";
      	cin >> choix;
      	    switch(choix){
      		case 1:
      		cout << "Les descripteurs"<<endl;
      		b.AffichDescips();
      		b.FichIndic();
		//waitKey(0);
      		break;
      		case 2:
      		b.AfficheImage();
      		break;
      		case 3:
      		b.TrierDescips();
      		break;
      		case 4:
      		b.SupprimerImage();
      		break;
	        case 5 :
                while(choix_soustri != 4){
                cout << "Quel sous tri voulez vous effectuer ? : (1) Intervalle de dates, (2) Type d'accès, (3) Prix, (4) Quitter "<< endl ;
                cin >> choix_soustri ;

                if(choix_soustri == 1){b.SousTrierDate() ;}
                if(choix_soustri == 2){b.SousTrierAcces() ;}
                if(choix_soustri == 3){b.SousTrierPrix() ;}
                }
                break;	
	
		case 6 : 
			cout << "Quel traitement souhaitez vous effectuer ? : (1) Détection de contours (Laplacien), (2) Filtrage par convolution 3x3, (3) Transformée de Hough, (4) Quitter "<< endl ;
			cin >> choix_trait ;
		while(choix_trait !=4){
			Image imtemp;
			cout << "Donner le numéro de l'image à modifier "<< endl ;
			cin >> num ;
			imtemp = b.GetBib().at(num-1);
			imtemp.ChargeImage();
			if(choix_trait == 1){cout << " Tapez 1 pour 4 connexités ou Tapez 2 pour 8 connexités " << endl ; cin >> choix_lap ; imtemp.TraitementLapl(choix_lap) ;}
		        if(choix_trait == 2){imtemp.conv33() ;}
		        if(choix_trait == 3){imtemp.HoughTransforme() ;}
			cout << "Quel traitement souhaitez vous effectuer ? : (1) Détection de contours (Laplacien), (2) Filtrage par convolution 3x3, (3) Transformée de Hough, (4) Quitter "<< endl ;
			cin >> choix_trait ;
		 }
                break;
	
		case 7 : 
		while(choix_ajout !=2){
		cout << "Souhaitez vous (1) ajouter une image ou (2) Quitter "<< endl ;
		cin >> choix_ajout ;
		if(choix_ajout == 1){b.AjouterImage();}}
                break;		
      	        
		case 8 : 
		choix_modif = 1;
		while(choix_modif !=2){
			cout << "Donner le numéro de l'image à modifier "<< endl ;
			cin >> num ;
			while((num < 1) || (num > b.GetBib().size()))
			{
				cout << "Valeur incorrecte, veuillez entrer une valeur correspondant à une image : " << endl;
				cin >> num;
			}
			b.GetBib().at(num-1).Modif() ;
			cout << "Souhaitez vous (1) modifier une autre image ou (2) Quitter "<< endl;
			cin >> choix_modif ;
			while((choix_modif != 1) && (choix_modif != 2))
			{
				cout << "Réponse incorrecte, veuillez saisir 1 ou 2" << endl;
				cin >> choix_modif;
			}
		}
		break ;}
                }while(choix!=0);

      break;

      case 1 :
      b.ChargerDecrip(1);
      b.AffichDescips();
      b.TrierDescips();
      b.FichIndic();
      while(choix_soustri != 4){
      cout << "Quel sous tri voulez vous effectuer ? : (1) Intervalle de dates, (2) Type d'accès, (3) Prix, (4) Quitter "<< endl ;
      cin >> choix_soustri ;

      if(choix_soustri == 1){b.SousTrierDate() ;}
      if(choix_soustri == 2){b.SousTrierAcces() ;}
      if(choix_soustri == 3){b.SousTrierPrix() ;}
      }
      break;

      case 2 :
      break;
    } 
	return 0;
}

 
	 
