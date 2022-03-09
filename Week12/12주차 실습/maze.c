#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void drawEndline();
void build_sero();
void build_garo();
void garo_absorption();
void sero_absorption();

int N, M;
int setnum = 0;
int* sero_wall;
int* garo_wall;
int* room_num;

FILE* fp;
int main()
{
	int wallnum = -1;
	int i, j;
	srand(time(NULL));

	scanf("%d", &N);
	scanf("%d", &M);
	fp = fopen("maze.maz", "wt");

	sero_wall = (int*)malloc(sizeof(int) * (N - 1));
	garo_wall = (int*)malloc(sizeof(int) * N);
	room_num = (int*)calloc(N, sizeof(int));
	drawEndline();

	for(i = 0; i < N - 1; i++)
	{
		sero_wall[i] = rand() % 2;
		if(sero_wall[i] == 1)
		{
			for(j = wallnum + 1; j <= i; j++)
			{
				room_num[j] = setnum;
			}
			setnum++;
			wallnum = i;
		}
	}

	for(i = wallnum + 1; i < N; i++)
	{
		room_num[i] = setnum;
	}
	setnum++;

	build_sero();
	//첫째 줄 완성

	for(i = 1; i < M - 1; i++)
	{
		garo_absorption();
		build_garo();
		sero_absorption();
		build_sero();
	}
	//마지막 줄 전까지

	garo_absorption();
	build_garo();

	for(i = 0; i < N - 1; i++)
	{
		if(room_num[i] != room_num[i + 1])
		{
			sero_wall[i] = 0;
			wallnum = room_num[i + 1];
			room_num[i + 1] = room_num[i];

			for(j = 0; j < N; j++)
				if(room_num[j] == wallnum)
					room_num[j] = room_num[i];
		}
		else
			sero_wall[i] = 1;
	}
	build_sero();
	drawEndline();
	fclose(fp);
	return 0;
}

void sero_absorption()
{
	int i, j;
	int num;

	for(i = 0; i < N - 1; i++)
	{
		if(room_num[i] != room_num[i + 1])
		{
			sero_wall[i] = rand() % 2;

			if(sero_wall[i] == 1)
			{
				num = room_num[i + 1];
				room_num[i + 1] = room_num[i];
				for(j = 0; j < N; j++)
				{
					if(room_num[j] == num)
						room_num[j] = room_num[i];
				}
				sero_wall[i] = 0;
			}
			else
				sero_wall[i] = 1;
		}
		else
			sero_wall[i] = 1;
	}
}
void garo_absorption()
{
	int i;
	int flag = 0;
	int num;

	num = room_num[0];

	for(i = 0; i < N; i++)
	{
		garo_wall[i] = rand() % 2;

		if(garo_wall[i] == 0)
			flag = 1;

		if(i <N - 1)
		{
			if(num != room_num[i + 1])
			{
				if(flag == 0)
					garo_wall[i] = 0;
				flag = 0;
				num = room_num[i + 1];
			}
		}

		if((i == N - 1) && (flag == 0))
			garo_wall[i] = 0;

		if(garo_wall[i] == 1)
		{
			room_num[i] = setnum;
			setnum++;
		}
	}
}

void build_sero()
{
	int i;
	fprintf(fp, "|");
	for(i = 0; i < N - 1; i++)
	{
		fprintf(fp, " ");
		if(sero_wall[i] == 1)
			fprintf(fp, "|");
		else
			fprintf(fp, " ");
	}
	fprintf(fp, " |\n");
}
void build_garo()
{
	int i;
	fprintf(fp, "+");
	for(i = 0; i < N; i++)
	{
		if(garo_wall[i] == 1)
			fprintf(fp, "-+");
		else
			fprintf(fp, " +");
	}
	fprintf(fp, "\n");
}
void drawEndline()
{
	int i;
	for(i = 0; i < N; i++)
	{
		fprintf(fp, "+-");
	}
	fprintf(fp, "+\n");
}