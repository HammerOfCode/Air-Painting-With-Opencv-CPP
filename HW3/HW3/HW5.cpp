#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Mat image = imread("C:\\Users\\MSI\\Downloads\\OpenCV_HMW_SRC\\opencv_logo.jpg", 1);
	Mat bgr[3], blue_img, red_img, green_img, zero(image.size(), CV_8U, Scalar(0));
	
	split(image, bgr);
	// Show individual channels
	imshow("image1", bgr[0]);
	imshow("image2", bgr[1]);
	imshow("image3", bgr[2]);

	Mat g;

	g = Mat::zeros(Size(image.cols, image.rows), CV_8UC1);

	{

		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(g);
		channels.push_back(bgr[2]);
		/// Merge the three channels
		merge(channels, red_img);
		
	}
	
	
	// Showing Green Channel
	{

		vector<Mat> channels;
		channels.push_back(g);
		channels.push_back(bgr[1]);
		channels.push_back(g);
		merge(channels, green_img);
		

	}
	// Showing Blue Channel

	{
		vector<Mat> channels;
		channels.push_back(bgr[0]);
		channels.push_back(g);
		channels.push_back(g);
		merge(channels, blue_img);
		

	}
	imshow("image", image), imshow("blue_img", blue_img);
	imshow("green_img", green_img), imshow("red_img", red_img);

	waitKey();
	return 0;
}