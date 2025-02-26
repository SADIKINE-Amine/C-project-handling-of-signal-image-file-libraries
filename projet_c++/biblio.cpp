#include "image.h"
#include "ftech.h"
#include "biblio.h"


Biblio::Biblio()
{  Image bib;
	_bib.push_back(bib);
}

vector<Image> Biblio::GetBib()
{
  return _bib;
}

void Biblio::ChargerDecrip(short unsigned int prf)
{

    vector<string> Tableau;      //Pour stocker les descripteurs
    string ligne;             // Pour stocker une ligne du fichier

    string const nomFlux("data.txt");
    ifstream monFlux(nomFlux.c_str(), ios::app);

    if(monFlux)
    {
         while (getline(monFlux,ligne))
        {
          Tableau.push_back(ligne);
        }

        monFlux.close();
    }
    else
    cerr << "Impossible d'ouvrir le fichier !" << endl; 
    Image H;
    int k=0;
    
  for( unsigned int i = 0 ; i< Tableau.size();i++)
      {
        string str;
        Ftech y;
        stringstream is(Tableau.at(i));
        istream_iterator<string> begin(is);
        istream_iterator<string> end; 
        vector<string> Tsrings(begin, end); //Chaque case du tableau Tsrings contient une des informations sur l'Image
        str=Tsrings[3];
        //cout << "test";
        if(prf==0 || str[0]=='O')
        {
          _bib.push_back(H);
          y.SetNum2(k+1);
          y.SetTitre2(Tsrings[0]); //Titre
          y.SetSource2(Tsrings[1]);//Source
          y.SetAuth2(Tsrings[2]);//Auteur
          y.SetAcces2(str[0]);//acces
          y.SetPrix2(stof(Tsrings[4].substr())); //Prix
          y.SetDate2(atoi(Tsrings[5].c_str()),atoi(Tsrings[6].c_str()), atoi(Tsrings[7].c_str()));
          y.SetChemin2(Tsrings[8].c_str());//Chemin
          _bib.at(k).SetDesc(y);
          k++;
        }
      }

      int j=_bib.size()-1;
      _bib.erase(_bib.begin()+j);
}

void Biblio::AffichDescips()
{  AfficheEntete();
   for( unsigned int i = 0 ; i<_bib.size();i++)
      {
        Ftech Des = _bib.at(i).GetDesc();
        _bib.at(i).AffichDescip();
    }
}

void Biblio::SupprimerImage() 
{
  unsigned int id;
  cout << "Tapez le numero de l'image à supprimer : ";
  cin >> id;
  if(id > _bib.size() || id < 1 )
  {
    cout<<"\033[31m";
    cout <<"Le numero que vous avez saisie est invalide "<<endl;
    cout<<"\033[00m";
  }else
      {  
        _bib.erase(_bib.begin()+id-1);
        for (unsigned int j=id-1 ; j<_bib.size() ; ++j)
        {
          Ftech Desc=_bib.at(j).GetDesc();
          Desc.SetNum2(j+1);
          _bib.at(j).SetDesc(Desc);  
        }
      }
}

void Biblio::FichIndic(){

  unsigned int acees_libre=0,nbrImg=_bib.size();
  float cout_max, cout_min, moyenne,somme=0;

  Ftech Des=_bib.at(0).GetDesc();
  cout_min=Des.GetPrix();
  cout_max=Des.GetPrix();

   for (unsigned int i=1 ; i<_bib.size() ; ++i)
        {   Des=_bib.at(i).GetDesc(); 
            if (Des.GetPrix() < cout_min){
               cout_min=Des.GetPrix();
            }
        }

    for (unsigned int i=1 ; i<_bib.size() ; ++i)
        {   Des=_bib.at(i).GetDesc(); 
            if (Des.GetPrix() > cout_max)
            {
               cout_max=Des.GetPrix();
            }
        }

    for (unsigned int i=0 ; i<_bib.size() ; ++i)
        {   Des=_bib.at(i).GetDesc(); 
            somme=Des.GetPrix()+somme;           
        }
        moyenne=somme/nbrImg;

    for (unsigned int i=0 ; i<_bib.size() ; ++i)
        {   
            Des=_bib.at(i).GetDesc();
            if(Des.GetAcces()=='O') 
            {
              acees_libre++;
            }           
        }
      cout<<"\033[100;1m"<<endl;
      cout <<"__________________________________Les indicateurs____________________________________________________________"<<endl<<endl;
      cout <<"                  -Le nombre d'images                  : "<<nbrImg<<endl;
      cout <<"                  -Le coût min                         : "<<cout_min<<endl;
      cout <<"                  -Le coût max                         : "<<cout_max<<endl;
      cout <<"                  -Le coût moyenne                     : "<<moyenne<<endl;
      cout <<"                  -Nombre d'image à acces libre        : "<<acees_libre<<endl;
      cout <<"______________________________________________________________________________________________________________"<<endl;
      cout<<"\033[00m";
      cout<<endl;
}

