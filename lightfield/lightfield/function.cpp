#include "header.h"

void define_cameraInfo(cameraInfo &A)
{
	A.lens_size = 26.0; // mm
	A.K = 100.0; //  마이크로렌즈 수
	A.N = 9.0; // 마이크로렌즈 하나당 픽셀 한줄 수
	A.Cpix = A.N / 2.0;
	A.Fs = 1.0 / (A.lens_size / (A.K*A.N)); //mm 
	A.Fu = 1.0 / (A.lens_size / A.K); //mm
	A.Cm = (A.K*(A.N - 1) / 2.0) - A.Cpix;
	A.Cu = (A.K) / 2.0;
	A.du = 2.5;
	A.dm = 30.0;
	A.D = 30.0;
	A.fm = 1.0 / ((1.0 / A.dm) + (1.0 / A.D));
	//A.fm = 20.0;
}

void define_H(mat &H_rel_abs, mat &H_abs_phi, mat &H_phi_sphi, mat &H_T, mat &H_M, mat &H_sphi_phi, cameraInfo info)
{
	H_rel_abs << 1 << 0 << info.N << 0 << -info.Cpix << endr
		<< 0 << 1 << 0 << info.N << -info.Cpix << endr
		<< 0 << 0 << 1 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;

	H_abs_phi << 1 / info.Fs << 0 << 0 << 0 << -(info.Cm / info.Fs) << endr
		<< 0 << 1 / info.Fs << 0 << 0 << -(info.Cm / info.Fs) << endr
		<< 0 << 0 << 1 / info.Fu << 0 << -(info.Cu / info.Fu) << endr
		<< 0 << 0 << 0 << 1 / info.Fu << -(info.Cu / info.Fu) << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;

	H_phi_sphi << 1 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << 0 << 0 << 0 << endr
		<< -(1 / info.du) << 0 << 1 / info.du << 0 << 0 << endr
		<< 0 << -(1 / info.du) << 0 << 1 / info.du << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;

	H_T << 1 << 0 << info.du + info.dm << 0 << 0 << endr
		<< 0 << 1 << 0 << info.du + info.dm << 0 << endr
		<< 0 << 0 << 1 << 0 << 0 << endr
		<< 0 << 0 << 0 << 1 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;

	H_M << 1 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << 0 << 0 << 0 << endr
		<< -(1 / info.fm) << 0 << 1 << 0 << 0 << endr
		<< 0 << -(1 / info.fm) << 0 << 1 << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;

	H_sphi_phi << 1 << 0 << 0 << 0 << 0 << endr
		<< 0 << 1 << 0 << 0 << 0 << endr
		<< 1 << 0 << info.D << 0 << 0 << endr
		<< 0 << 1 << 0 << info.D << 0 << endr
		<< 0 << 0 << 0 << 0 << 1 << endr;
}

colorimg **IntAlloc2(int width, int height)
{
	colorimg** tmp;

	tmp = (colorimg**)calloc(height, sizeof(colorimg*));
	for (int i = 0; i < height; i++)
		tmp[i] = (colorimg*)calloc(width, sizeof(colorimg));
	return(tmp);
}
colorimg** ReadImage_color(char *name, int *width, int *height)
{
	cv::Mat img = cv::imread(name, CV_LOAD_IMAGE_COLOR);
	colorimg ** image = (colorimg**)IntAlloc2(img.cols, img.rows);

	*width = img.cols;
	*height = img.rows;
	for (int i = 0; i<img.rows; i++)
		for (int j = 0; j < img.cols; j++)
		{
			image[i][j].b = img.at<cv::Vec3b>(i, j)[0]; //B
			image[i][j].g = img.at<cv::Vec3b>(i, j)[1]; //G
			image[i][j].r = img.at<cv::Vec3b>(i, j)[2]; //R
		}
	return(image);
}
void WriteImage_color(char* name, colorimg** image, int width, int height)
{
	cv::Mat img(height, width, CV_8UC3);
	for (int i = 0; i<height; i++)
		for (int j = 0; j<width; j++)
		{
			img.at<cv::Vec3b>(i, j)[0] = (uchar)image[i][j].b;
			img.at<cv::Vec3b>(i, j)[1] = (uchar)image[i][j].g;
			img.at<cv::Vec3b>(i, j)[2] = (uchar)image[i][j].r;
		}
	imwrite(name, img);
}
void Free(colorimg** image, int width, int height)
{
	for (int i = 0; i < height; i++)
		free(image[i]);
	free(image);
}

