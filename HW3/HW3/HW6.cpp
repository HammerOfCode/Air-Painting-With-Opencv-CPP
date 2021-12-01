/**#include<iostream>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/objdetect/objdetect.hpp>
using namespace cv;
using namespace std;

int main() {
	Mat frame;//declaring a matrix to video frame in it//
	namedWindow("Detect");//Declaring a window to show our work//
	VideoCapture image(0);//capturing video from default camera//
	if (!image.isOpened()) { //Error message if video source is not found//
		cout << "Couldn't load video from the source.Make sure your camera is working properly." << endl;
		system("pause");
		return 0;
	}
	double height = image.set(CAP_PROP_FRAME_HEIGHT, 480);//setting up height of each frame//
	double width = image.set(CAP_PROP_FRAME_WIDTH, 640);//setting up width of each frame//
	CascadeClassifier face_cascade, eyes_cascade;//declaring a CascadeClassifier object//
	face_cascade.load("C:\\opencv-4.x\\data\\haarcascades\\haarcascade_frontalface_alt.xml");//loading the cascade classifier//
	eyes_cascade.load("C:\\opencv-4.x\\data\\haarcascades\\haarcascade_eye.xml");
	while (true) {
		bool temp = image.read(frame);//loading video frames from source to our matrix named frame//
		vector<Rect>faces;//Declaring a vector named faces//
		
		face_cascade.detectMultiScale(frame, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(100, 100));//detecting the face
		
		for (int i = 0; i < faces.size(); i++) { //for locating the face
			Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);//getting the center of the face//
			ellipse(frame, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 0), 4, 8, 0);//draw an ellipse on the face//
			
			Mat faceROI = frame(faces[i]);//Taking area of the face as Region of Interest for eyes//
			vector<Rect>eyes;//declaring a vector 
			eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(5, 5));//detect eyes in every face//
			for (size_t j = 0; j < eyes.size(); j++) { //for locating eyes//
				Point center(faces[i].x + eyes[j].x + eyes[j].width * 0.5, faces[i].y + eyes[j].y + eyes[j].height * 0.5);//getting the centers of both eyes//
				int radius = cvRound((eyes[j].width + eyes[j].height) * 0.25);//declaring radius of the eye enclosing circles//
				circle(frame, center, radius, Scalar(0, 255, 0), 4, 8, 0);//drawing circle around both eyes//
			}
		}
		imshow("Detect", frame);//showing result in window named 'Detect'//
		if (waitKey(30) == 27) { //wait time for each frame is 30 milliseconds//
			break;
		}
	}
	return 0;
}**/
/**
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char** argv)
{
	/// Use the cmdlineparser to process input arguments
	CommandLineParser parser(argc, argv,
		"{ help h            |      | show this message }"
		"{ video v           |      | (required) path to video }"
	);

	/// If help is entered
	if (parser.has("help")) {
		parser.printMessage();
		return 0;
	}

	/// Parse arguments
	string video_location(parser.get<string>("video"));
	if (video_location.empty()) {
		parser.printMessage();
		return -1;
	}

	/// Create a videoreader interface
	VideoCapture cap(video_location);
	Mat current_frame;

	/// Set up the pedestrian detector --> let us take the default one
	HOGDescriptor hog;
	hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

	/// Set up tracking vector
	vector<Point> track;

	while (true) {
		/// Grab a single frame from the video
		cap >> current_frame;

		/// Check if the frame has content
		if (current_frame.empty()) {
			cerr << "Video has ended or bad frame was read. Quitting." << endl;
			return 0;
		}

		/// run the detector with default parameters. to get a higher hit-rate
		/// (and more false alarms, respectively), decrease the hitThreshold and
		/// groupThreshold (set groupThreshold to 0 to turn off the grouping completely).

		///image, vector of rectangles, hit threshold, win stride, padding, scale, group th
		Mat img = current_frame.clone();
		resize(img, img, Size(img.cols * 2, img.rows * 2));

		vector<Rect> found;
		vector<double> weights;

		hog.detectMultiScale(img, found, weights);

		/// draw detections and store location
		for (size_t i = 0; i < found.size(); i++)
		{
			Rect r = found[i];
			rectangle(img, found[i], cv::Scalar(0, 0, 255), 3);
			stringstream temp;
			temp << weights[i];
			putText(img, temp.str(), Point(found[i].x, found[i].y + 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255));
			track.push_back(Point(found[i].x + found[i].width / 2, found[i].y + found[i].height / 2));
		}

		/// plot the track so far
		for (size_t i = 1; i < track.size(); i++) {
			line(img, track[i - 1], track[i], Scalar(255, 255, 0), 2);
		}

		/// Show
		imshow("detected person", img);
		waitKey(1);
	}

	return 0;
}

**/

#include <opencv2/objdetect.hpp>

#include <opencv2/imgcodecs.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

using namespace cv;

using namespace std;


void display(Mat &im, Mat &bbox)
{
	int n = bbox.rows;
	for (int i = 0; i < n; i++)
	{
		line(im, Point2i(bbox.at<float>(i, 0), bbox.at<float>(i, 1)), Point2i(bbox.at<float>((i + 1) % n, 0), bbox.at<float>((i + 1) % n, 1)), Scalar(255, 0, 0), 3);
	}
	imshow("Result", im);
}

int main(int argc, char* argv[])
{
	// Read image
	Mat inputImage;
	if (argc > 1)
		inputImage = imread(argv[1]);
	else
		inputImage = imread("C:\\Users\\MSI\\Desktop\\BARCODE.jpg");

	QRCodeDetector qrDecoder = QRCodeDetector::QRCodeDetector();

	Mat bbox, rectifiedImage;

	std::string data = qrDecoder.detectAndDecode(inputImage, bbox, rectifiedImage);
	if (data.length() > 0)
	{
		cout << "Decoded Data : " << data << endl;

		display(inputImage, bbox);
		rectifiedImage.convertTo(rectifiedImage, CV_8UC3);
		imshow("Rectified QRCode", rectifiedImage);

		waitKey(0);
	}
	else
		cout << "QR Code not detected" << endl;
}
