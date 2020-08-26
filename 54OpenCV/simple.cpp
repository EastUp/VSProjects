#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int element_size = 1;
int max_size = 21;
Mat src;


/*int main(){
	Mat src = imread("E:/copy.png");

	if (!src.data){
		cout << "src read error" << endl;
		return -1;
	}
	imshow("src", src);

	Mat dst;
	 blur(src, dst, Size(15, 15));

	 ��ֵ�˲� �����п��ǵ��������ȡ�м���Ǹ�ֵ   1,2,��3��,4,5  ȥ������
	 medianBlur(src, dst,5);

	 ˫���˲� ������������ �����ڸ�˹����˹��������������ǿ��˫�߱�����������Ϣ����ǿ�����ڸ�˹���������ز�
	bilateralFilter(src,dst,15,100,5);

	imshow("dst", dst);

	 ��Ĥ����
	Mat final;
	Mat kernal = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(dst,final,dst.depth(),kernal);
	imshow("final",final);

	waitKey(0);
	return 0;
}*/

// �����븯ʴ������ڰ�ͼƬ
void trackbarCallback(int pos, void *userdata){
	int size = element_size * 2 + 1;
	// ����һ�� kernel
	Mat kernel = getStructuringElement(MORPH_RECT, Size(size, size));
	Mat dst;

	//���� �� ���ֵ(ȥ�ڵ�)
	dilate(src, dst, kernel);
	// ��ʴ ����Сֵ ��ȥ�׵㣩
	// erode(src,dst,kernel);
	imshow("output image", dst);
}


int main(){
	src = imread("E:/copy.png");

	if (!src.data){
		cout << "src read error" << endl;
		return -1;
	}
	imshow("src", src);
	
	// ����һ�� window
	namedWindow("output image");

	// ��̬����
	createTrackbar("Trackbar","output image",&element_size,max_size,trackbarCallback);


	waitKey(0);
	return 0;
}