void Biblio::AffichePrix()
{  
  unsigned int id;
  cout << "Tapez le numero de l'image : ";
  cin >> id;
  if(id > _bib.size() || id < 1 )
  { 
    cout<<"\033[31m";
    cout <<"Le numero que vous avez saisie est invalide "<<endl;
    cout<<"\033[00m";
  }else
    {
      Ftech Des;

      Des=_bib.at(id-1).GetDesc();
            if (Des.GetPrix()==0)
            {
              cout<<"L'image est gratuite"<<endl;
            }else
              {
                cout<< "Le coût est : ";
                cout<< Des.GetPrix()<<" euros"<<endl;
              }                   
    }
}

void Biblio::AfficheImage()
{
  unsigned int id,q;
  cout<<"\033[100;1m"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl<<endl;
  cout <<"       Le sous menu : Affichage d'une ou plusieurs image(s)"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout << endl;
  cout << "                     Pour afficher une image tapez   1"<<endl;  
  cout << "                     Pour quitter le sous menu tapez 0"<<endl;                        
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout<<"\033[00m"<<endl;
  do{
    cout << "Tapez votre choix (1 ou 0)"<<endl;
    cout <<"--->  ";
    cin >> q;
    }while(q!=0 && q!=1);
  while(q!=0)
  {
    cout << "Tapez le numéro de l'image à afficher"<<endl;
    cout <<"--->  ";
    cin >> id;

      while(id > _bib.size() || id < 1)
      {
        cout<<"\033[31m";
        cout <<"Le numero que vous avez saisie est invalide "<<endl;
        cout<<"\033[00m";
        cout << "Veuillez taper un numéro valide "<<endl;
        cout <<"--->  ";
        cin >> id;
      }
     
      Image img=_bib.at(id-1);
      Ftech Des=_bib.at(id-1).GetDesc();
      string titre=Des.GetTitre();
      img.ChargeImage();

      imshow(titre,img.GetImg());
      waitKey();
      do{
      cout << "Pour afficher une autre image tapez 1 si non tapez 0"<<endl;
      cout <<"--->  ";
      cin >> q;
        while(q!=0 && q!=1)
        {
          cout<<"\033[31m";
          cout <<"Le numero que vous avez saisie est invalide "<<endl;
          cout<<"\033[00m";
          cout << "Veuillez taper un numéro valide (1 ou 0)"<<endl;
          cout <<"--->  ";
          cin >> q;
        }
      }while(q!=0 && q!=1); 
  }
}                  


void Biblio::ModifDescrip()
{ int rep ;
  unsigned int indice;
  cout<<"\033[100;1m"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl<<endl;
  cout <<"    Le sous menu : Modification d'un ou plusieurs descripteur(s)"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout << endl;
  cout << "                  Taper 1 pour choisir une image à modifier"<<endl;
  cout << "                  Taper 2 pour  quitter                    "<<endl<<endl;                          
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout<<"\033[00m"<<endl;
  cout <<"--->  ";
  cin >> rep;
  while(rep!=2){
    if(rep==1)
    {
      cout << "Entrer le numéro de l'image à modifier" << endl;
      cout <<"--->  ";
      cin >> indice;
      while((indice < 1) || (indice >_bib.size()))
      {
        cout<<"\033[31m";
        cout << "Choix invalide, veuillez un numéro valide " << endl;
        cout<<"\033[00m";
        cout <<"--->  ";
        cin >> indice;
      }
      _bib.at(indice-1).Modif();
      cout<<"\033[100;1m"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl<<endl;
  cout <<"    Le sous menu : Modification d'un ou plusieurs descripteur(s)"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout << endl;
  cout << "                  Taper 1 pour choisir une image à modifier"<<endl;
  cout << "                  Taper 2 pour  quitter                    "<<endl<<endl;                          
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout<<"\033[00m"<<endl;
  cout <<"--->  ";
  cin >> rep;
    }
    else
    {
      cout<<"\033[31m";
      cout << "Choix invalide, veuillez saisir 1 ou 2" << endl;
      cout<<"\033[00m";
      cout <<"--->  ";
      cin >> rep;
      
    }
  }
}

