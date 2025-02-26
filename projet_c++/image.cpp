#include "image.h"
#include "ftech.h"


Image::Image(string nomfich, unsigned int num):_descript(num)
{
	Mat img = imread(nomfich, 1);
	_img = img;
}

Image::Image(unsigned int num):_descript(num)
{
}
Image::Image()
{
	Ftech tech;
	Mat img;
	_descript=tech;
	_img=img;

}

//Getters

Mat Image::GetImg()
{
	return _img;
}

Ftech Image::GetDesc()
{
	return _descript;
}

//Setters

void Image::SetImg( Mat img)
{
     _img=img;
}
void Image::SetDesc(Ftech descript)
{
	_descript=descript;
}


void Image::ChargeImage()
{
	string chemin;
	chemin=_descript.GetChemin();
	chemin="Images/"+chemin;
	_img=imread(chemin);
	 
}


 void Image::Modif()
{
	int choix = 7;
	bool stop = 1;
	string acc_str;
	char acc;
	

	while(stop)
		{
		cout << "Quel élément de l'image modifier ?" << endl;
		cout << "1 - le Titre " << endl << "2 - l'Auteur " << endl << "3 - la Source" << endl;
		cout << "4 - la Date " << endl << "5 - le Prix " << endl <<  "6 - l'Accès " <<  endl;
		cout << "0 - Annuler (Retour Menu) " << endl;	
		cin >> choix;

		while((choix < 0) || (choix > 6))
			{
			cout << "Choix invalide, veuillez saisir un nombre entre 0 et 6" << endl;
			cin >> choix;
			}
			
		
		switch(choix){
			case 1 :
				_descript.SetTitre();
				break;
			case 2 :
				_descript.SetAuth();
				break;
			case 3 :
				_descript.SetSource();
				break;
			case 4 :
				_descript.SetDate();
				break;
			case 5 :
				_descript.SetPrix();
				break;
			case 6 :
				cout << "Le droit d'accès actuel est : " << _descript.GetAcces() << endl;
				cout << "Quel type d'accès voulez vous imposer pour cet image ? (O/R) " << endl;
				
				cin >> acc_str;
				acc = acc_str[0];
				while(((acc != 'O') && (acc != 'R')) )// ||  (acc_str.size() > 2))
					{
					cout << "Réponse invalide veuillez saisir la lettre O ou la lettre R" << endl;
					cin >> acc;
					}
				_descript.SetAcces(acc);
				break;
			default :
				stop = 0;
				break;

			}
		
		if(choix != 0)
			{
				cout << "Souhaitez vous effectuer une autre modification ? (O/N)" << endl;
			cin >> acc_str;
			
			while((acc_str.size() != 1) || (acc_str[0] != 'N' && acc_str[0] != 'O'))
				{
				cout << "Réponse invalide veuillez saisir la lettre O ou la lettre N" << endl;	
				cin >> acc_str;
				}
			acc =  acc_str[0];
			if(acc == 'N')
				{
				stop = 0;
				}
			}
		}
}


void Image::AffichDescip()
{
	_descript.AffichDescip1();
}

