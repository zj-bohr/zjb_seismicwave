#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int Tn;
int Xn; 
int Zn;
#define PI 3.141592653589793


#define X 3
#define Y 60


#define DH 8.0
#define DT 0.0005

#define Frequency 25
#define Round 3

int main()
{

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


	double* w = (double*)malloc(sizeof(double) * Tn);


	for (int i = 0; i < Tn; i++)
	{
		w[i] = exp(-(2 * PI * Frequency / Round) * (2 * PI * Frequency / Round) * DT * (i - 90) * (i - 90) * DT) * cos(2 * PI * Frequency * DT * (i - 90));
	}

	double** vel = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		vel[i] = (double*)malloc(sizeof(double) * Zn);
	}

    //绕射
	/*
		for (int i = 0; i < Xn; i++)
			for (int j = 0; j < Zn; j++)
			{
				vel[i][j] = 3000;//均匀介质
			}

		*/
	
	/*
	for (int i = 0; i < Xn; i++)
		for (int j = 0; j < Zn; j++)
			if (i > (10 * pow((j - 100) , 2) + 50))
			{
				vel[i][j] = 3000; 
			}
			else
			{
				vel[i][j] = 2000; 
			}
    */

	//起伏界面
	/*
	for (int i = 0; i < Xn; i++)
		for (int j = 0; j < Zn; j++)
			if (i > (50* sin(j*PI/50)) + 100))
			{
				vel[i][j] = 3000;
			}
			else
			{
				vel[i][j] = 2000;
			}
    */

    //盆地
	/*
	for (int i = 0; i < Xn; i++)
	{
		for (int j = 0; j < Zn; j++)
		{
			if (j < (i-400)||(j>900-i)||(i>450))
			{
				vel[i][j] = 2000;
			}
			else
			{
				vel[i][j] = 3000;
			}
		}
	}*/

	//malloc the size for the grid
	double** p_now = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		p_now[i] = (double*)malloc(sizeof(double) * Zn);
	}


	double** p_past = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		p_past[i] = (double*)malloc(sizeof(double) * Zn);
	}


	double** temp = (double**)malloc(sizeof(double*) * Xn);
	for (int i = 0; i < Xn; i++)
	{
		temp[i] = (double*)malloc(sizeof(double) * Zn);
	}

    //波前
	double** wavefront = (double**)malloc(sizeof(double*) * Tn);
	for (int i = 0; i < Tn; i++)
	{
		wavefront[i] = (double*)malloc(sizeof(double) * Zn);
	}


	double** p_temp;

	for (int i = 0; i < Xn; i++)
	{
		for (int j = 0; j < Zn; j++)
		{
			p_now[i][j] = 0;
			p_past[i][j] = 0;
			temp[i][j] = 0;
		}
	}
	for (int i = 0; i < Tn; i++)
	{
		for (int j = 0; j < Zn; j++)
		{
			wavefront[i][j]=0;
		}
	}
	

	for (int k = 0; k < Tn; k++)
	{
		for (int i = 2; i < Xn - 2; i++)
		{
			for (int j = 2; j < Zn - 2; j++)
			{
				//吸收边界
				/*int A = vel[i][j] * DH/DT  ;
				p_now[2][j] = (2 - 2 * A - pow(A, 2)) * temp[2][j] + 2 * A * (1 + A) * temp[3][j] - pow(A, 2) * temp[4][j] + (2 * A - 1) * p_past[2][j] - 2 * A * p_past[3][j];//左边界
				p_now[Xn - 3][j] = (2 - 2 * A - pow(A, 2)) * temp[Xn - 3][j] + 2 * A * (1 + A) * temp[Xn - 4][j] - pow(A, 2) * temp[Xn - 5][j] + (2 * A - 1) * p_past[Xn - 3][j] - 2 * A * p_past[Xn - 4][j];//右边界
				p_now[i][2] = (2 - 2 * A - pow(A, 2)) * temp[i][2] + 2 * A * (1 + A) * temp[i][3] - pow(A, 2) * temp[i][4] + (2 * A - 1) * p_past[i][2] - 2 * A * p_past[i][3];//上边界
				p_now[i][Zn - 3] = (2 - 2 * A - pow(A, 2)) * temp[i][Zn - 3] + 2 * A * (1 + A) * temp[i][Zn - 4] - pow(A, 2) * temp[i][Zn - 5] + (2 * A - 1) * p_past[i][Zn - 3] - 2 * A * p_past[i][Zn - 4];//下边界*/
				p_now[i][j] = 2 * temp[i][j] - p_past[i][j] + (vel[i][j] * vel[i][j] * DT * DT / (DH * DH)) * (-1.0 / 12 * (temp[i - 2][j]
					+ temp[i + 2][j]) + 4 / 3.0 * (temp[i - 1][j] + temp[i + 1][j]) - 5 / 2.0 * temp[i][j] - 1.0 / 12 * (temp[i][j - 2] + temp[i][j + 2])
					+ 4 / 3.0 * (temp[i][j - 1] + temp[i][j + 1]) - 5 / 2.0 * temp[i][j]) + w[k] * (i == X && j == Y) ;
				/*wavefront[k] [j]= p_now[2][j];//地震记录*/
			}
		}

		p_temp = p_now;
		p_now = p_past;
		p_past = temp;
		temp = p_temp;
	}

	printf("Xn is %d,Zn is %d,Tn is %d\n", Xn, Zn, Tn);

	//将矩阵数据写入文件
	FILE* fp;
	errno_t error;
	error = fopen_s(&fp, "wavefront.dat", "w+");

	//波前记录
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
			fprintf(fp, "\n");
		}
	}

	//地震记录
	/*
	if (error != 0)
	{
		printf("打开失败");
	}
	else
	{
		for (int i = 0; i < Tn; i++)
		{
			for (int j = 0; j < Zn; j++)
			{
				fprintf(fp, "%lf ", wavefront[i][j]);
			}
			fprintf(fp, "\n");
		}
	}
	*/

	//释放指针
	fclose(fp);
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