void Biblio::AjouterImage()
{
unsigned int numero = _bib.size() + 1 ; 
Image Imdes ;
Ftech Des(numero) ;
//Imdes(numero) ;

char type ;
//Des._img.SetDesc(Des) ;

Des.SetTitre() ;
Des.SetAuth() ;
Des.SetSource() ;
Des.SetPrix() ;
Des.SetDate() ;

string chemin;
Mat test ;
cout << "Quel est le nom du fichier, placé dans le repertoire Image/ ?" << endl;
cin >> chemin;
chemin = "Images/"+chemin ;
cout << chemin << endl ;
test = imread(chemin) ;
	while(test.data == NULL )                              // Check for invalid input
        {
        cout <<  "Le chemin spécifié est incorrect ! Veuillez recommencer : "  << endl ;
	cin >> chemin;
	chemin = "Images/"+chemin ;
	test = imread(chemin) ;
        }

Des.SetChemin(chemin) ;

cout << "Quel mode d'accès souhaitez-vous pour votre image : O (ouvert à tous les utilisateurs authentifiés) ou R (restreint aux utilisateurs de votre type)" << endl ;
cin >> type ;
while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore();
	    cout <<  "Quel mode d'accès souhaitez-vous pour votre image : O (ouvert à tous les utilisateurs authentifiés) ou R (restreint aux utilisateurs de votre type)" << endl;
	    cin >> type ; 	
        } 
while (type != 'O' && type != 'R') // à tester
{
cout << "Saisie incorrecte, veuillez recommencer : " << endl ; 
cout << "Quel mode d'accès souhaitez-vous pour votre image : O (ouvert à tous les utilisateurs authentifiés) ou R (restreint aux utilisateurs de votre type)" << endl ;
cin >> type ;
}
Des.SetAcces(type) ;

cout << "Votre choix est : " << endl ;

Des.AffichDescip1();

int choix_verif ;
cout << endl << " (1) Confirmez-vous votre choix ou (2) souhaitez vous resaisir certaines données de votre image ? " << endl ;
cin >> choix_verif ;
while(choix_verif != 1 && choix_verif != 2)
{
	cout << "Erreur de saisie, veuillez recommencer : " << endl ;
	cin >> choix_verif ;
}

switch(choix_verif){
case 1 : cout << "Choix confirmé" << endl ;
	break ;
case 2 : 
	int choix_elmt = 0 ;
	cout << "Quel paramètre souhaitez-vous modifier : (1) titre, (2) auteur, (3) source, (4) Prix, (5) Date, (6) tous les éléments, (7) Quitter ?" << endl ;
	cin >> choix_elmt ;
	/*while(choix_elmt != 1 && choix_elmt != 2 && choix_elmt != 3 && choix_elmt != 4 && choix_elmt != 5 && choix_elmt != 6 && choix_elmt !=7)*/
cin.clear();
while(choix_elmt <= 0 || choix_elmt > 7)
{	cout << "Erreur de saisie, veuillez recommencer : " << endl ;
	cin >> choix_elmt ;
}
	while(choix_elmt != 7) 
{
	if(choix_elmt == 1){Des.SetTitre();}	
	if(choix_elmt == 2){Des.SetAuth();}
	if(choix_elmt == 3){Des.SetSource();}	
	if(choix_elmt == 4){Des.SetPrix();}
	if(choix_elmt == 5){Des.SetDate();}
	if(choix_elmt == 6){Des.SetTitre();
			    Des.SetAuth();
	                    Des.SetSource();
	                    Des.SetPrix();
	                    Des.SetDate();}	
	
break ;	
}	
}
Imdes.SetDesc(Des);
_bib.push_back(Imdes) ;	
}

