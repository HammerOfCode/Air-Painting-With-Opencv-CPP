#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;
///////////// BASIC FUNCTIONS 

void main() {

	string path = "..\\..\\..\\Users\\MSI\\Downloads\\OpenCV source files\\ch04\\utils\\airplane.bmp";
	Mat img = imread(path);
	Mat imgGray, imgBlur, imgCanny, imgDil, imgEro;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(img, imgBlur, Size(7,7), 5,0);//size of the kernel / sigma x sigma y 
	Canny(imgBlur, imgCanny, 50, 150);//threshold 1 threshhold 2
	Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5));//define the shape, define the size
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgEro, kernel);

	imshow("Image", img);
	imshow("ImageG", imgGray);
	imshow("ImageB", imgBlur);
	imshow("ImageCANNY", imgCanny);
	imshow("ImageDilate", imgDil);
	imshow("ImageEro", imgEro);

	waitKey(0);
}

