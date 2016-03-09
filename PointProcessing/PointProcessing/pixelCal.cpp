#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
void plus(Mat, Mat);
void main()
{
	Mat A = imread("lenna.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	Mat B(A.rows, A.cols, CV_8UC1);
	/*
	for (int i = 0; i < A.rows; i++)
	{
		for (int j = 0; j < A.cols; j++)
		{
			B.at<uchar>(i, j) = A.at<uchar>(i, j) + 20;
		}
	}*/
	plus(A,B);
	imwrite("plus3.bmp", B);
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
	//imwrite("plus2.bmp", B);
}
