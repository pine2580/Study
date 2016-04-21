#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <Windows.h>
#include <iostream>
typedef struct
{
	double z[2];

}gaussian;

#define pi 3.14159265358979323846264338327950288
int readFile(int *x, char* direct);
void Expectation(int x, double* avg, double* covar, double *weight, gaussian &P);
void count_P_z(double *N_j, gaussian *P, int i);
void Cal_avg(double *M_avg, double N_j, gaussian *P, int* x, int i);
void Cal_covar(double* M_covar, double N_j, gaussian *P, int* x, double M_avg, int i);
void Cal_weight(double* M_weight, double N_j);
double argmax(double *M_covar, double *M_weight, double *M_avg, int *x);
