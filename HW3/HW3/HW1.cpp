#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main()
{
	Rect2f rect(Point2f(30, 40), Size2f(100, 200));
	cout << "rect = " << rect << endl;

	rect += Point2f(10, 10);
	rect += Size2f(20, 30);
	cout << "rect = " << rect << endl;

	return 0;
}
