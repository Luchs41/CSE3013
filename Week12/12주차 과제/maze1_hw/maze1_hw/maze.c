#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void v_print(int* v_wall);
void h_print(int* h_wall);
void v_connect(int* h_wall);
void h_connect(int* v_wall);

int num = 0;
int id = 0;
int WIDTH, HEIGHT;
int** h_wall;
int** v_wall;
int* room_num;

FILE* fp;

int main()
{
	int i, j, k;
	int currwall = -1;
	fp = fopen("maze.maz", "wt");
	scanf("%d", &WIDTH);
	scanf("%d", &HEIGHT);

	h_wall = (int**)malloc(sizeof(int*)*(HEIGHT - 1));
	v_wall = (int**)malloc(sizeof(int*)*(HEIGHT));

	for (i = 0; i < HEIGHT - 1; i++)
	{
		h_wall[i] = (int*)malloc(sizeof(int)*WIDTH);
		v_wall[i] = (int*)malloc(sizeof(int)*WIDTH - 1);
	}

	v_wall[i] = (int*)malloc(sizeof(int)*WIDTH - 1);
	room_num = (int*)malloc(sizeof(int)*WIDTH);
	memset(room_num, 0, sizeof(room_num));

	for (i = 0; i < WIDTH; i++) fprintf(fp, "+-");
	fprintf(fp, "+\n");
	srand(time(NULL));

	for (i = 0; i < WIDTH - 1; i++) {
		v_wall[0][i] = rand() % 2;
		if (v_wall[0][i] == 1)
		{
			for (j = currwall + 1; j <= i; j++) room_num[j] = id;
			id = id + 1;
			currwall = i;
		}
	}
	for (i = currwall + 1; i < WIDTH; i++)
		room_num[i] = id;
	id = id + 1;


	for (k = 1; k < HEIGHT - 1; k++) {
		v_connect(h_wall[k - 1]);
		h_connect(v_wall[k]);
	}
	v_connect(h_wall[HEIGHT - 2]);

	for (i = 0; i < WIDTH - 1; i++)
	{
		if (room_num[i] != room_num[i + 1])
		{
			v_wall[HEIGHT - 1][i] = 0;
			currwall = room_num[i + 1];
			room_num[i + 1] = room_num[i];
			for (j = 0; j < WIDTH; j++)
			{
				if (room_num[j] == currwall)
					room_num[j] = room_num[i];
			}
		}
		else
		{
			v_wall[HEIGHT - 1][i] = 1;
		}
	}
	num = WIDTH;
	if (WIDTH > HEIGHT) num = HEIGHT;
	num = num / 2;

	for (i = 1; i <= num; )
	{
		j = rand() % (HEIGHT - 1);
		k = rand() % (WIDTH - 1);

		if (v_wall[j][k] == 1)
		{
			v_wall[j][k] = 0;
			i++;
		}
		else if (h_wall[j][k] == 1)
		{
			h_wall[j][k] = 0;
			i++;
		}
	}

	for (i = 0; i < HEIGHT - 1; i++)
	{
		v_print(v_wall[i]);
		h_print(h_wall[i]);
	}
	v_print(v_wall[i]);

	for (i = 0; i < WIDTH; i++) {
		fprintf(fp, "+-");
	}
	fprintf(fp, "+\n");
	return 0;
}

void v_print(int* v_wall)
{
	fprintf(fp, "|");
	for (int i = 0; i < WIDTH - 1; i++)
	{
		fprintf(fp, " ");
		if (v_wall[i] == 1)
			fprintf(fp, "|");
		else
			fprintf(fp, " ");
	}
	fprintf(fp, " |\n");
}
void h_print(int* h_wall)
{
	fprintf(fp, "+");
	for (int i = 0; i < WIDTH; i++)
	{
		if (h_wall[i] == 1)
			fprintf(fp, "-+");
		else
			fprintf(fp, " +");
	}
	fprintf(fp, "\n");
}
void v_connect(int* h_wall)
{
	int  cur_room = room_num[0], switch1 = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		h_wall[i] = rand() % 2;
		if (h_wall[i] == 0) switch1 = 1;
		if (i < WIDTH - 1)
		{
			if (cur_room != room_num[i + 1])
			{
				if (switch1 == 0) h_wall[i] = 0;
				switch1 = 0;
				cur_room = room_num[i + 1];
			}
		}
		if ((i == WIDTH - 1) && (switch1 == 0)) h_wall[i] = 0;
		if (h_wall[i] == 1) {
			room_num[i] = id;
			id = id + 1;
		}
	}
}
void h_connect(int* v_wall)
{
	int i, j, cur_room, pre_wall = -1;
	for (i = 0; i < WIDTH - 1; i++)
	{
		if (room_num[i] != room_num[i + 1])
		{
			v_wall[i] = rand() % 2;
			if (v_wall[i] == 0)
			{
				cur_room = room_num[i + 1];
				room_num[i + 1] = room_num[i];
				for (j = 0; j < WIDTH; j++)
				{
					if (room_num[j] == cur_room) room_num[j] = room_num[i];
				}

			}
			else v_wall[i] = 1;
		}
		else v_wall[i] = 1;
	}
}
