//Virtual Paint
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

Mat img;
VideoCapture cap(0);
vector<vector<int>> newPoints;
//{x,y,0}(blue), {x,y,1}(pink)

//  hmin,smin,vmin,hmax, smax, vmax 
vector<vector<int>> myColors{ {77,193,162,179,255,255},//blue
								{133,35,199,179,199,255}, //pink
									{56,107,107,90,255,255}//green
	
};

vector<Scalar> myColorValues{ {255,0,0},{203,192,255},{34,139,34} };//

Point getContours(Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	drawContours(img, contours, -1, Scalar(255, 0, 255), 2);

	vector<vector<Point>> conPoly(contours.size());
	vector<Rect> boundRect(contours.size());
	
	Point myPoint(0,0);
	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			cout << conPoly[i].size() << endl;
			boundRect[i] = boundingRect(conPoly[i]);
			myPoint.x = boundRect[i].x + boundRect[i].width / 2;// Get the middle point from the bounding box
			myPoint.y = boundRect[i].y; // y is already at its point


			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);// WE WILL GET THE STARPOINT FROM THE BOUNDING BOX
			//putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}
	}
	return myPoint;
}






vector<vector<int>>  findColor(Mat img) {
	Mat imgHSV;

	cvtColor(img, imgHSV, COLOR_BGR2HSV); //HUE SATURATION VALUES
	for (int i = 0; i < myColors.size(); i++){
		Scalar lower(myColors[i][0], myColors[i][1], myColors[i][2]);
		// hmin hue minimun, smin saturation minimun, vmin value minmin
		Scalar upper(myColors[i][3], myColors[i][4], myColors[i][5]);
		Mat mask;
		inRange(imgHSV, lower, upper, mask);//inrange function to collect color img, lower limit, upper limi, OUTPUT MASK
		//imshow(to_string(i), mask); //shows the masks from the colors
		Point myPoint =   getContours(mask);//gets the contours from bounding boxes from the masks

		
		if (myPoint.x != 0 && myPoint.y != 0) {
		
			newPoints.push_back({ myPoint.x, myPoint.y,i });
		}
	}
	return newPoints;
}


void drawOnCanvas(vector<vector<int>> newPoints, vector<Scalar> myColorValues){
	for (int i = 0; i < newPoints.size();i++)
	{
		circle(img, Point(newPoints[i][0], newPoints[i][1]), 10, myColorValues[newPoints[i][2]], FILLED);
	}


	}

void main() {

	
	
	while (true)
	{
		cap.read(img);
		newPoints = findColor(img);
		drawOnCanvas(newPoints, myColorValues);
		flip(img, img, 1);
		imshow("Image", img);
		waitKey(1);
	}
}
