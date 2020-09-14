#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

// ֱ��ͼ���⻯
/*int main(){
	Mat src = imread("E:/2_04.png");
	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);

	imshow("src",src);

	// Histogram ֱ��ͼ
	Mat dst;
	equalizeHist(gray, dst);
	imshow("dst", dst);

	waitKey(0);
	return 0;
}*/

// ֱ��ͼ�ļ���ͻ���
int main(){
	Mat src = imread("E:/copy.png");
	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}
	imshow("src", src);

	// ��ȡֱ��ͼ��B G R ÿ������������������Լ�д������ȥ���룩
	vector<Mat> bgr_s;
	split(src,bgr_s);

	// b ͨ������Ϊʲô���� ��ɫ������һ���Ҷ�ͼ ?   
	// imshow("bgr_s", bgr_s[0]);

	// ������ֱ��ͼ������
	// images �����ͼ��
	// nimages ����ͼ��ĸ��� 
	// channels �ڼ�ͨ��
	// mask ��ģ
	// dims ��Ҫͳ�Ƶ�ͨ������
	// histSize �ȼ��ĸ���  0-255
	// ranges ���ݵķ�Χ  0-255
	// uniform true �Ƿ�Եõ���ͼƬ���й�һ������
	// accumulate �ڶ��ͼ��ʱ���Ƿ��ۼƼ�������ֵ�ĸ��� false
	/*calcHist(const Mat* images, int nimages,
	const int* channels, InputArray mask,
	OutputArray hist, int dims, const int* histSize,
	const float** ranges, bool uniform = true, bool accumulate = false);*/

	int histSize = 256;
	float range[] = { 0, 256 };
	const float * ranges = { range };
	Mat hist_b, hist_g, hist_r;

	calcHist(&bgr_s[0], 1, 0, Mat(), hist_b, 1, &histSize, &ranges, true, false);
	calcHist(&bgr_s[1], 1, 0, Mat(), hist_g, 1, &histSize, &ranges, true, false);
	calcHist(&bgr_s[2], 1, 0, Mat(), hist_r, 1, &histSize, &ranges, true, false);

	// Mat ���������ֵ����һ����������ֵ
	// ��������hist_b �����ʲô������Ǹ����Ҷ�ֵ�ĸ�����hist_b ��Сֵ 0 �����ֵ ͼƬ�Ŀ�*��

	// ��һ��
	int hist_h = 400;
	int hist_w = 512; // 256 * 2��2 �����ʵĴ�С��
	int bin_w = hist_w / histSize; // ���ʴ�С
	// alpha ��Сֵ 
	// beta ���ֵ
	/*normalize(InputArray src, InputOutputArray dst, double alpha = 1, double beta = 0,
	int norm_type = NORM_L2, int dtype = -1, InputArray mask = noArray());*/
	// NORM_MINMAX ���ŵ�һ������
	normalize(hist_b, hist_b, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_g, hist_g, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(hist_r, hist_r, 0, hist_h, NORM_MINMAX, -1, Mat());

	// ����һ��ͼ��
	Mat histImage(hist_h, hist_w, CV_8SC4, Scalar()); 
	for (int i = 1; i < histSize; i++)
	{
		// ��ʼ�㣬������ 255
		line(
			histImage,
			Point((i - 1)*bin_w, hist_h - hist_b.at<float>(i - 1)),// ͼƬ�����ص� ���Ͻǲ��� 0,0
			Point(i*bin_w, hist_h - hist_b.at<float>(i)),
			Scalar(255, 0, 0), bin_w, LINE_AA);
		line(
			histImage,
			Point((i - 1)*bin_w, hist_h - hist_g.at<float>(i - 1)),
			Point(i*bin_w, hist_h - hist_g.at<float>(i)),
			Scalar(0, 255, 0), bin_w, LINE_AA);
		line(
			histImage,
			Point((i - 1)*bin_w, hist_h - hist_r.at<float>(i - 1)),
			Point(i*bin_w, hist_h - hist_r.at<float>(i)),
			Scalar(0, 0, 255), bin_w, LINE_AA);
	}

	imshow("histImage", histImage);

	waitKey(0);
	return 0;
}