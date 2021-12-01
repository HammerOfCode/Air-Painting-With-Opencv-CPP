#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;
///////////// Color Detection + Tracking Bar
Mat imgHSV, mask;

int hmin=0, smin=0, vmin=0;
int hmax=179, smax=240, vmax=255;

//How to use your own values for the color detection
//The answer is trackbar


int main() {

	string path = "Resources/lambo.png";
	
	Mat img = imread(path);

	cvtColor(img, imgHSV, COLOR_BGR2HSV); //HUE SATURATION VALUES
	
	namedWindow("TrackBars", (640, 200));

	createTrackbar("Hue MIN", "TrackBars", &hmin,179); 
	//name of the trackbar, the address from the  value(the window name, address of the value(&hmin), max value for hue is 180 saturation 255
	createTrackbar("Hue MAX", "TrackBars", &hmax, 179);
	createTrackbar("SAT MIN", "TrackBars", &smin, 255);
	createTrackbar("SAT MAX", "TrackBars", &smax, 255);
	createTrackbar("VAL MIN", "TrackBars", &vmin, 255);
	createTrackbar("VAL MAX", "TrackBars", &vmax, 255);


	while (true)
	{

	



	Scalar lower(hmin, smin, vmin);
		// hmin hue minimun, smin saturation minimun, vmin value minmin
	Scalar upper(hmax, smax, vmax);



	inRange(imgHSV, lower, upper, mask);//inrange function to collect color img, lower limit, upper limi, OUTPUT MASK
	
	imshow("Image", img);
	imshow("ImageHSV", imgHSV);
	imshow("ImageMask", mask);
	waitKey(1);
	
	}
	
}

