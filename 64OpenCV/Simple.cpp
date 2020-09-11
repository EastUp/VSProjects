#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

// 1.������ǿ(���Է�ʽ)
/*int main(){
	Mat src = imread("E:/2_05.jpg");
	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src",src);

	cout << src.channels() << endl;

	Mat dst = src.clone();
	for (int row = 0; row < src.rows; row++)
	{
		for (int col = 0; col < src.cols; col++)
		{
			Vec3b pixels = src.at<Vec3b>(row,col);
			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(pixels[0] + 30);
			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(pixels[1] + 30);
			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(pixels[2] + 30);
		}
	}

	imshow("dst",dst);

	waitKey(0);
	return 0;
}*/


// 2.ֱ�����⣬�����Աȶ�
/*int main(){
	Mat src = imread("E:/2_05.jpg");
	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	Mat hsv;
	cvtColor(src,hsv,COLOR_BGR2HSV);

	vector<Mat> hsv_s;
	split(hsv,hsv_s);

	equalizeHist(hsv_s[2],hsv_s[2]);
	merge(hsv_s,hsv);
	cvtColor(hsv,src,COLOR_HSV2BGR);

	imshow("dst",src);

	waitKey(0);
	return 0;
}*/

// ��дֱ��ͼ����Դ��
void calcHist(const Mat &mat,Mat &hist){

}

// 3. ��дֱ��ͼ����Դ��
int main(){
	Mat src = imread("E:/2_05.jpg");
	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	imshow("gray",gray);

	// hist û�п�ߣ���������һ���յ�����
	Mat hist;
	calcHist(gray,hist);

	// ��ֱ��ͼ����һ��
	normalize(hist,hist,255);
	cout << hist << endl;

	// ��ֱ��ͼ
	int bin_w = 2;
	int grad = 256;
	Mat hist_mat(grad,bin_w * 256,CV_8UC3);
	for (int i = 0; i < grad; i++)
	{
		Point start(i*bin_w, hist_mat.rows);
		Point end(i*bin_w, hist_mat.rows - hist.at<int>(0,i));
		line(hist_mat, start, end, Scalar(255, 0, 255), bin_w, LINE_AA);
	}

	imshow("hist_mat",hist_mat);

	waitKey(0);
	return 0;
}


