#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define Max(a,b) a>b ? a :b 

// inline ���������������� define ��������ʱ�滻
// ����define ��û���ϸ�ļ��,inline�����Ĳ�����ȷ�е��������Ի����ϸ�����ͼ��
// inline ʹ�ó��������漰���ڸ��ӵĺ���
inline int max1(int a, int b){
	return a > b ? a : b;
}

// 1. inline �� define������
//int main(){
//	Mat src = imread("E:/test.jpg");
//
//	cout << max1(2, 3) << endl;
//
//	imshow("src", src);
//	waitKey(0);
//	return 0;
//}

// 2. ��״���ļ�����
//int main(){
//	Mat src = imread("E:/test.jpg");
//	
//	// �ж϶�ȡ�Ƿ���ȷ
//	if (src.empty()){
//		cout << "src read error" << endl;
//		return -1;
//	}
//
//	// 2.1 ������
//	// LINE_8: 8��ͨ�ߣ�8-connected��,����һ����������һ����ı߻��
//	// LINE_4: ��һ�������һ�����������û�н��ˣ�
//	line(src,Point(10,10),Point(300,300),Scalar(0,0,255),5,LINE_8);
//
//	// 2.2 ���ƾ���
//	rectangle(src, Point(20, 20), Point(100, 100), Scalar(0, 0, 255), 5, LINE_8);
//	rectangle(src, Rect(30,30,20,50), Scalar(0, 0, 255), 5, LINE_8);
//
//
//	// 2.3 ������Բ
//	// �ڶ��������ǣ���Բ�����ĵ�
//	// ����������: Size ��һ��ֵ����Բ x width �İ뾶�� �ڶ����� y height �İ뾶
//	ellipse(src,Point(src.cols/2,src.rows/4),Size(src.cols/8,src.rows/4),180,0,360,Scalar(255,0,0),3,LINE_AA);
//
//	// 2.4 ԰
//	circle(src,Point(src.cols-500,src.rows-500),50,Scalar(0,255,255),5,LINE_AA);
//
//	// 2.5 ��� fillpoly �����
//	/*CV_EXPORTS void fillPoly(InputOutputArray img, const Point** pts,
//		const int* npts, int ncontours,
//		const Scalar& color, int lineType = LINE_8, int shift = 0,
//		Point offset = Point());*/
//	Point pots[] = { Point(100, 100), Point(100, 200), Point(200, 200), Point(100, 100) };
//
//	const Point* potss[] = { pots };
//
//	const int npts[] = { 4 };
//
//	fillPoly(src, potss, npts, 1, Scalar(255, 0, 0), LINE_8);
//
//	// 2,6 ������
//	// fontFace ����
//	// fontScale ���ţ���С
//	putText(src, "HI��OpenCV", Point(100, 100), QT_FONT_BLACK,1,Scalar(255,0,255),1,LINE_AA);
//
//	// 2.7 ����� srand ����
//	// opencv ����� srand random Ч��һ��
//	RNG rng(time(NULL));
//	// ����һ��ͼƬ,�� src �Ŀ�ߺ���ɫͨ��һֱ�����еĵ㶼�� 0
//	Mat dst = Mat::zeros(src.size(),src.type());
//
//	for (int i = 0; i < 10; i++)
//	{
//		Point sp;
//		sp.x = rng.uniform(0,dst.cols);
//		sp.y = rng.uniform(0, dst.rows);
//		Point ep;
//		ep.x = rng.uniform(0, dst.cols);
//		ep.y = rng.uniform(0, dst.rows);
//		line(dst, sp, ep, Scalar(rng.uniform(0, 255), rng.uniform(0, 255),rng.uniform(0, 255)));
//	}
//
//	imshow("src", dst);
//	waitKey(0);
//	return 0;
//}

// 3. ͼ�������˲�����
// 3.1 ͼ�������Ĥ���� �����Թ���ͼ����Ϣ��
int main(){
	Mat src = imread("E:/copy.png");
	if (src.empty()){
		cout << "src read error" << endl;
		return -1;
	}

	// ��������Ĥ����
	// ����һ����Դͼ���С���������ͬ��ȫ 0 ����
	/*Mat dst = Mat::zeros(src.size(),src.type());
	int rows = src.rows;
	int cols = src.cols;
	int channels = src.channels();
	for (int i = 1; i < rows - 1; i++)
	{
		// ��һ��
		uchar* previous = src.ptr<uchar>(i-1);
		// ��ǰ��
		uchar* current = src.ptr<uchar>(i);
		// ��һ��
		uchar* next = src.ptr<uchar>(i+1);
		// ���
		uchar* output = dst.ptr<uchar>(i);
		for (int j = channels; j < (cols-1)*channels; j++)
		{
			output[j] = saturate_cast<uchar>(5 * current[j] - (previous[j] + next[j] + current[j - channels] + current[j + channels]));
		}
	}*/


	// opencv �Դ�����Ĥ����
	Mat dst;
	Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	filter2D(src,dst,src.depth(),kernel);

	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
	return 0;
}