#include <stdio.h>
#include <math.h>
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
void XOR(Mat, Mat);
void NOT(Mat, Mat);
void Gamma(Mat, Mat);
void Binarization(Mat, Mat);
void Stress(Mat, Mat);
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
	Mat H(A.rows, A.cols, CV_8UC1);
	Mat I(A.rows, A.cols, CV_8UC1);
	AND(A, circle, F);
	OR(A, circle, G);
	XOR(A, H);
	NOT(A, I);
	imwrite("AND.bmp", F);
	imwrite("OR.bmp", G);
	imwrite("XOR.bmp", H);
	imwrite("NOT.bmp", I);

	Mat J(A.rows, A.cols, CV_8UC1);
	Mat K(A.rows, A.cols, CV_8UC1);
	Mat L(A.rows, A.cols, CV_8UC1);
	Gamma(A, J);
	Binarization(A, K);
	Stress(A, L);
	imwrite("Gamma.bmp", J);
	imwrite("Binarization.bmp", K);
	imwrite("stress.bmp", L);

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
			if (in.at<uchar>(i, j) == 0 && circle.at<uchar>(i, j) == 0)
				out.at<uchar>(i, j) = 0;
			else
				out.at<uchar>(i, j) = in.at<uchar>(i, j);
		}
	}
}
void XOR(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			if((in.at<uchar>(i,j)^100)==0)
				out.at<uchar>(i, j) = 0;
			else
				out.at<uchar>(i, j) = in.at<uchar>(i,j);
		}
	}
}
void NOT(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = 255-in.at<uchar>(i, j);
		}
	}
}
void Gamma(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			out.at<uchar>(i, j) = pow(in.at<uchar>(i, j),1/1.2);
			//감마 값이 1보다 크면 어두워지고, 작으면 밝아짐
		}
	}
}
void Binarization(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			if (in.at<uchar>(i, j)>128)
				out.at<uchar>(i, j) = 255;
			else
				out.at<uchar>(i, j) = 0;
		}
	}
}
void Stress(Mat in, Mat out)
{
	for (int i = 0; i < in.rows; i++)
	{
		for (int j = 0; j < in.cols; j++)
		{
			if (in.at<uchar>(i, j) > 100 && in.at<uchar>(i, j) < 150)
				out.at<uchar>(i, j) = 255;
			else
				out.at<uchar>(i, j) = in.at<uchar>(i, j);
		}
	}
}