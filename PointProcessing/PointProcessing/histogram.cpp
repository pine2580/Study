#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#define MIN(x,y) (x<y ? x:y)
#define MAX(x,y) (x>y ? x:y)

using namespace cv;
int PixelMax(Mat in,int max_temp)
{
	max_temp = in.at<uchar>(0, 0);
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			max_temp = MAX(max_temp, in.at<uchar>(i, j));
		}
	return max_temp;
}
int PixelMin(Mat in, int min_temp)
{
	min_temp = in.at<uchar>(0, 0);
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			min_temp = MIN(min_temp, in.at<uchar>(i, j));
		}
	return min_temp;
}
void HistoStretch(Mat in, int max_temp, int min_temp,Mat out)
{//명암대비가 개선되어 품질이 좋아짐
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = ((in.at<uchar>(i, j) - min_temp)*255 / (max_temp - min_temp));
		}
}
void End_IN(Mat in, int max_temp, int min_temp, Mat out)
{
	for (int i = 0; i < in.rows; i++)
		for (int j = 0; j < in.cols; j++)
		{
			if (in.at<uchar>(i, j) <= min_temp)
				out.at<uchar>(i, j) = 0;
			else if (in.at<uchar>(i, j) >= max_temp)
				out.at<uchar>(i, j) = 255;
			else
				out.at<uchar>(i,j)= ((in.at<uchar>(i, j) - min_temp) * 255 / (max_temp - min_temp));
		}
}
void main()
{
	Mat A=imread("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat B(A.rows, A.cols, CV_8UC1);
	Mat C(A.rows, A.cols, CV_8UC1);
	int high=0, low=0;

	high=PixelMax(A,high);
	low=PixelMin(A, low);
	
	HistoStretch(A, high, low,B);
	imwrite("HistoStretch.bmp", B);
	End_IN(A, high, low, C);
	imwrite("End_In.bmp", C);
}