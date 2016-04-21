#include "header.h"

void main()
{
	int *data = (int*)calloc(sizeof(int),2500);
	char* direct = "C:\\Users\\김송란\\Desktop\\송란이폴더\\data.txt";
	int count;
	count = readFile(data, direct);
	
	
	gaussian *P=(gaussian*)calloc(2500,sizeof(gaussian));
	
	double *weight = (double*)calloc(sizeof(double), 2);
	double *avg = (double*)calloc(sizeof(double), 2);
	double *covar = (double*)calloc(sizeof(double), 2);
	avg[0] = 160.0;//임의로 정해줌
	avg[1] = 150.0;//임의로 정해줌
	covar[0] = 50.0;//임의로 정해줌
	covar[1] = 150.0;//임의로 정해줌
	weight[0] = 0.6;//임의로 정해줌
	weight[1] = 0.4; //임의로 정해줌
	double *N_j = (double*)calloc(sizeof(double), 2);
	double *M_avg = (double*)calloc(sizeof(double), 2);//M단계 후 평균 저장
	double *M_covar = (double*)calloc(sizeof(double), 2);//M단계 후 분산 저장
	double *M_weight = (double*)calloc(sizeof(double), 2);//M단계 후 가중치 저장
	while (1)
	{
		for (int i = 0; i < 2500; i++)
		{
			Expectation(data[i], avg, covar, weight, P[i]);
		}
		//초기화
		N_j[0] = 0, N_j[1] = 0;
		M_avg[0] = 0, M_avg[1] = 0;
		M_covar[0] = 0, M_covar[1] = 0;
		for (int i = 0; i < 2; i++)
		{
			count_P_z(&N_j[i], P, i);//j번째 가우시언에 소속된 샘플의 개수
			Cal_avg(&M_avg[i], N_j[i], P, data, i);
			Cal_covar(&M_covar[i], N_j[i], P, data, M_avg[i], i);
			Cal_weight(&M_weight[i], N_j[i]);
		}
		printf("\n");
		for (int i = 0; i < 2; i++)
		printf("[%d]  평균% lf  분산 %lf  가중치 %lf\n",i, M_avg[i], M_covar[i], M_weight[i]);
		double temp = (avg[0] - M_avg[0]);
		double temp1 = (avg[1] - M_avg[1]);
		temp = abs(temp);
		temp1 = abs(temp1);
		if (temp<0.00000000001&&temp1<0.00000000001)
		{
			break;
		}
		else
		{
			//초기값 변경
			for (int i = 0; i < 2; i++)
			{
				avg[i] = M_avg[i]; 
				covar[i] = M_covar[i];
				weight[i] = M_weight[i];
			}
		}
	}
	free(weight);
	free(avg);
	free(covar);
	free(N_j);
	free(M_avg);
	free(M_covar);
	free(M_weight);
}
	