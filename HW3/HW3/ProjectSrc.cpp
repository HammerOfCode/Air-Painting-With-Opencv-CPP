//Virtual Paint
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;
//  hmin,smin,vmin,hmax, smax, vmax 
vector<vector<int>> myColors{ {64,209,151,179,255,255},//blue
								{133,35,199,179,199,255}//rosa 
};//verde

vector<Scalar> myColorValues{ {255,0,0},{203,192,255},{0,255,0} };
void findColor(Mat img){
	Mat imgHSV;

	cvtColor(img, imgHSV, COLOR_BGR2HSV); //HUE SATURATION VALUES
	for (int i = 0; i < myColors.size(); i++)
	{
	Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
	// hmin hue minimun, smin saturation minimun, vmin value minmin
	Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
	Mat mask;
	inRange(imgHSV, lower, upper, mask);//inrange function to collect color img, lower limit, upper limi, OUTPUT MASK
	imshow(to_string(i), mask);
	}
	}

void main() {

	VideoCapture cap(0);
	Mat img;
	while (true)
	{
		cap.read(img);
		findColor(img);
		imshow("Image", img);
		waitKey(1);
	}
}
