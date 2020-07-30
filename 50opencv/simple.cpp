#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
	Mat src = imread("E:/test.jpg");

	// 判读读取是否正确，文件不存在
	if (src.empty()){
		cout << "src read error" << endl;
		return -1;
	}

	// uchar* data; 头指针
	if (!src.data){
		cout << "src read error" << endl;
		return -1;
	}

	// imshow("test",src);

	// 获取信息
	int cols = src.cols;// 宽
	int rows = src.rows;// 高
	int chnnales = src.channels();// 颜色通道

	// Mat的构造函数
	// CV_8UC1 1个颜色的通道  (0-255)
	// CV_8UC2 2个颜色的通道  16位 RGB565
	// CV_8UC3 3个颜色的通道  24位
	// CV_8UC4 4个颜色的通道  32位 ARGB8888
	// 匹配上 Java Bitmap 的颜色通道 RGB565 ARGB8888
	// Scalar 指定颜色

	// 第一个参数 rows 高，第二个参数 cols 宽
	Mat mat(500,300,CV_8UC1,Scalar(255));

	// Size 第一个参数是 width , 第二个参数是 height
	Mat mat1(Size(300,500),CV_8UC1,Scalar(255));

	//三颜色通道
	Mat mat2(Size(300,500),CV_8UC3,Scalar(255,0,255));

	// cout << mat2 << endl;

	// 拷贝构造函数，但是不会去拷贝内容操作的还是原来的图
	// Mat dst(src);
	// Mat dst = src;

	// 会拷贝内容
	Mat dst;
	// src.copyTo(dst);
	dst = src.clone();

	imshow("test", mat2);

	cout << cols << "," << rows << "," << chnnales << endl;

	waitKey(0);
	return 0;
}