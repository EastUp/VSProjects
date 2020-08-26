#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main(){
	Mat src = imread("E:/copy.png");

	if (src.empty()){
		cout << "src read error" << endl;
	}
	imshow("src", src);

	// ��ֵģ��
	Mat dst;
	// Size��w,h��ֻ���ǻ��������������ҵ����ĵ�
	// Point(-1,-1) �������ĵ�
	blur(src,dst,Size(151,151),Point(-1,-1));
	imshow("dst", dst);

	// ��˹ģ��
	Mat gaussian;
	// sigmaX sigmaY ���� ����
	// sigmaY ��������� sigmaX һ��
	// ��� sigmaX <= 0 ,�Լ������ 0.3*((ksize-1)*0.5 - 1) + 0.8
	// sigmaX ԽСԽûЧ��
	GaussianBlur(src, gaussian, Size(151, 151), 0);
	imshow("gaussian", gaussian);

	waitKey(0);
	return 0;
}