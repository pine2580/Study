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
void Equalize(Mat in, int max_temp,Mat out)
{
	//평활화
	int hist[256] = { 0 };
	int sum[256] = { 0 };
	int n[256] = { 0 };
	//1.히스토그램 생성
	for (int k = 0; k < 256;k++)
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
				{
					if (in.at<uchar>(i, j) == k)
						hist[k] += 1;
				}
	//2.누적합 생성
	for (int i = 0; i < 256; i++)
	{
		if (i == 0)
			sum[i] = hist[i];
		else
			sum[i] += (hist[i]+sum[i-1]);
	}
	//3. 정규화
	for (int i = 0; i < 256; i++)
	{
		n[i] = (sum[i] * max_temp )/ (256*256) ;
	}
	for (int k = 0; k < 256; k++)
		for (int i = 0; i < in.rows; i++)
			for (int j = 0; j < in.cols; j++)
			{
				if (in.at<uchar>(i, j) == k)
					out.at<uchar>(i, j) = n[k];
			}
}
void main()
{
	Mat A=imread("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat B(A.rows, A.cols, CV_8UC1);
	Mat C(A.rows, A.cols, CV_8UC1);
	Mat D(A.rows, A.cols, CV_8UC1);
	int high=0, low=0;

	high=PixelMax(A,high);
	low=PixelMin(A, low);
	
	HistoStretch(A, high, low,B);
	imwrite("HistoStretch.bmp", B);
	End_IN(A, high, low, C);
	imwrite("End_In.bmp", C);
	Equalize(A, high, D);
	imwrite("Equalize.bmp", D);
}