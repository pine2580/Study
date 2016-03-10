#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void plus(Mat, Mat);
void sub(Mat, Mat);
void multi(Mat, Mat);
void div(Mat, Mat);
void AND(Mat, Mat, Mat);
void OR(Mat, Mat, Mat);
void main()
{
	Mat A = imread("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat B(A.rows, A.cols, CV_8UC1);
	Mat C(A.rows, A.cols, CV_8UC1);
	Mat D(A.rows, A.cols, CV_8UC1);
	Mat E(A.rows, A.cols, CV_8UC1);
	
	plus(A, B);
	sub(A, C);
	multi(A, D);
	div(A, E);
	imwrite("plus.bmp", B);
	imwrite("sub.bmp", C);
	imwrite("multi.bmp", D);
	imwrite("div.bmp", E);

	Mat circle = imread("circle.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat F(A.rows, A.cols, CV_8UC1);
	Mat G(A.rows, A.cols, CV_8UC1);
	AND(A, circle, F);
	OR(A, circle, G);
	imwrite("AND.bmp", F);
	imwrite("OR.bmp", G);
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
void AND(Mat in, Mat circle, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			if ((in.at<uchar>(i, j)&&circle.at<uchar>(i, j)))
				out.at<uchar>(i, j) = in.at<uchar>(i, j);
			else
				out.at<uchar>(i, j) = 0;
		}
	}
}
void OR(Mat in, Mat circle, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			//if ((in.at<uchar>(i, j) || circle.at<uchar>(i, j)))
			//	out.at<uchar>(i, j) = in.at<uchar>(i, j);
			//else
			//	out.at<uchar>(i, j) = 0;
			if (in.at<uchar>(i, j)==0 && circle.at<uchar>(i, j) == 0)
				out.at<uchar>(i, j) = 0;
			else
				out.at<uchar>(i, j) = in.at<uchar>(i, j);
		}
	}
}