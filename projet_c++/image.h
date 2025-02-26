#ifndef __image_h
#define __image_h


#include <stdio.h>
#include <stdlib.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/opencv.hpp>
#include "ftech.h"

using namespace cv;
using namespace std;

class Image {

		Ftech _descript;
		Mat _img;

	public:
		
		Image(string nomfich, unsigned int num);
		Image(unsigned int num);
		Image();

		// Getters
		Mat GetImg();

		Ftech GetDesc();
		// Setters
		void SetImg( Mat img);
		void SetDesc(Ftech descript);
		void SetNumero(unsigned int num);


		//Autres Méthodes
		void Modif();
		void AffichDescip();
		void ChargeImage();
		void TraitementLapl(int connex);
		void conv33() ;
		void HoughTransforme();
		void Histogram();

};
int Max(int a,int b);
int Min(int a,int b);



#endif
