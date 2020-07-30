#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
	Mat src = imread("E:/test.jpg");

	imshow("test",src);

	waitKey(0);
}