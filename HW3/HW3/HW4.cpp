#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/types_c.h>
#include <Windows.h>

using namespace cv;
using namespace std;

// 1~3차원 히스토그램 계산 함수
void calc_histo(const Mat image, Mat& hist, Vec3i bins, Vec3f range, int dims = 2)
{
	int sizes[] = { bins[0], bins[1], bins[2] };
	hist = Mat(dims, sizes, CV_32F, Scalar(0));		// 히스토그램 누적 행렬

	Vec3f  gap(0, 0, 0);
	for (int i = 0; i < dims; i++) {
		if (bins[i] > 0)
			gap[i] = range[i] / (float)bins[i];		// 계급 간격
	}

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++)
		{
			int idx[2] = { 0 };
			for (int c = 0; c < dims; c++) {
				int tmp = image.at<uchar>(i, j * image.channels() + c);
				idx[c] = tmp / gap[c];
			}
			hist.at<float>(idx)++;
		}
	}
}

void calc_Histo(const Mat& img, Mat& hist, Vec3i bins, Vec3f range, int _dims)
{
	int 	dims = (_dims <= 0) ? img.channels() : _dims;// 히스토그램 차원수
	int		channels[] = { 0, 1, 2 };		// 채널 목록
	int		histSize[] = { bins[0], bins[1], bins[2] };

	float  range1[] = { 0, range[0] };
	float  range2[] = { 0, range[1] };
	float  range3[] = { 0, range[2] };
	const float* ranges[] = { range1, range2, range3 };	// 모든 채널 화소범위

	calcHist(&img, 1, channels, Mat(), hist, dims, histSize, ranges);
}

Mat draw_histo(Mat hist)
{
	if (hist.dims != 2) {
		cout << "히스토그램이 2차원 데이터가 아닙니다." << endl;
		exit(1);
	}
	float ratio_value = 512.f;			// 휘도 범위 스케일 비율
	float ratio_hue = 180.f / hist.rows;		// 색상 범위 스케일 비율
	float ratio_sat = 256.f / hist.cols;		// 채도 범위 스케일 비율

	Mat graph(hist.size(), CV_32FC3);
	for (int i = 0; i < hist.rows; i++) {
		for (int j = 0; j < hist.cols; j++)
		{
			float value = hist.at<float>(i, j) * ratio_value;// 빈도값
			float hue = i * ratio_hue;		      // 색상값
			float sat = j * ratio_sat;		      // 채도값
			graph.at<Vec3f>(i, j) = Vec3f(hue, sat, value);
		}
	}

	graph.convertTo(graph, CV_8U);
	cvtColor(graph, graph, CV_HSV2BGR);		// HSV →BGR 컬러변환
	resize(graph, graph, Size(0, 0), 20, 20, INTER_NEAREST);// 그래프 크기변경
	return graph;
}

int main()
{
	Mat image = imread("..\\color_space.jpg", IMREAD_COLOR);	// 명암도 영상 로드
	CV_Assert(!image.empty());			// 영상 예외처리

	Vec3i bins(16, 16, 16);			// 히스토그램 계급 개수 
	Vec3f ranges(256, 256, 256);			// 빈도 범위

	Mat hsv, hist;
	calc_Histo(image, hist, bins, ranges, 2);	// 2차원 히스토그램 계산
	//calc_histo(image, hist, bins, ranges, 2);	// 2차원 히스토그램 계산

	cout << hist << endl;
	imshow("image", image);
	imshow("Historgram", draw_histo(hist));

	waitKey();

	return 0;
}