#include "header.h"

int readFile(int *x, char* direct)
{
	
	int temp1=0;
	int count = 0;

	FILE *fp = fopen(direct, "rt");
	if (fp == NULL)
	{
		printf("파일이 없습니다\n");
	}
	while ((feof(fp)) == 0)
	{
		fscanf(fp, "%d", &temp1);
		x[count] = temp1;
		count++;
	}
	fclose(fp);
	return count;
}

void Expectation(int x, double* avg, double* covar, double *weight, gaussian &P)
{
	double temp1=0, temp2=0;
	double nomal[2];
	double forexp = 0;
	double forexp0 = 0, forexp1 = 0;
	
	for (int i = 0; i < 2; i++)
	{
		forexp = pow((double)x - avg[i], 2.0);
		nomal[i] = (1.0 / sqrt(2.0 * pi *covar[i])) * exp(-forexp / (2.0 * covar[i]));
	}
	for (int i = 0; i < 2; i++)
	{
		temp2 += (weight[i] * nomal[i]);
	}
	for (int i = 0; i < 2; i++)
	{
		temp1 = weight[i] * nomal[i];
		P.z[i] = temp1 / temp2;
	}
}
void count_P_z(double *N_j, gaussian *P,int i)
{
	for (int j = 0; j < 2500; j++)
	{
		*N_j += P[j].z[i];
	}
}
void Cal_avg(double *M_avg, double N_j, gaussian *P, int* x, int i)
{
	for (int j = 0; j < 2500; j++)
	{
		*M_avg += P[j].z[i] * x[j];
	}
	*M_avg = *M_avg / N_j;
}
void Cal_covar(double *M_covar, double N_j, gaussian *P, int* x, double M_avg, int i)
{
	for (int j = 0; j < 2500; j++)
	{
		*M_covar += P[j].z[i] * (x[j] - M_avg)*(x[j] - M_avg);
	}
	*M_covar = *M_covar / N_j;
}
void Cal_weight(double *M_weight, double N_j)
{
	*M_weight = N_j / 2500.0;
}
