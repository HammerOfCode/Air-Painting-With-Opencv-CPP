#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;
///////////// Warp Images (Deformat Imagenes)
float w = 150;
float h = 250;
Mat matrix, imgWarp;

int main() {

	string path = "Resources/cards.jpg"; 
	Mat img = imread(path);

	Point2f src[4] = { {529,142},{771,190},{405,395}, {674,457} };//source point
	//The function requires floating poiints so we will have to use Point2f, we will put the 4 points of the card, 
	//we obtained the points while using Paint
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0,h}, {w,h} };//destination points
	


	matrix = getPerspectiveTransform(src, dst);//We need to transform the Matrix
	warpPerspective(img, imgWarp,matrix,Point(w,h));
	
	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 20, Scalar(200, 150, 100), FILLED);//Draws a circle at the corner of every card

	}


	imshow("Image", img);
	imshow("Image Warp", imgWarp);
	waitKey(0);
}