void LineEquation(double s, double t, double u, double v,double D,mat &Pl1, mat &Pl2, mat &unitvector)
{
	double temp,size;
	Pl1 << s << t << 0 << endr; //
	Pl2 << u << v << D << endr; // 
	temp = pow(u - s,2) + pow(v - t,2)+pow(D-0,2);
	size = sqrt(temp);
	unitvector << (u - s) / size << (v - t) / size << (D - 0) / size << endr;

	//unitvector << u - s << v - t << D - 0 << endr;
	//unitvector.print(" ");
}
void PlaneEquation(mat imageCoord, mat &Pp1,mat &Pp2,mat &Pp3,mat &nomalvector)
{
	Pp1 << imageCoord(0,0) << imageCoord(0,1) << imageCoord(0,2) << endr;
	Pp2 << imageCoord(1,0) << imageCoord(1,1) << imageCoord(1,2) << endr;
	Pp3 << imageCoord(2,0) << imageCoord(2,1) << imageCoord(2,2) << endr;
	
	mat temp1, temp2, temp3, temp4,temp5;
	temp1 = Pp3 - Pp1;
	temp2 = Pp2 - Pp1;
	temp3 = Pp3 - Pp1;
	temp4 = Pp2 - Pp1;
	temp5 = cross(temp3, temp4);
	double temp5size = sqrt(pow(temp5.at(0, 0), 2) + pow(temp5.at(0, 1), 2) + pow(temp5.at(0, 2), 2));
	nomalvector = temp5 / temp5size;
	//nomalvector.print("nomalvector ");
	
	
}
void CrossLinePlane(mat unitvector, mat nomalvector,mat Pp1,mat Pl1, mat &x)
{
	double temp = dot(unitvector, nomalvector);
	mat temp2 = (Pp1 - Pl1)/temp;
	double t = dot(temp2, nomalvector);
	//cout << "t " << t << endl;

	x=Pl1 + (t*unitvector);
	//x.print("직선과 평면이 만나는 점 x ");
	
}
void InterpolationCoor(mat x, mat &a, mat &b, mat &c, mat &d, mat &sub_xy,int input_width, int input_height, int world_x, int world_y)
{
	mat target;
	target << x(0,0)*((double)input_width / (double)world_x) << x(0,1)*((double)input_height / (double)world_y) << endr;
	a << int(target(0, 0)) << int(target(0, 1)) << endr;
	b << int(target(0, 0)) + 1 << int(target(0, 1)) << endr;
	c << int(target(0, 0)) << int(target(0, 1)) + 1 << endr;
	d << int(target(0, 0)) + 1 << int(target(0, 1)) + 1 << endr;
	sub_xy << target(0, 0) - int(target(0, 0)) << target(0, 1) - int(target(0, 1)) << endr;
}
void rawimage(int Flag, int i, int j,int width, int height,colorimg** inputimg, colorimg** outimg, mat a, mat b, mat c, mat d, mat sub_xy)
{
	if (Flag == 1)
	{
		int a_x, a_y, b_x, b_y, c_x, c_y, d_x, d_y, sub_x, sub_y;
		a_x = a(0, 0);
		a_y = a(0, 1);
		b_x = b(0, 0);
		b_y = b(0, 1);
		c_x = c(0, 0);
		c_y = c(0, 1);
		d_x = d(0, 0);
		d_y = d(0, 1);
		sub_x = sub_xy(0, 0);
		sub_y = sub_xy(0, 1);
		if ((a_x >= width - 1) && (d_y <= height - 1))
		{
			outimg[i][j].b = inputimg[d_y][width-1].b;
			outimg[i][j].g = inputimg[d_y][width-1].g;
			outimg[i][j].r = inputimg[d_y][width-1].r;
		}
		else if ((a_y >= height - 1) && (d_x <= width - 1))
		{
			outimg[i][j].b = inputimg[height-1][d_x].b;
			outimg[i][j].g = inputimg[height - 1][d_x].g;
			outimg[i][j].r = inputimg[height - 1][d_x].r;
		}
		else if ((a_x >= width - 1) && (a_y >= height - 1))
		{
			outimg[i][j].b = inputimg[height - 1][width-1].b;
			outimg[i][j].g = inputimg[height - 1][width-1].g;
			outimg[i][j].r = inputimg[height - 1][width-1].r;
		}
		else
		{
			outimg[i][j].b = (1 - sub_x)*(1 - sub_y)*((uchar)inputimg[a_y][a_x].b) + sub_x*(1 - sub_y)*((uchar)inputimg[b_y][b_x].b)
				+ (1 - sub_x)*sub_y*((uchar)inputimg[c_y][c_x].b) + sub_x*sub_y*((uchar)inputimg[d_y][d_x].b);
			outimg[i][j].g = (1 - sub_x)*(1 - sub_y)*((uchar)inputimg[a_y][a_x].g) + sub_x*(1 - sub_y)*((uchar)inputimg[b_y][b_x].g)
				+ (1 - sub_x)*sub_y*((uchar)inputimg[c_y][c_x].g) + sub_x*sub_y*((uchar)inputimg[d_y][d_x].g);
			outimg[i][j].r = (1 - sub_x)*(1 - sub_y)*((uchar)inputimg[a_y][a_x].r) + sub_x*(1 - sub_y)*((uchar)inputimg[b_y][b_x].r)
				+ (1 - sub_x)*sub_y*((uchar)inputimg[c_y][c_x].r) + sub_x*sub_y*((uchar)inputimg[d_y][d_x].r);
		}
		
	}
	else if (Flag == 2)
	{
		outimg[i][j].b = 128;
		outimg[i][j].g = 0;
		outimg[i][j].r = 0;
	}
}
int detectInOut(mat imageCoord, mat x)
{
	if ((imageCoord(0, 0) < x(0, 0)) && (x(0, 0) < imageCoord(3, 0)-1) && (imageCoord(0, 1) < x(0, 1)) && (x(0, 1) < imageCoord(3, 1)-1))
	{
		return 1;//이미지평면 안
	}
	else return 2;//이미지평면 밖
}

void MakeSubApertureImages(int i, int j, int lens, int sensor, colorimg** inputimg, colorimg** outimg)
{
	for (int k = 0; k < lens; k++)
	{
		for (int l = 0; l < lens; l++)
		{
			outimg[i*lens + k][j*lens + l].b = inputimg[k*sensor + i][l*sensor + j].b;
			outimg[i*lens + k][j*lens + l].g = inputimg[k*sensor + i][l*sensor + j].g;
			outimg[i*lens + k][j*lens + l].r = inputimg[k*sensor + i][l*sensor + j].r;

		}

	}
}