#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

// ����ʶ����أ� ��ֵ��������Э�������ֵ����������
/*int main(){

	Mat src = (Mat_<double>(3, 3) << 50, 50, 50, 60, 60, 60, 70, 70, 70);
	// ƽ��ֵ ��(50+50+50+...+70) / 9 = 60;
	// ��׼��������������������ƽ��ֵ֮���ƽ���ĺ͵�ƽ�������ٿ�����
	// ((50-60)��ƽ�� + (50-60)��ƽ�� + (50-60)��ƽ�� + (60-60)��ƽ��... + (70-60)��ƽ��)/9 = ������(66.6666666667) = 8.1649658093 
	Mat mean, stddev; // mean ƽ��ֵ��stddev ��׼����
	meanStdDev(src, mean, stddev);
	cout << mean << endl;
	cout << stddev << endl;

	cout << "========================================" << endl;

	// Э�������
	Mat covar;
	calcCovarMatrix(src,covar,mean,COVAR_NORMAL | COVAR_ROWS);
	cout << mean << endl;
	cout << covar << endl;

	cout << "========================================" << endl;

	// Э���������ȥ����������������
	src = (Mat_<double>(2, 2) << 100, 100, 100, 100);
	Mat eigenvalues, eigenvectors;
	eigen(src, eigenvalues, eigenvectors);
	cout << eigenvalues << endl;
	cout << eigenvectors << endl;

	waitKey(0);
	getchar();
	return 0;
}*/


// ����ʶ����أ�PCA ԭ����Ӧ�� ����ά��
int main(){

	Mat src = imread("E:/copy.png");
	
	int size = src.rows * src.cols;
	Mat data(size,3,CV_8UC1);

	for (int i = 0; i < size; i++)
	{
		int row = i / src.cols;
		int col = i - row * src.cols;

		data.at<uchar>(i, 0) = src.at<Vec3b>(row, col)[0];
		data.at<uchar>(i, 1) = src.at<Vec3b>(row, col)[1];
		data.at<uchar>(i, 2) = src.at<Vec3b>(row, col)[2];
	}

	// ���ս�ά������
	PCA pca_analyze(data, Mat(), PCA::Flags::DATA_AS_ROW);

	cout << pca_analyze.mean << endl;
	cout << pca_analyze.eigenvalues << endl;
	cout << pca_analyze.eigenvectors << endl;

	waitKey(0);
	getchar();
	return 0;
}