void Image::TraitementLapl(int connex)
{
	Mat Lapl;
	Mat img;// = _img;
	
	cvtColor(_img, img, CV_BGR2GRAY);
	Mat imo = Mat::zeros(img.size(), CV_8U);

	int Val2, Val;

	int Seuil = 300;
//cout << connex << endl;

	if(connex == 8) 
		{
		Lapl = (Mat_<double>(3,3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
		}
	else
		{
		Lapl = (Mat_<double>(3,3) << 0, -1, 0, -1, 4, -1, 0, -1, 0); 
		}

cout << "Votre noyau = " << endl << Lapl << endl;

// Pixel du coin haut gauche :
	Val = img.at<char>(0,0)*4 + img.at<char>(0,1) * -2 + img.at<char>(1,0) * -2;
	if((Val < -Seuil) || (Val > Seuil))
		{
		imo.at<unsigned char>(0,0)= 255;
		}

// Pixel du coin haut droit :
	Val = img.at<char>(0, img.size().width-1)*4 + img.at<char>(0, img.size().width -2) * -2 + img.at<char>(1, img.size().width-1) * -2;
	if((Val < -Seuil) || (Val > Seuil))
		{
		imo.at<unsigned char>(0, img.size().width-1)= 255;
		}

// Pixel du coin bas gauche :
	Val = img.at<char>(img.size().height-1,0)*4 + img.at<char>(img.size().height-1,1) * -2 + img.at<char>(img.size().height-2,0) * -2;
	if((Val < -Seuil) || (Val > Seuil))
		{
		imo.at<unsigned char>(img.size().height-1,0)= 255;
		}

// Pixel du coin bas droit :
	Val = img.at<char>(img.size().height-1, img.size().width-1)*4 + img.at<char>(img.size().height-1, img.size().width -2) * -2 + img.at<char>(img.size().height-2, img.size().width-1) * -2;
	if((Val < -Seuil) || (Val > Seuil))
		{
		imo.at<unsigned char>(img.size().height-1, img.size().width-1)= 255;
		}

// Pixels de la première et de la dernière ligne
	for (int y = 1 ; y < img.size().width - 1; y++)
		{
		Val = img.at<char>(img.size().height-1, y) * 5;
		Val2 = img.at<char>(0, y) * 5;
		for(int m = 0 ; m < 2 ; m++)
			{
			for(int k = -1 ; k < 2 ; k++)
				{
				if((m != 0) && (k !=0))
					{
					Val += img.at<char>(img.size().height-1-m, y+k) * Lapl.at<double>(1-m, k+1);
					Val2 += img.at<char>(m, y+k) * Lapl.at<double>(1+m, k+1);	
					}
				}
			}
		if((Val < -Seuil) || (Val > Seuil))
			{
			imo.at<unsigned char>(img.size().height-1,y)= 255;
			}
		if((Val2 < -Seuil) || (Val2 > Seuil))
			{
			imo.at<unsigned char>(0,y)= 255;
			}
		}


// Pixels de la première et de la dernière colonne
	for (int x = 1 ; x < img.size().width-1; x++)
		{
		Val = img.at<char>(x, img.size().width-1) * 5;
		Val2 = img.at<char>(x, 0) * 5;
		for(int m = 0 ; m < 2 ; m++)
			{
			for(int k = -1 ; k < 2 ; k++)
				{
				if((m != 0) && (k !=0))
					{
					Val += img.at<char>(x+k, img.size().width-1-m) * Lapl.at<double>(k+1, -m);
					Val2 += img.at<char>(x+k, m) * Lapl.at<double>(k+1,1-m);	
					}
				}
			}
		if((Val < -Seuil) || (Val > Seuil))
			{
			imo.at<unsigned char>(x, img.size().width-1)= 255;
			}
		if((Val2 < -Seuil) || (Val2 > Seuil))
			{
			imo.at<unsigned char>(x,0)= 255;
			}
		}


// Pixels du centre
	for (int y = 1; y < img.size().width; y++)
		{
		for (int x = 1; x < img.size().height-1; x++)
			{
			Val = 0;
			for(int k = -1; k < 2; k++)
				{
				for(int m = -1; m < 2; m++)
					{
					Val += img.at<char>(x+k, y+m)*Lapl.at<double>(k+1, m+1);
					}
				}
			if(((Val)  < -Seuil ) || ((Val) > Seuil))
				{
				imo.at<unsigned char>(x,y) = 255;
				}
			}
		}
	
	//affichage
	
	namedWindow( "Contours détectés", WINDOW_AUTOSIZE ); // Création d'une fenêtre pour l'affichage
	imshow("Contours détectés", imo);
	waitKey(0); // Wait for a keystroke in the window
}
void Image::conv33()
{
Mat img;
cvtColor(_img, img, CV_BGR2GRAY);
img = Mat_<float>(img) ;

int krows = 3 ; //dimensions du kernel (fixes)
int kcols = 3 ;
int kCenterX = 1; //kernel appliqué en son centre (fixé)
int kCenterY = 1;

int i,j,n,m,mm,nn, ii, jj,choix,choix2,ind =0, ind2 = 0 ; 

cv::Mat moyenneur(3,3,CV_32FC1,0.0f); //init des 2 kernels contenant des valeurs réelles
cv::Mat gaussien(3,3,CV_32FC1,0.0f);

//saisie en dur d'une bibliothèque de 8 kernels

Mat prewitt_x, prewitt_y, sobel_x, sobel_y, laplacien_4, laplacien_8 ;
moyenneur = (Mat_<float>(3,3) << 1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9,1.0/9);
gaussien = (Mat_<float>(3,3) << 1.0/32,1.0/8,1.0/32,1.0/8,3.0/8,1.0/8,1.0/32,1.0/8,1.0/32);
prewitt_x = (Mat_<float>(3,3) << -1,-1,-1,0,0,0,1,1,1);
prewitt_y = (Mat_<float>(3,3) << -1,0,1,-1,0,1,-1,0,1);
sobel_x = (Mat_<float>(3,3) << -1,-2,-1,0,0,0,1,2,1);
sobel_y = (Mat_<float>(3,3) << -1,0,1,-2,0,2,-1,0,1);
laplacien_4 = (Mat_<float>(3,3) << 0,-1,0,-1,4,-1,0,-1,0);
laplacien_8 = (Mat_<float>(3,3) << -1,-1,-1,-1,8,-1,-1,-1,-1);

//concaténation dans un vecteur contenant les 8 kernels

vector<Mat> _matkernel;
_matkernel.push_back(moyenneur), _matkernel.push_back(gaussien), _matkernel.push_back(prewitt_x), _matkernel.push_back(prewitt_y), _matkernel.push_back(sobel_x),_matkernel.push_back(sobel_y),_matkernel.push_back(laplacien_4), _matkernel.push_back(laplacien_8)  ;
/*for(i_vect = 0 ; i_vect<_matkernel.size() ; i_vect++)
cout << "Vector = " << _matkernel.at(i_vect) << endl ;*/
Mat kernel ;
kernel = (Mat_<float>(3,3) << 0,0,0,0,0,0,0,0,0); 
float saisie[9] = {0} ;

//choix entre saisie utilisateur ou accès au vecteur de kernels
cout << "Tapez (1) si vous voulez saisir un kernel (noyau) ou (2) si vous voulez en utiliser un déjà prédéfini (cf liste suivante) : |moyenneur| |laplacien_4| |laplacien_8| |prewitt_x| |prewitt_y| |sobel_x| |sobel_y| "<< endl ;
cin >> choix ;
while(choix != 1 && choix !=2){
cout << "Erreur de saisie ! Recommencez. Rappel : Tapez (1) si vous voulez saisir un kernel (noyau) ou (2) si vous voulez en utiliser un déjà prédéfini (cf liste suivante) : |moyenneur| |laplacien_4| |laplacien_8| |prewitt_x| |prewitt_y| |sobel_x| |sobel_y| " << endl ;
cin >> choix;}

//saisie du noyau par l'utilisateur
if(choix == 1)
{
for(i=0; i < 3; i++)              // indice de ligne du kernel
{   ind += 1 ;
    for(j=0; j < 3; ++j)          // indice de colonne du kernel
    { ind2 += 1 ;
cout << "Saisie de l'élément ("<<j<<","<<ind-1<<") : "; //ajustement pour affichage
//cout << "ind2 = " << ind2 << endl ;
cin >> saisie[ind2-1] ;
while (cin.fail() ) 
        {  
            cout << "Saisie incorrecte, recommencez : " << endl;  
            cin.clear();  
            cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
	    cout << "Saisie de l'élément ("<<j<<","<<ind-1<<") : ";
	    cin >> saisie[ind2-1] ; 	
        } 
;}}
kernel =(Mat_<float>(3,3) << saisie[0],saisie[1],saisie[2],saisie[3],saisie[4],saisie[5],saisie[6],saisie[7],saisie[8]); 
cout << endl ;
}
//choix du kernel de la bibliothèque à appliquer à l'image
if (choix == 2){
cout << "Tapez : (1) moyenneur (2) gaussien  (3) prewitt_x (4) prewitt_y (5) sobel_x (6) sobel_y (7) laplacien_4 (8) laplacien_8" << endl ;
cin >> choix2 ;
//vérification du choix utilisateur
while(choix2 != 1 && choix2 != 2 && choix2 != 3 && choix2 != 4 && choix2 != 5 && choix2 != 6 && choix2 != 7 && choix2 !=8){
cout <<"|Erreur de saisie| Veuillez recommencez ! | Tapez : (1) moyenneur (2) gaussien  (3) prewitt_x (4) prewitt_y (5) sobel_x (6) sobel_y (7) laplacien_4 (8) laplacien_8" << endl ;
cin >> choix2 ;}
kernel =_matkernel.at(choix2-1) ;
}

cv::Mat out(img.rows,img.cols, CV_32FC1,0.0f); //matrice en sortie

//algorithme

for(i=0; i < img.rows; i++)              // lignes
{
    for(j=0; j < img.cols; ++j)          // colonnes
    {
        for(m=0; m < krows; ++m)     // lignes du kernel
        {
            mm = krows - 1 - m;      // Indices des lignes du kernel retournée à 180°

            for(n=0; n < kcols; ++n) // colonnes du kernel
            {
                nn = kcols - 1 - n;  // Indices des colonnes du kernel retournée à 180°

                // Indices correspondants aux zones d'applications du kernel
                ii = i + (kCenterY - mm);
                jj = j + (kCenterX - nn);

                // Pour éviter les calculs à l'extérieur des dimensions de l'image (test)
                if( (ii >= 0 && ii < img.rows) && (jj >= 0 && jj < img.cols) )
                    out.at<float>(i,j) += img.at<float>(ii,jj) * kernel.at<float>(mm,nn);
            }
        }
    }
}
//affichage
Mat dst;
cv::normalize(out, dst, 1, 0,NORM_INF, CV_32FC1);
namedWindow( "Display window", WINDOW_AUTOSIZE ); // Création d'une fenêtre pour l'affichage
imshow("Display window", dst);
waitKey(0); // Wait for a keystroke in the window
}



void Image::HoughTransforme(){

Scalar Intensite;  
Mat image,src_gris,detection_Contour,src=_img;  
cvtColor( src, src_gris, CV_BGR2GRAY );
blur( src_gris, detection_Contour, Size(3,3) );
Canny(detection_Contour, detection_Contour, 100,200); 
image= detection_Contour;   

 
            // La taille de l'image 
            int nColonne  = image.cols;                  
            int nligne  = image.rows; 
            int maxTheta = 360;
            int maxRho =sqrt(nColonne*nColonne +nligne*nligne);
            Mat Acc=Mat::zeros(maxTheta,maxRho,CV_8UC1); //CV_8UC1= image mono-canal 8-bit (image en ni-veaux de gris)

            // Lecture pixel par pixel de l'image  
            for (int y = 0; y < nColonne ; y++)                 
            {                                                
                for (int x = 0; x < nligne; x++)
                {   Intensite=image.at<uchar>(x,y);
                    if (Intensite.val[0]>0)//if a pixel is black, skip it.
                    {
                         
                        
                          for (int theta =0; theta <maxTheta; theta++)
                            {   
                                // Transformer theta en radian avec theta varie de -90 à 90
                                float rad = (3.14*(theta)/180)- (3.14);
                                //Calcule du rho
                                int rho = round(x*cos(rad) + y*sin(rad)); 
                                 
                                if (rho > 0) 
                                Acc.at<uchar>(theta,rho,CV_8UC1)++;
                            
                            }
                                            
                        }
                }
            }
  
int minVal = 0;
int maxVal = 0;

        for (int j = 0; j < maxRho; j++)
        {
            for (int i = 0; i < maxTheta; i++)
            {
                int conv =Acc.at<uchar>(i, j,CV_8UC1); 

                minVal = Min(minVal, conv);
                maxVal = Max(maxVal, conv);
            }
        }

        int maxRange = 255;
 

 
        for (int j = 0; j < maxRho; j++)
        {
            for (int i = 0; i < maxTheta; i++)
            {
               Acc.at<uchar>(i,j, CV_8UC1) = maxRange * (Acc.at<uchar>(i,j, CV_8UC1) - minVal) / (maxVal - minVal);
 
            }
        }

imshow("La transformée de Hough ", Acc);
waitKey();
} 

void Image::Histogram(){
int histogram[256];          // allocation de la mémoire 
    Mat I=_img;  //Charger l'image
    Mat Igray;
	cvtColor(I,Igray,COLOR_BGR2GRAY); //Convertir l'image en niveaux de gris
	I=Igray;


  
    // intialiser toutes les vlaleurs d'intensité par 0
    for(int i = 0; i < 255; i++)
    	histogram[i] = 0; 


    //lire l'intensité de toutes les pixles
    for(int i = 0; i < I.rows; i++)
        for(int j = 0; j < I.cols; j++)
            histogram[(int) I.at<uchar> (i,j)]++; 


   // Valeur Max d'Intensité
    int max = histogram[0];
    for(int i = 1; i < 256; i++)
       {
        if(max < histogram[i])
          max = histogram[i];
       }


   //  Rendre l'intensité d'Image entre [0,255] 
    Mat histI(256, 256, CV_8UC1, Scalar(255)); //255 pour précisser la taille de notre fentre d'affichage 

    for(int i = 0; i < 255; i++)
        histogram[i] = ((double)histogram[i]/max)*histI.rows;  



    // dessiner l'intensité d'histogram
    for(int i = 0; i < 255; i++)
    {
	 line( histI, Point(i, 256),Point(i, 256 - histogram[i]),Scalar(0), 0 );    
    }


    // affichage l'histogram
    namedWindow("L'intensité de l'histogram");
    imshow("L'intensité de l'histogram", histI);

    waitKey();  // Avoir le temps de voir l'histogram
  }

int Max(int a,int b){
if(a>b)
{return a;}
else
{return b;}
}
int Min(int a,int b){
if(a<b)
{return a;}
else
{return b;}
}
