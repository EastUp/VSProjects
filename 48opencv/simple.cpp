// ͷ�ļ� + dll��̬��
#include <opencv2/opencv.hpp>
#include <iostream> // ͷ�ļ� �� dll

using namespace cv;

void main(){
	// imread ��ȡһ��ͼƬ Mat(ͼƬ)
	Mat src = imread("E:/test.jpg");

	// Mat dst;

	// Bitmap ������RGB ��mat Ĭ�� BGR 
	// cvtColor(src,dst,COLOR_BGR2GRAY);

	// �ߣ�����ɫͨ�� rows ��(��) cols ��(��) 3 ��1�����ص� 3 ��ɫͨ��������������Ϣ��BGR��
	printf("�иߣ�%d,�п�%d,ͨ����%d",src.rows,src.cols,src.channels());

	// char ���з��ŵ� unsigned char ���޷��ŵ�,char ������ΧΪ-128��127( 0x80__0x7F)�� ��unsigned char ������ΧΪ0��255( 0__0xFF ) ��ʱ�����������ֵ����255��Χ�ڣ�Ҳ��unsigned char�����������Ƕ��ʽ�õĶ�
	for (int i = 0; i < src.rows; i++){
		// ��ȡ��ǰ�е��׵�ַ
		uchar* start_pixels = src.ptr<uchar>(i);
		
		for (int j = 0; j < src.cols; j++){
			uchar b = start_pixels[0];
			uchar g = start_pixels[1];
			uchar r = start_pixels[2];

			// ��ɫת�Ҷ�
			// ��ʽ���� f =  0.11R + 0.59G + 0.30B   gery ���255 ������������ܻᳬ�� 255
			// uchar gery = 0.11f*r + 0.59f*g + 0.30f*b;
			uchar gray = 0.11f*r + 0.59f*g + 0.30f*b;

			// ��ɫת�ڰ�
			uchar bw = (b + g + r) / 3 > 125 ? 255 : 0;

			// saturate_cast ���� 255�ͱ��255 ��С��0 �ͱ��0
			/* start_pixels[0] = saturate_cast<uchar>(bw);
			start_pixels[1] = saturate_cast<uchar>(bw);
			start_pixels[2] = saturate_cast<uchar>(bw);*/

			// ���Ͷ����������Щ
			start_pixels[0] = saturate_cast<uchar>(1.2f * b);
			start_pixels[1] = saturate_cast<uchar>(1.2f * g);
			start_pixels[2] = saturate_cast<uchar>(1.2f * r);

			start_pixels += 3;
		}
	}


	// �� mat д���ļ�
	imwrite("E://test3.jpg",src);

	// ��ʾͼƬ
	imshow("test pic", src);

	waitKey(0);
}