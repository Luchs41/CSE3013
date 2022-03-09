#include <stdlib.h>
#include "..\ExternDoc.h"
#include "..\UI\Zoom.h"
#include "..\UI\MsgView.h"
#include "..\Graphics\DrawFunc.h"
#include "..\Example\Example.h"

#define ERROR_NUMBER -1

//function prototype

static void drawDirect(CDC *pDC);
static void drawBuffered();

//Start of user code
#include <float.h>

/*****************************************************************
* function	: bool readFile(const char* filename)
* argument	: cons char* filename - filename to be opened
* return	: true if success, otherwise flase
* remark	: After read data file, phisycal view must be set;
*			  otherwise drawing will not be executed correctly.
*			  The window will be invalidated after readFile()
*			  returns true.
******************************************************************/

typedef struct maze{
	int up, down, right, left;
} maze;

maze** miro;
char** miro_char;
int N, M;
int i, j;

bool readFile(const char* filename){
	FILE* fp;
	char input;
	int HEIGHT, WIDTH;
	fp = fopen(filename, "r");
	if(fp == NULL)
		return false;
	N = M = 0;	//M은 세로길이 HEIGHT를, N은 가로길이 WIDTH를 구하는 데 사용된다. 
	while(fscanf(fp, "%c", &input) != EOF)
	{
		if(input == '+' || input == '-')
			N++;
		else
			break;
	}	//파일의 첫번째 줄을 읽어서 WIDTH를 파악한다. 
	M++;
	while(fscanf(fp, "%c", &input) != EOF)
	{
		if(input != '+' && input != '-' && input != ' ' && input != '|')
			M++;
	}

	fclose(fp);
	fp = fopen(filename, "r");

	miro_char = (char**)malloc(sizeof(char*) * (M + 2));
	for(i = 0; i < M + 2; i++)
		miro_char[i] = (char*)malloc(sizeof(char) * (N + 2));
	for(i = 0; i < M + 2; i++)
	{
		for(j = 0; j < N + 2; j++)
		{
			fscanf(fp, "%c", &input);
			miro_char[i][j] = input;
			if(input == '\0' || input == '\n')
			{
				miro_char[i][j] = '\0';
				break;
			}
		}
		if(input == '\0')
			break;
	}
	N--;

	HEIGHT = M / 2;
	WIDTH = N / 2;

	miro = (maze**)malloc(sizeof(maze*)*HEIGHT);
	for(i = 0; i < HEIGHT; i++)
	{
		miro[i] = (maze*)malloc(sizeof(maze) * WIDTH);
		for(j = 0; j < WIDTH; j++)
		{
			miro[i][j].up = FALSE;
			miro[i][j].down = FALSE;
			miro[i][j].left = FALSE;
			miro[i][j].right = FALSE;
		}
	}	//미로 정보의 초기값

	for(i = 0; i < M; i++)
	{
		if(i % 2)
		{
			for(j = 0; j < N; j++)
			{
				if(j % 2)
				{
					if(miro_char[i][j - 1] == '|')
						miro[i / 2][j / 2].left = TRUE;
					if(miro_char[i][j + 1] == '|')
						miro[i / 2][j / 2]. right = TRUE;
					if(miro_char[i - 1][j] == '-')
						miro[i / 2][j / 2].up = TRUE;
					if(miro_char[i + 1][j] == '-')
						miro[i / 2][j / 2].down = TRUE;
				}
			}
		}
	}	//미로 각 위치의 상하좌우를 체크하여 각 방향으로 이동할 수 있으면 TRUE로 값을 바꾼다. 
	setWindow(0, 0, N / 2, M / 2, 1);
	fclose(fp);

	return true; 
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	for(i = 0; i < M / 2; i++)
	{
		free(miro[i]);
		free(miro_char[i]);
	}
	free(miro);
	free(miro_char);
}

/**************************************************************
* function	: bool writeFile(const char* filename)
*
* argument	: const char* filename - filename to be written
* return	: true if success, otherwise false
* remark	: Save user data to a file
****************************************************************/
bool writeFile(const char* filename){
	//start of the user code
	bool flag;
	flag = 0;

	return flag;
	//end of usercode
}

/************************************************************************
* fucntion	: void drawMain(CDC* pDC)
*
* argument	: CDC* pDC - device context object pointer
* remark	: Main drawing function. Called by CMFC_MainView::OnDraw()
*************************************************************************/
void drawMain(CDC *pDC){
	//if direct drawing is defined
#if defined(GRAPHICS_DIRECT)
	drawDirect(pDC);
	//if buffered drawing is defined
#elif defined(GRAPHICS_BUFFERED)
	drawBuffered();
#endif
}

/************************************************************************
* function	: static void drawDirect(CDC *pDC
*
* argument	: CDC* pDC - device context object pointer
* remark	: Direct drawing routines here.
*************************************************************************/
static void drawDirect(CDC *pDC){
	//begin of user code
	//Nothing to write currently.
	//end of user code
}

/***********************************************************************
* function	: static void drawBuffered()
*
* argument	: CDC* pDC -0 device object pointer
* remark	: Buffered drawing routines here.
************************************************************************/
static void drawBuffered(){
	//start of the user code
	//end of the user code
	DrawBox_I(0, 0, N / 2, M / 2, 3, RGB(100, 0, 0));

	for(i = 0; i < M; i++)
	{
		if(i % 2 && i / 2 < M / 2)
		{
			for(j = 0; j < N; j++)
			{
				if(j % 2 && j / 2 < N / 2)
				{
					if(miro[i / 2][j / 2].down && i / 2 + 1 < M / 2)
						DrawLine_I(j / 2, i / 2 + 1, j / 2 + 1, i / 2 + 1, 3, RGB(0, 0, 100));
					
					if(miro[i / 2][j / 2].right && j / 2 + 1 < N / 2)
						DrawLine_I(j / 2 + 1, i / 2, j / 2 + 1, i / 2 + 1, 3, RGB(0, 0, 100));
				}
			}
		}
	}
}