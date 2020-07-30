#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
	Mat src = imread("E:/test.jpg");

	// �ж���ȡ�Ƿ���ȷ���ļ�������
	if (src.empty()){
		cout << "src read error" << endl;
		return -1;
	}

	// uchar* data; ͷָ��
	if (!src.data){
		cout << "src read error" << endl;
		return -1;
	}

	// imshow("test",src);

	// ��ȡ��Ϣ
	int cols = src.cols;// ��
	int rows = src.rows;// ��
	int chnnales = src.channels();// ��ɫͨ��

	// Mat�Ĺ��캯��
	// CV_8UC1 1����ɫ��ͨ��  (0-255)
	// CV_8UC2 2����ɫ��ͨ��  16λ RGB565
	// CV_8UC3 3����ɫ��ͨ��  24λ
	// CV_8UC4 4����ɫ��ͨ��  32λ ARGB8888
	// ƥ���� Java Bitmap ����ɫͨ�� RGB565 ARGB8888
	// Scalar ָ����ɫ

	// ��һ������ rows �ߣ��ڶ������� cols ��
	Mat mat(500,300,CV_8UC1,Scalar(255));

	// Size ��һ�������� width , �ڶ��������� height
	Mat mat1(Size(300,500),CV_8UC1,Scalar(255));

	//����ɫͨ��
	Mat mat2(Size(300,500),CV_8UC3,Scalar(255,0,255));

	// cout << mat2 << endl;

	// �������캯�������ǲ���ȥ�������ݲ����Ļ���ԭ����ͼ
	// Mat dst(src);
	// Mat dst = src;

	// �´������
	Mat dst;
	// src.copyTo(dst);
	dst = src.clone();

	imshow("test", mat2);

	cout << cols << "," << rows << "," << chnnales << endl;

	waitKey(0);
	return 0;
}