void Biblio::TrierDescips() // il faut voir cette methode modifier on sortie _bib
{
  int choix;
  Ftech Des1;
  Ftech Des2;
  vector<Ftech> Des;
  Ftech temp;

  cout<<"\033[100;1m"<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl<<endl;
  cout <<"    Le sous menu : Tri  "<<endl;
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout << endl;
  cout << "                  Pour trier :"<<endl<<endl;
  cout << "                  -En ordre décroissant de coût taper       1. " << endl;
  cout << "                  -En ordre décroissant de la date taper    2." << endl;
  cout << "                  -En ordre alphabetique de l'auteur  taper 3." << endl;
  cout << "                   (Pour quitter taper 4)" << endl; 
  cout <<"______________________________________________________________________________________________________________"<<endl;
  cout<<"\033[00m"<<endl;
   
  do{
    cout <<"--->  ";
    cin >> choix;
    if(choix==1 || choix==2 || choix==3)
    {
      for (unsigned int i=0 ; i<_bib.size() ; ++i)
        { 
          Des.push_back(Des1);
          Des1=_bib.at(i).GetDesc();
          Des.at(i)=Des1;
        }

    }

    switch(choix){
      

      case 1 : 
      
      AfficheEntete();
       for (unsigned int i=0 ; i<_bib.size() ; ++i)
        {   
          
          for (unsigned int j=i ; j<_bib.size() ; j++)
          {
            Des1=Des.at(j);
            Des2=Des.at(i);
              if (Des1.GetPrix() > Des2.GetPrix())
                {  
                      temp=Des.at(i);
                      Des.at(i)=Des.at(j);
                      Des.at(j)=temp;                 
                }
          }
          
          Des.at(i).AffichDescip1();
        }

      break;
      case 2 :
      AfficheEntete();
      for (unsigned int i=0 ; i<_bib.size() ; i++)
        {
          for (unsigned int j=i ; j< _bib.size() ; j++)
          {
            Des1=Des.at(j);
            Des2=Des.at(i);
              if (Des1.GetAnnee() > Des2.GetAnnee())
                {  
                    temp=Des.at(i);
                    Des.at(i)=Des.at(j);
                    Des.at(j)=temp;                 
                }
              }
        }

        for (unsigned int i=0 ; i<_bib.size() ; i++)
        {
          for (unsigned int j=i ; j<_bib.size() ; j++)
          {
            Des1=Des.at(j);
            Des2=Des.at(i);
              if (Des1.GetAnnee()==Des2.GetAnnee() && Des1.GetMois()>Des2.GetMois())
                {  
                      temp=Des.at(i);
                      Des.at(i)=Des.at(j);
                      Des.at(j)=temp;                 
                }
            
            }
        }

        for (unsigned int i=0 ; i<_bib.size() ; i++)
        {
          for (unsigned int j=i ; j< _bib.size() ; j++)
          {
            Des1=Des.at(j);
            Des2=Des.at(i);
              if (Des1.GetAnnee()==Des2.GetAnnee() && Des1.GetMois()==Des2.GetMois() && Des1.GetJour()==Des2.GetJour())
                {  
                  temp=Des.at(i);
                  Des.at(i)=Des.at(j);
                  Des.at(j)=temp;                 
                }
          }
          Des.at(i).AffichDescip1();
        }

      break;
      case 3 :
      AfficheEntete();

      for (unsigned int i=0 ; i<_bib.size() ; i++)
        {
          for (unsigned int j=i ; j<_bib.size() ; j++)
          {
            Des1=Des.at(j);
            Des2=Des.at(i);
            string str1=Des1.GetAuth();
            string str2=Des2.GetAuth();
            int x=str1.compare(str2);
              if ( x < 0 )
                {  
                temp=Des.at(i);
                 Des.at(i)=Des.at(j);
                 Des.at(j)=temp;
                }
            }
          Des.at(i).AffichDescip1();
        }
       
      break;

      case 4 :
       // cette case permet d'eviter le message de default
      break;
  
      default :
      cout<<"\033[31m";
      cout << "Choix invalide, veuillez saisir un nombre entre 1 et 4" << endl;
      cout<<"\033[00m";
    }

  }while(choix!= 4);
}

