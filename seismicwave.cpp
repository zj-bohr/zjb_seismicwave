#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// set the square of grid
int Tn;
int Xn; 
int Zn;
#define PI 3.141592653589793

// set the explode site in the grid
#define X 150
#define Y 5

// some default constant for ricker wavelet
#define DH 8.0
#define DT 0.0005

#define Frequency 25
#define Round 3

int main() 
{
	// linput messages
	printf("Hello this is a program to caculate acoustic wave equation\n");
	printf("Please input the Xn, Zn and Tn\n");
	printf("Xn is :");
	if (scanf_s("%d", &Xn) != 1 || Xn <= 0)
	{
		printf("What youinput is nonesense! \n"); 
		exit(1);
	}
	printf("Zn is :");
	if (scanf_s("%d", &Zn) != 1 || Xn <= 0) 
	{ 
		printf("what youinput is nonesense !\n"); 
		exit(1); 
	}
	printf("Tn is : ");
	if (scanf_s("%d", &Tn) != 1 || Xn <= 0)
	{
		printf("what youinput is nonesense!\n"); 
		exit(1);
	}

	// malloc the size of the ricker wavelet
	double* w = (double*)malloc(sizeof(double) * Tn);

	// initialize the ricker wavelet
	for (int i = 0; i < Tn; i++)
	{
		w[i] = exp(-(2 * PI * Frequency / Round) * (2 * PI * Frequency / Round) * DT * (i - 90) * (i - 90) * DT) * cos(2 * PI * Frequency * DT * (i - 90));
	}

	//initialize the velocity
	double** vel = (double**)malloc(sizeof(double*) * Xn); 
	for (int i = 0; i < Xn; i++)
	{
		vel[i] = (double*)malloc(sizeof(double) * Zn);
	}
	
	for(int i=0;i<Xn ;i++)
		for(int j=0;j<Zn;j++)
		{
			vel[i][j]= 3000;//均匀边界
		}
	
	/* 
	for(int i=0 ; i<Xn;i++)
	{
		for(int j=0;j<Zn;j++)
		{
			vel[i][j] = 3000;
			if(i>145&&i<155&&j>70&&j<80) vel[i][j]=0;
		}
	}*/// 绕射波

	/*
	for (int i = 0; i < Xn; i++)
	{
		for (int j = 0; j < Zn; j++)
		{
			if (j < (0.006 * (320 - i) * (i + 20)))
			{
				vel[i][1] = 2000;
			}
			else
			{
				vel[i][j] = 3000;
			}
		}//盆地模型
	}*/

	//malloc the size for the grid
	double** p_now = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		p_now[i] = (double*)malloc(sizeof(double) * Zn);
	}
			
	//past value of wavefield
	double** p_past = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		p_past[i] = (double*)malloc(sizeof(double) * Zn);
	}

	//present value of wavefield
	double** temp = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)	
	{
		temp[i] = (double*)malloc(sizeof(double) * Zn);
	}

	//trancisent value of wavefield
	double** p_temp;

	//initialize the grid
	for (int i = 0; i < Xn; i++)
	{
		for (int j = 0; j < Zn; j++)
		{
			p_now[i][j] = 0;
			p_past[i][j] = 0;
			temp[i][j  ] = 0;
		}
	}

	//any dimension calculate
	for (int k = 0; k < Tn; k++)
	{
		for (int i = 2; i < Xn - 2; i++)
		{
			for (int j = 2; j < Zn - 2; j++)
			{
				/*int A = vel[i][3]*DH/ DT;//定义A的值
				u2[2][j] =(2- 2* A - pow(A,2) )*u1[2][j]+2* A*(1 +A)*u1[3][j]-pow(A,2)*u1[4][j]+(2* A- 1)*u0[2][j]-2*A*uO[3][j];//左边界
				u2[Xn - 3][j] - (2 - 2 * A - pow(A, 2)) * u1[Xn - 3][j] + 2 * A * (1 + A) * u1[Xn - 4][j] - pow(A,2)* u1[Xn - 5][j] + (2 * A - 1) * u0[Xn - 3][j]- 2 * A * u0[Xn - 4][j];//右边界
				u2[i][2]-(2 -2* A - pow(A,2))*u1[i][2]+ 2 *A*(1 +A)*u1[i][3] - pow(A,2)*u1[i][4] +(2*A - 1)*u0[i][2]-2* A*u0[i][3];//上边界
				u2[i][Zn - 3] =(2- 2* A - pow(A,2) )*u1[i][Zn -3]+2* A*(1 +A)*u1 [i][Zn-4] - pow(A,2)*u1[i] [Zn - 5]+(2* A- 1)*u0[i][Zn - 3]- 2*A*u0[i][Zn - 4];//下边界*/
				p_now[i][j] = 2 * temp[i][j] - p_past[i][j] + (vel[i][j] * vel[i][j] * DT * DT / (DH * DH)) * (-1.0 / 12 * (temp[i - 2][j] + temp[i + 2][j]) + 4 / 3.0 * (temp[i - 1][j] + temp[i + 1][j]) - 5 / 2.0 * temp[i][j] - 1.0 / 12 * (temp[i][j - 2] + temp[i][j + 2]) + 4 / 3.0 * (temp[i][j-1] + temp[i][j + 1]) - 5 / 2.0 * temp[i][j]) + w[k] * (i == X && j == Y);
			}
		}

		// switch array for next loop
		p_temp = p_now;
		p_now = p_past;
		p_past = temp;
		temp = p_temp;
		printf("loop %d is done !\n", k);
	}

	// open a file a recordthe result
	printf("Xn is %d,Zn is %d,Tn is %d\n", Xn, Zn, Tn);

	// output into file
	FILE* fp;
	errno_t error;
	error = fopen_s(&fp, "wavefront.dat", "w+");
	//这里的返回值是，如果成功返回0，如果不成功返回非0
	if (error != 0)
	{
		printf("打开失败");
	}
	else 
	{
		for (int i = 0; i < Xn; i++)
		{
			for (int j = 0; j < Zn; j++)
			{
				fprintf(fp, "%lf ", temp[i][j]);
			}
		}
	}
	
	fclose(fp);

	// free the memeory
	free(w);
	for (int i = 0; i < Xn; i++)
	{
		free(p_now[i]);
	}
	for (int i = 0; i < Xn; i++)
	{
		free(p_past[i]);
	}
	for (int i = 0; i < Xn; i++)
	{
		free(temp[i]);
	}
	for (int i = 0; i < Xn; i++)
	{
		free(vel[i]);
	}
	free(temp);
	free(p_now);
	free(p_past);
	free(vel);
	return 0;
}
