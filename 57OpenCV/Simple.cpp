#include<iostream>
#include<opencv2/opencv.hpp>

using namespace cv;
using namespace std;

// 1. Sobel����΢���� ���Ե
/*int main(){
	Mat src = imread("E:/card1.png");

	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	//Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1); 
	//Mat dst;
	//filter2D(src,dst,src.depth(),kernel);

	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src,gaussian,Size(3,3),0);
	// 2. ת�Ҷ�
	Mat gray;
	cvtColor(gaussian, gray, COLOR_BGR2GRAY);
	// 3. ���ݶ�
	// ���� ��delta -> �ڼ������Ļ������ټ��� delta
	// ddepth : -1������ gray.depth()��ͬ��ֵ������Ӧ�ô��� gray ���ȸ��ߵ�ֵ(1 / 3=0,1f/3 = 0.3333)
	// x y �����ݶ�һ�㲻����������Scharr ��ǿ
	Mat sobel_x, sobel_y;
	Sobel(gray, sobel_x, CV_32F, 1, 0, 3);
	Sobel(gray, sobel_y, CV_32F, 0, 1, 3);

	// 4. �����ֵ (��Ϊ�е�����ֵ�����Ϊ����)
	convertScaleAbs(sobel_x, sobel_x);
	convertScaleAbs(sobel_y, sobel_y);

	// 5. �ϲ����������ͼƬ
	Mat sobel;
	addWeighted(sobel_x,0.5,sobel_y,0.5,0,sobel);

	imshow("sobel_x", sobel_x);
	imshow("sobel_y", sobel_y);
	imshow("sobel", sobel);

	waitKey(0);
	return 0;
}*/


// 1. Scharr ��ǿ���Ե
/*int main(){
	Mat src = imread("E:/card1.png");

	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	//Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	//Mat dst;
	//filter2D(src,dst,src.depth(),kernel);

	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);
	// 2. ת�Ҷ�
	Mat gray;
	cvtColor(gaussian, gray, COLOR_BGR2GRAY);
	// 3. ���ݶ�
	// ���� ��delta -> �ڼ������Ļ������ټ��� delta
	// ddepth : -1������ gray.depth()��ͬ��ֵ������Ӧ�ô��� gray ���ȸ��ߵ�ֵ(1 / 3=0,1f/3 = 0.3333)
	// x y �����ݶ�һ�㲻����������Scharr ��ǿ
	Mat scharr_x, scharr_y;
	Scharr(gray, scharr_x, CV_32F, 1, 0, 3);
	Scharr(gray, scharr_y, CV_32F, 0, 1, 3);

	// 4. �����ֵ (��Ϊ�е�����ֵ�����Ϊ����)
	convertScaleAbs(scharr_x, scharr_x);
	convertScaleAbs(scharr_y, scharr_y);

	// 5. �ϲ����������ͼƬ
	Mat scharr(gray.size(),gray.type());
	// addWeighted(scharr_x, 1, scharr_y, 1, 0, scharr);
	int width = gray.cols;
	int height = gray.rows;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int x_p = scharr_x.at<uchar>(i, j);
			int y_p = scharr_y.at<uchar>(i, j);
			int p = x_p + y_p;
			scharr.at<uchar>(i, j) = saturate_cast<uchar>(p);
		}
	}


	imshow("scharr_x", scharr_x);
	imshow("scharr_y", scharr_y);
	imshow("scharr", scharr);

	waitKey(0);
	return 0;
}*/


// 3. Laplance ͼƬ��Ե���
/*int main(){
	Mat src = imread("E:/card1.png");

	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	//Mat kernel = (Mat_<int>(3, 3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);
	//Mat dst;
	//filter2D(src,dst,src.depth(),kernel);

	// 1. �����˹
	Mat gaussian;
	GaussianBlur(src, gaussian, Size(3, 3), 0);
	// 2. ת�Ҷ�
	Mat gray;
	cvtColor(gaussian, gray, COLOR_BGR2GRAY);
	// 3. laplance
	Mat lpls;
	Laplacian(gray, lpls, CV_16S, 5);

	// 4.�����ֵ
	convertScaleAbs(lpls, lpls);

	// 5. ��ֵ��
	Mat thresh;
	threshold(lpls,thresh,0,255,THRESH_BINARY|THRESH_OTSU);


	imshow("lpls", lpls);

	waitKey(0);
	return 0;
}*/

// 4.Canny ͼƬ��Ե���
int main(){
	Mat src = imread("E:/card1.png");

	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	// Canny ��ԭ��
	// 1. ��˹ȥ����
	// 2. �Ҷ�ת��
	// 3. �����ݶ� Sobel/Scharr
	// 4. ������ź�����
	// 5. �ߵ���ֵ�����ֵͼ��0,255�� threshold1 ����ֵ threshold2 ����ֵ

	Mat dst;

	// ������threshold1 - threshold2 ���� threshold1 - threshold2 ֮�䣬ȡ���ֵ 255������ȡ 0  ���� 1 ��2  1 ��3   30-60  30-90  50-100 50-150
	// ������L2gradient  falsee������:����ֵ��ӣ�true������:������(sobel_x^2 + soble_y^2)
	Canny(src,dst,30,90,3,true);


	imshow("dst", dst);

	waitKey(0);
	return 0;
}