void Biblio::SauvgardeDescrips() 
{ 
      
    string const monFlux("data.txt");
    ofstream ofs(monFlux.c_str(), ios::out | ios::trunc);
    if(ofs){
    Ftech Des;
    for (unsigned int j=0 ; j<_bib.size() ; j++)
          {
            
            Des=_bib.at(j).GetDesc();
            ofs <<Des.GetTitre()<<" "<<Des.GetSource()<<" "<<Des.GetAuth()<<" "<<Des.GetAcces()<<" "<<Des.GetPrix()<<" "<<Des.GetJour()<<" "<<Des.GetMois()<<" "<<Des.GetAnnee()<<" "<<Des.GetChemin()<<endl;

          }
           ofs.close(); 
        }
        else   
          cerr << "Erreur à l'ouverture pour la Sauvgarde!" << endl;
}

void Biblio::SousTrierPrix()
{
unsigned int i,choix,cpt = 0 ;
float prixmin, prixmax ;
Ftech Des;

cout << "Tapez 1 si vous voulez voir les images dont le prix est < à 9.99 euros, Tapez 2 pour la tranche de prix suivante : 10 euros <= prix <= 99.99 euros, Tapez 3 pour un prix > 100 euros et Tapez 4 pour une tranche de prix choisie et Tapez 5 pour voir les images gratuites" << endl ;
cin >> choix ;
cout <<"--->  ";

while(choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5){
cout << "Votre choix est erronné /! ... Rappel : "<< endl << "Rappel : Tapez 1 si vous voulez voir les images dont le prix est < à 9.99 euros, Tapez 2 pour la tranche de prix suivante : 10 euros <= prix <= 99.99 euros, Tapez 3 pour un prix > 100 euros et Tapez 4 pour une tranche de prix choisie" << endl ;
cout <<"--->  ";
cin >>choix;
}

switch(choix){
  
  
case 1 : 
  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetPrix() <= 9.99){
      cpt+=1 ;
    _bib.at(i).AffichDescip();
    }
  }
  if(cpt == 0)
    cout << "Il n'y a pas d'image dont le coût est inférieur à 9.99 euros" << endl ;
  break ;

case 2 : 
  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetPrix() >= 10 && Des.GetPrix() <=99.99 ){
      cpt+=1 ;
    _bib.at(i).AffichDescip();
    }
  }
  if(cpt == 0)
    cout << "Il n'y a pas d'image dont le coût est compris dans l'intervalle 10 euros<= prix <= 99.99 euros" << endl ;
  break ;

  case 3 : 

  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetPrix() >100)
    {
      cpt+=1 ;
      _bib.at(i).AffichDescip();
    }
  }
  if(cpt == 0)
    cout << "Il n'y a pas d'image dont le coût est supérieur à 100 euros" << endl ;
  break ;

  case 4 : 
  cout << "Saisissez la borne inférieure de votre intervalle de prix : Prix_min = " ;
  cin >> prixmin ;
  cout << "Saisissez la borne inférieure de votre intervalle de prix : Prix_max = " ;
  cin >> prixmax ;
  while(prixmax<=prixmin){
  cout << "/! Vos choix sont incorrects, veuillez recommencer" << endl ;
  cout << "Saisissez la borne inférieure de votre intervalle de prix : Prix_min = ";
  cin >> prixmin ;
  cout << "Saisissez la borne supérieure de votre intervalle de prix : Prix_max = ";
  cin >> prixmax ;}
  for(i = 0 ; i < _bib.size() ; i++)
  {
    Des=_bib.at(i).GetDesc();
    if(Des.GetPrix() > prixmin && Des.GetPrix() < prixmax)
    {
      cpt+=1 ;
      
      _bib.at(i).AffichDescip();
    }
  }
    if(cpt == 0)
    cout << "Il n'y a pas d'image dont le coût est compris sur l'intervalle "<< prixmin << " < prix < " << prixmax << endl ;
  break ;

  case 5 : 
  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetPrix() == 0)
    {
      cpt+=1 ;
      _bib.at(i).AffichDescip();
    }
  }
  if(cpt == 0)
    cout << "Il n'y a pas d'image gratuite dans la bibliothèque" << endl ;
  break ;
}
}
void Biblio::SousTrierAcces()
{
unsigned int i,choix,cpt = 0 ;
Ftech Des;

cout << "Tapez 1 si vous voulez voir les images dont l'accès est 'O' : ouvert aux utilisateurs de niveau 1 et 0 ou Tapez 2 pour les images d'accès 'R' : restreint aux utilisateurs de niveau 0" << endl ;
cin >> choix ;
cout <<"--->  ";

while(choix != 1 && choix != 2){
cout << "Votre choix est erronné /! ... Rappel : "<< endl << "Tapez 1 si vous voulez voir les images dont l'accès est 'O' : ouvert aux utilisateurs de niveau 1 et 0 ou Tapez 2 pour les images d'accès 'R' : restreint aux utilisateurs de niveau 0" << endl ;
cout <<"--->  ";
cin >>choix;
}

switch(choix){ 
case 1 : 
  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetAcces() == 'O'){
      cpt+=1 ;
    _bib.at(i).AffichDescip();
    }
  }
  if(cpt == 0)
    cout << "Il n'y a pas d'image dont le droit d'acces est 'O'" << endl ;
  break ;

