#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define k 0.04
#define practicedata 380
#define textdata 126
#define n 15
int count=1000;
double a[practicedata][n];
double b[textdata][n];
double max[n], min[n];
double w[n-1];
double new_w[n-1];
double y = 0;
double rmse;
int inputs();
void initdata();//数据归一化
void model_practice();
void model_access();

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) 
{
	if (inputs() == 0)
	{
		return 0;
	}
	initdata();
	model_practice();
	model_access();
	return 0;
}


int inputs()
{
	int i, j;
	char fname[256];
	printf("请输入存放数据的文件名：");
	scanf("%s", fname);
	FILE* fp = fopen(fname, "rb");
	if (fp == NULL)
	{
		printf("不能打开输入的文件\n");
		return 0;
	}
	for (i = 0;i < practicedata;i++)
	{
		a[i][0] = 1;
		for (j = 1;j < n;j++)
		{
			fscanf(fp, "%lf", &a[i][j]);
		}
	}
	for (i = 0;i < textdata;i++)
	{
		b[i][0] = 1;
		for (j = 1;j < n;j++)
		{
			fscanf(fp, "%lf", &b[i][j]);
		}
	}
	fclose(fp);
	return 1;
}

void initdata()
{
	int i, j;
	for ( j=1;j < n;j++)
	{
		max[j] = min[j] = a[0][j];
		for ( i=0;i<practicedata;i++)
		{
			max[j] = max[j] > a[i][j] ? max[j] : a[i][j];
			min[j] = min[j] < a[i][j] ? min[j] : a[i][j];
		}
	}
	for ( i = 0;i < practicedata;i++)
	{
		for (j = 1;j < n;j++)
		{
			a[i][j] = (a[i][j] - min[j]) / (max[j] - min[j]);
		}
	}
	for ( j = 1;j < n;j++)
	{
		max[j] = min[j] = b[0][j];
		for (i = 0;i < textdata;i++)
		{
			max[j] = max[j] > b[i][j] ? max[j] : b[i][j];
			min[j] = min[j] < b[i][j] ? min[j] : b[i][j];
		}
	}
	for ( i = 0;i < textdata;i++)
	{
		for (j = 1;j < n;j++)
		{
			b[i][j] = (b[i][j] - min[j]) / (max[j] - min[j]);
		}
	}
	for ( i = 0;i < n-1;i++) w[i] = 1;
}

void model_practice()
{
	int i, j;
	while (count--)
	{
		double sum1[practicedata];
		double sum2[n - 1];
		for ( i = 0;i < practicedata;i++)
		{
			sum1[i] = 0;
			for (j = 0;j < n - 1;j++)
			{
				sum1[i] += w[j] * a[i][j];
			}
			sum1[i] -= a[i][n - 1] * (n - 1);
		}
		for (j = 0;j < n - 1;j++)
		{
			sum2[j] = 0;
			new_w[j] = w[j];
			for (i = 0;i < practicedata;i++)
			{
				sum2[j] += sum1[i] * a[i][j];
			}
			new_w[j] -= k * sum2[j] / 4;
		}
		for ( i = 0;i < n - 1;i++) w[i] = new_w[i];
	}
}

void model_access()
{
	int i, j;
	double sum3=0;
	for ( i = 0;i < textdata;i++)
	{
		y = 0;
		for ( j = 0;j < n - 1;j++)
		{
			y += w[j] * b[i][j];
		}
		sum3 += (y - b[i][n - 1]) * (y - b[i][n - 1]);
	}
	sum3 /= textdata;
	sum3 = sqrt(sum3);
	rmse = sum3;
}
