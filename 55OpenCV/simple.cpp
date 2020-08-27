#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

// 1. ��̬ѧ����
/*int main(){
	Mat src = imread("E:/copy.png");

	if (!src.data){
		cout << "imread error" << endl;
		return -1;
	}

	imshow("src", src);

	Mat kernel = getStructuringElement(MORPH_RECT,Size(25,25));
	Mat dst;
	// ��ʴ
	// erode(src, dst, kernel);
	// ����
	//dilate(src,dst,kernel);

	// MORPH_OPEN �����ȸ�ʴ������
	// morphologyEx(src, dst,MORPH_OPEN,kernel);
	
	// MORPH_CLOSE �գ������ͺ�ʴ
	// morphologyEx(src,dst,MORPH_CLOSE,kernel);
	
	// MORPH_GRADIENT �ݶȣ����� - ��ʴ
	//morphologyEx(src, dst, MORPH_GRADIENT, kernel);

	// MORPH_TOPHAT ��ñ��ԭͼ�� - ��ͼ��
	// morphologyEx(src,dst,MORPH_TOPHAT,kernel);

	// MORPH_BLACKHAT ��ñ����ͼ�� - ԭͼ��
	morphologyEx(src,dst,MORPH_BLACKHAT,kernel);


	imshow("dst",dst);

	waitKey(0);
	return 0;
}*/

// 2. ��֤��ʶ��
/*int main(){
	Mat src = imread("E:/copy.png");

	if (!src.data){
		cout << "imread error" << endl;
		return -1;
	}

	imshow("src", src);

	// 2.1 �Ѳ�ɫ��� �ڰ� ��ֵ��
	// �Ұ�
	Mat gray;
	cvtColor(src,gray,COLOR_BGR2GRAY);
	// imshow("gray",gray);
	// ��ֵ���������Զ���ֵ
	// ~ ���ű�ʾ = ��255 - ԭ��������ֵ�� ��ͬ�� bitwise_not
	Mat binary;
	adaptiveThreshold(~gray,binary,255,ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY,15,0);
	imshow("binary",binary);

	Mat kernel = getStructuringElement(MORPH_RECT,Size(5,5));
	Mat dst;
	// ��ʴ
	erode(src,dst,kernel);
	// ����
	dilate(src, dst, kernel);
	// morphologyEx(src,dst,MORPH_CLOSE,kernel);
	bitwise_not(dst, dst);

	imshow("dst",dst);

	waitKey(0);
	return 0;
}*/

// 3. ��ȡˮƽ��
/*int main(){
	Mat src = imread("E:/copy.png");

	if (!src.data){
		cout << "imread error" << endl;
		return -1;
	}

	imshow("src", src);
	Mat gray;
	cvtColor(src, gray, COLOR_BGR2GRAY);
	// imshow("gray",gray);
	// ��ֵ���������Զ���ֵ
	// ~ ���ű�ʾ = ��255 - ԭ��������ֵ�� ��ͬ�� bitwise_not
	Mat binary;
	adaptiveThreshold(~gray, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 15, 0);

	// ��ֵ����ЩС���⣬��һ���ֲ�
	Mat kernel = getStructuringElement(MORPH_RECT, Size(9, 9));
	Mat dst;
	dilate(binary, dst, kernel);
	erode(dst, dst, kernel);

	// ȡˮƽ
	Mat lLine = getStructuringElement(MORPH_RECT, Size(src.cols/16,1));
	erode(dst,dst,lLine);
	dilate(dst,dst,lLine);
	imshow("dst",dst);


	waitKey(0);
	return 0;
}*/


// 4. �ϲ����뽵����
int main(){
	Mat src = imread("E:/copy.png");

	if (!src.data){
		cout << "imread error" << endl;
		return -1;
	}

	imshow("src", src);

	Mat dst;
	// �ϲ��� ������˹ ˫���Բ�ֵ��Ԥ���㣨���㣩ֵ
	// pyrUp(src,dst,Size(src.cols*2,src.rows*2));
	// ��������1. ��ͼ����и�˹ģ����2.�ٹ��������ٽ��㡣 ���õĸ�˹ ���ԱȽ���
	pyrDown(src,dst,Size(src.cols/2,src.rows/2));

	imshow("dst",dst);

	// imwrite("E:/copy_pyrUp.png", dst);


	waitKey(0);
	return 0;
}