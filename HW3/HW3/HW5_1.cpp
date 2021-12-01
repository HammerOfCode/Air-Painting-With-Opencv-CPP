#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

String	title = "HW05OCV03";

int main()
{
	Mat image = imread("C:\\Users\\MSI\\Downloads\\OpenCV_HMW_SRC\\coins.jpg", 1);
	CV_Assert(image.data);

	Mat gray, th_img;
	Mat kernel(3, 3, CV_8UC1, Scalar(1));

	cvtColor(image, gray, COLOR_BGR2GRAY);		         // 명암도 변환 
	GaussianBlur(gray, gray, Size(7, 7), 2, 2);			// 블러링

	//threshold(gray, th_img, 50, 255, THRESH_BINARY); // 이진화
	threshold(gray, th_img, 130, 255, THRESH_BINARY | THRESH_OTSU); // 이진화
	morphologyEx(th_img, th_img, MORPH_OPEN, kernel, Point(-1, -1), 2);  // 열림연산

	imshow("image", image);
	imshow(title, th_img);

	waitKey();
	return 0;
}