case 2 : 
  for(i = 0 ; i < _bib.size() ; i++){
    Des=_bib.at(i).GetDesc();
    if(Des.GetAcces() == 'R'){
      cpt+=1 ;
    _bib.at(i).AffichDescip();
    }
  }
if(cpt == 0)
    cout << "Il n'y a pas d'image dont le droit d'acces est 'R'" << endl ;
  break ;
}
}

void Biblio::SousTrierDate()
{
unsigned int i,cpt = 0 ;
Ftech Des ;
unsigned int jour1, jour2, mois1, mois2, annee1, annee2 ;
  
  cout << "Saisie de votre intervalle de dates : " << endl ;
  cout << "1ère date : " << endl ;
  cout << "Saisie du jour : " << endl ;
  cin >> jour1 ;
  cout << "Saisie du mois : " << endl ;
  cin >> mois1 ;
  cout << "Saisie de l'année : " << endl ;
  cin >> annee1 ;
  
  cout << "2ème date : " << endl ;
  cout << "Saisie du jour 2 : " << endl ;
  cin >> jour2 ;
  cout << "Saisie du mois 2 : " << endl ;
  cin >> mois2 ;
  cout << "Saisie de l'année 2 : " << endl ;
  cin >> annee2 ;

  while((jour1 <= 0 || jour1>31) || (jour2 <= 0 || jour2>31) || (mois1 <= 0 || mois1 > 12) || (mois2 <= 0 || mois2 > 12) || (annee1 < 1861 || annee2 > 2019)){
  cout << "Saisie erronée, veuillez recommencer : " << endl ;
  cout << "Saisie de votre intervalle de dates : " << endl ;
  cout << "1ère date : " << endl ;
  cout << "Saisie du jour : " << endl ;
  cin >> jour1 ;
  cout << "Saisie du mois : " << endl ;
  cin >> mois1 ;
  cout << "Saisie de l'année : " << endl ;
  cin >> annee1 ;
  
  cout << "2ème date : " << endl ;
  cout << "Saisie du jour : " << endl ;
  cin >> jour2 ;
  cout << "Saisie du mois : " << endl ;
  cin >> mois2 ;
  cout << "Saisie de l'année : " << endl ;
  cin >> annee2 ;
}
//concaténation des éléments saisis dans un entier

float date1, date2, jour, mois, annee, date_test ;
//concaténation des éléments de la date dans un seul nombre pour comparaison
date1 = annee1*10000 + mois1*100 + jour1 ;
date2 = annee2*10000 + mois2*100 + jour2 ;

  for(i = 0 ; i < _bib.size() ; i++)
  {
    Des=_bib.at(i).GetDesc() ;
  jour = Des.GetJour() ;
  mois = Des.GetMois() ;
  annee = Des.GetAnnee() ;

  date_test = annee*10000 + mois*100 + jour ;
  
    if(date_test >= date1 && date_test <= date2) 
    {
      cpt+=1 ;
      _bib.at(i).AffichDescip();
    }
  }
    if(cpt == 0)
    cout << "Il n'y a pas d'image sur votre intervalle de dates : " << jour1 << "/" << mois1 << "/" << annee1 << " et " << jour2 << "/" << mois2 << "/" << annee2 << endl ; 

}
void AfficheEntete()
{
  cout<<"\033[100;1m"<<endl;
  cout<<"_____________________________________________________________________________________"<<endl;
  cout<<endl;
  cout<<"N°"<<" | "<<"Titre"<<"              | "<<"Source"<<"             | ";
  cout<<"Auteur"<<"   |"<<"O/R"<<"   | "<<"Prix"<<"   | "<<"Date"<<endl;
  cout<<"_____________________________________________________________________________________"<< endl;
  cout<<"\033[00m"<<endl<<endl;
}
