#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;
///////////// Draw Shapes and Text

int main() {

	//Blank Image
	Mat img(512, 512,CV_8UC3, Scalar(255,255,255));//SIZE X, SIZEY, TYPE WITH CHANNELS, COLORS WITH SCALAR FUNCTIONS, BGR

	circle(img, Point(256, 256),155, Scalar(200,150,100), FILLED);
	//We will put a circule in the box we just created /img/the point to put it/Size of the circule/ Colors with Scalar/thickness if needed or instead of thickness we can write FILLED
	rectangle(img, Point(130,226), Point(382, 300), Scalar(0,255,0), FILLED); 
		//define 2 points the bottom top left cornert bottom right corner
	line(img, Point(0, 0), Point(512, 512), Scalar(0,0,0),3);
	line(img, Point(512, 0), Point(0, 512), Scalar(0, 0, 0), 3);
	putText(img, "Hi Amigo", Point(130, 280), FONT_ITALIC, 1.8, Scalar(200, 150, 100), 2);//img, text, starting point, define the font, Scale, Scalar, thickness
	
	imshow("Image", img);

	waitKey(0);
}