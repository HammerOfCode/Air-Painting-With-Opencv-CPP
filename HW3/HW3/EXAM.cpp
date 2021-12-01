#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

void Rect_a() {

}


int main()
{
	Rect2f rect_a(Point2f(20, 15), Size2f(150, 250));
	
	

	Rect2f rect_b;
	rect_a += Point2f(50, 30);
	rect_b = rect_a;
	rect_b += Size2f(50,100);
	Rect2f rect_c =rect_b;
	cout << "rect_a = " << rect_a << endl;
	cout << "rect_b = " << rect_b << endl;
	cout << "rect_c = " << rect_c << endl;

	vector <Rect2f> rects;
	rects.push_back(rect_a);
	rects.push_back(rect_b);
	rects.push_back(rect_c);


	for (int i = 0; i < (float)rects.size(); i++) {
		cout << format("rect[%d] = ", i) << rects[i] << endl;
	}
	return 0;
	FileStorage fs("Rectangles", FileStorage::WRITE);
	waitKey(700000);
	return 0;
}
