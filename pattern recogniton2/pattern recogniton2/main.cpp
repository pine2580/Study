#include "header.h"

void main()
{
	int *data = (int*)calloc(sizeof(int),2500);
	char* direct = "C:\\Users\\��۶�\\Desktop\\�۶�������\\data.txt";
	int count;
	count = readFile(data, direct);
	
	
	gaussian *P=(gaussian*)calloc(2500,sizeof(gaussian));
	
	double *weight = (double*)calloc(sizeof(double), 2);
	double *avg = (double*)calloc(sizeof(double), 2);
	double *covar = (double*)calloc(sizeof(double), 2);
	avg[0] = 160.0;//���Ƿ� ������
	avg[1] = 150.0;//���Ƿ� ������
	covar[0] = 50.0;//���Ƿ� ������
	covar[1] = 150.0;//���Ƿ� ������
	weight[0] = 0.6;//���Ƿ� ������
	weight[1] = 0.4; //���Ƿ� ������
	double *N_j = (double*)calloc(sizeof(double), 2);
	double *M_avg = (double*)calloc(sizeof(double), 2);//M�ܰ� �� ��� ����
	double *M_covar = (double*)calloc(sizeof(double), 2);//M�ܰ� �� �л� ����
	double *M_weight = (double*)calloc(sizeof(double), 2);//M�ܰ� �� ����ġ ����
	while (1)
	{
		for (int i = 0; i < 2500; i++)
		{
			Expectation(data[i], avg, covar, weight, P[i]);
		}
		//�ʱ�ȭ
		N_j[0] = 0, N_j[1] = 0;
		M_avg[0] = 0, M_avg[1] = 0;
		M_covar[0] = 0, M_covar[1] = 0;
		for (int i = 0; i < 2; i++)
		{
			count_P_z(&N_j[i], P, i);//j��° ����þ� �Ҽӵ� ������ ����
			Cal_avg(&M_avg[i], N_j[i], P, data, i);
			Cal_covar(&M_covar[i], N_j[i], P, data, M_avg[i], i);
			Cal_weight(&M_weight[i], N_j[i]);
		}
		printf("\n");
		for (int i = 0; i < 2; i++)
		printf("[%d]  ���% lf  �л� %lf  ����ġ %lf\n",i, M_avg[i], M_covar[i], M_weight[i]);
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
			//�ʱⰪ ����
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
	