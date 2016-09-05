#pragma once

#include <stdio.h>
#include <math.h>
#include <armadillo>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace arma;
//using namespace cv;
struct colorimg
{
	unsigned char r, g, b;
};
colorimg **IntAlloc2(int width, int height);
colorimg** ReadImage_color(char *name, int *width, int *height);
void WriteImage_color(char* name, colorimg** image, int width, int height);
void Free(colorimg** image, int width, int height);
void LineEquation(double s, double t, double u, double v, double D,mat&,mat&,mat&);
void PlaneEquation(mat,mat&,mat&,mat&,mat&);
void CrossLinePlane(mat, mat, mat, mat, mat&);
void InterpolationCoor(mat,mat &a, mat &b, mat &c, mat &d, mat &sub_xy,int,int,int,int);
void rawimage(int,int,int,int,int,colorimg** inputimg, colorimg** outimg, mat a, mat b, mat c, mat d, mat sub_xy);
int detectInOut(mat imageCoord, mat x);
void MakeSubApertureImages(int i, int j, int lens, int sensor, colorimg** inputimg, colorimg** outimg);


typedef struct __cameraInfo
{
	double lens_size;// mm단위
	double K; //마이크로렌즈 한줄 갯수
	double N;
	double Cpix;
	double Fs;
	double Fu;
	double Cm;
	double Cu;
	double du;
	double dm;
	double fm;
	double D;
}cameraInfo;

typedef struct __resultdata
{
	double s;
	double t;
	double U;
	double V;
}resultdata;


void define_cameraInfo(cameraInfo &A); // 카메라 내부 파라미터 정의

void define_H(mat &H_rel_abs, mat &H_abs_phi, mat &H_phi_sphi, mat &H_T, mat &H_M, mat &H_sphi_phi, cameraInfo info);

