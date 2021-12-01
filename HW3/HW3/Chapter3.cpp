#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>


using namespace std;
using namespace cv;
///////////// RESIZE AND CROP

int main() {

	string path = "..\\..\\..\\Users\\MSI\\Downloads\\OpenCV source files\\ch04\\utils\\airplane.bmp";
	Mat img = imread(path);
	Mat imgResized, imgCrop;
	//cout << img.size() << endl;
	resize(img, imgResized, Size(), 2,2 ); //Import image and resize it with resize(input image, output image, size of the img at this point, You can also resize with scales
	//Scale is more convinient unless you have to resize your image with and specific size

	Rect roi(120, 100, 400, 200);//x, y, widht, height
	imgCrop = img(roi);//Rectanguel
	imshow("Image", img);
	imshow("ImageResized", imgResized);
	imshow("Image Crop", imgCrop);
	
	waitKey(0);
}