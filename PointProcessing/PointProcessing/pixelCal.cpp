#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
void plus(Mat, Mat);
void sub(Mat, Mat);
void multi(Mat, Mat);
void div(Mat, Mat);
void main()
{
	Mat A = imread("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat B(A.rows, A.cols, CV_8UC1);
	Mat C(A.rows, A.cols, CV_8UC1);
	Mat D(A.rows, A.cols, CV_8UC1);
	Mat E(A.rows, A.cols, CV_8UC1);
	


	plus(A,B);
	sub(A, C);
	multi(A, D);
	div(A, E);
	imwrite("plus.bmp", B);
	imwrite("sub.bmp", C);
	imwrite("multi.bmp", D);
	imwrite("div.bmp", E);
}

void plus(Mat in,Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = in.at<uchar>(i, j) + 20;
		}
	}
}

void sub(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = in.at<uchar>(i, j) - 20;
		}
	}
}
void multi(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = in.at<uchar>(i, j) * 1.5;
		}
	}
}
void div(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = in.at<uchar>(i, j) / 1.5;
		}
	}
}