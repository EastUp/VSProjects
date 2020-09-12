#include<opencv2/opencv.hpp>
#include<iostream>

using namespace cv;
using namespace std;

// 1. ˫���˲�����
//int main(){
//	Mat src = imread("E:/meirong.jpg");
//
//	if (!src.data){
//		cout << "read error" << endl;
//		return -1;
//	}
//
//	imshow("src",src);
//
//	Mat dst;
//	bilateralFilter(src,dst,0,100,5);
//	imshow("dst", dst);
//
//	waitKey(0);
//	return 0;
//}


// 2. ���ģ���㷨����
/*int main(){
	Mat src = imread("E:/meirong.jpg");

	if (!src.data){
		cout << "read error" << endl;
		return -1;
	}

	imshow("src", src);

	// ��˹��ģ�����������˹����ˣ������������������֮��Ĳ�ֵ�����õı���ͼ��ı�Ե��

	Mat dst;

	int size = 15; // size == 10001 ʱ time = 5
	Mat kernel = Mat::ones(size, size, CV_32FC1) / (size * size);

	long st = clock();
	filter2D(src,dst,src.depth(),kernel);
	long et = clock();
	double time = static_cast<double>((et - st) / CLOCKS_PER_SEC);
	cout << "time = " << time << endl;

	//ʱ�临�Ӷ� = src.rows * src.cols * size * size

	imshow("dst", dst);

	waitKey(0);
	return 0;
}*/


// 3. ʹ�û���ͼ�㷨�Ծ��ģ�������Ż�
void fastBlateralBlur(Mat &src, Mat &dst, int size){
    // ����� size ����ȷ��Ϊ���� size % 2 == 1
    // �����Χ���������
    Mat mat;
    int radius = size / 2;
    copyMakeBorder(src,mat,radius,radius,radius,radius,BORDER_DEFAULT);
    // �����ͼ
    Mat sum_mat, sqsum_mat;
    integral(mat,sum_mat,sqsum_mat,CV_32S,CV_32S);

    dst.create(src.size(),src.type());
    int channels = src.channels();
    int area = size * size;
    // ���ĸ��㣬���ϣ����£����ϣ�����
    int x0 = 0, x1 = 0, y0 = 0, y1 = 0;
    for (int row = 0; row < src.rows; row++)
    {
        y0 = row;
        y1 = y0 + size;
        for (int col = 0; col < src.cols; col++)
        {
            x0 = col;
            x1 = x0 + size;
            for (int i = 0; i < channels; i++)
            {
                // ��ȡ�ĸ����ֵ����Ϊ�϶��ᳬ�� 255 ������Ҫ��Vec3i ��װ��
                int lt = sum_mat.at<Vec3i>(y0, x0)[i];
                int lb = sum_mat.at<Vec3i>(y1, x0)[i];
                int rt = sum_mat.at<Vec3i>(y0, x1)[i];
                int rb = sum_mat.at<Vec3i>(y1, x1)[i];

                // ����ĺ�
                int sum = rb - lb - rt + lt;
                dst.at<Vec3b>(row, col)[i] = sum / area;
            }
        }
    }
}


int main(){
    Mat src = imread("E:/meirong.jpg");

    if (!src.data){
        cout << "read error" << endl;
        return -1;
    }

    imshow("src", src);

    // ��˹��ģ�����������˹����ˣ������������������֮��Ĳ�ֵ�����õı���ͼ��ı�Ե��

    Mat dst;
    int size = 15; // size == 10001 ʱ time = 1 ��
    long st = clock();
    fastBlateralBlur(src,dst,size);
    long et = clock();
    double time = static_cast<double>((et - st) / CLOCKS_PER_SEC);
    cout << "time = " << time << endl;

    imshow("dst", dst);

    waitKey(0);
    return 0;
}