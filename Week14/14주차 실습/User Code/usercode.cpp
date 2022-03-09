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
void freeMemory();

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
typedef struct stack
{
	int x;
	int y;
}stack;



char** realmaze;
stack* S;
int** visited;
bool dfs_done = false;
int width=0, height=0, stacknum=0;

bool readFile(const char* filename){
	//start of the user code
	char tmp;
	int i=0, j=0;

	height=0;
	width=0;
	stacknum=0;

	FILE* fp = fopen(filename, "r");

	if( fp == NULL )
		return false;
	
	dfs_done = false;

	while( fscanf(fp, "%c", &tmp) != EOF )
	{
		if( tmp == '\n' )
		{
			height++;
			width=0;
		}
		else
			width++;
	}

	fclose(fp);

	realmaze=(char**)malloc(sizeof(char*)*(height+1));
	for(i=0;i<height+1;i++)
		realmaze[i]=(char*)malloc(sizeof(char)*(width));

	S=(stack*)malloc(sizeof(stack)*(height+1)*width);

	fp = fopen(filename, "r");
	i=0;
	j=0;
	while( fscanf(fp, "%c", &tmp) != EOF )
	{
		realmaze[i][j]=tmp;
		if( realmaze[i][j] == '\n' )
		{
			i++;
			j=0;
		}
		else
			j++;
	}
	fclose(fp);

	visited=(int**)malloc(sizeof(int*)*height);
	for(i=0;i<height;i++)
		visited[i]=(int*)malloc(sizeof(int)*width);

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			visited[i][j] = false;
		}
	}

	setWindow(0, 0, width, height+1, 1);

	return true; //edit after finish this function
	//end of usercode
}

/******************************************************************
* function	: bool FreeMemory()
*
* remark	: Save user data to a file
*******************************************************************/
void freeMemory(){
	//start of the user code
	//end of usercode
	int i;

	for(i=0;i<height;i++)
	{
		free(visited[i]);
	}

	free(visited);
	free(S);
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
	int i,j;
	int fromx,fromy,tox,toy;

	for(i=1; i<=height+1; i++)
	{

		for(j=1; j<=width; j++)
		{
			if( realmaze[i-1][j-1] == '-' )
			{
				DrawLine_I(j+1, i, j-1, i, 3, RGB(0,0,150));
			}
			else if( realmaze[i-1][j-1] == '|' )
			{
				DrawLine_I(j, i-1, j, i+1, 3, RGB(0,0,150));
			}
		}
	}

	DrawSolidBox_I(2-0.5,2-0.5,2+1-0.5,2+1-0.5,1,RGB(29,219,22),RGB(29,219,22));
	DrawSolidBox_I(width-1-0.5,height-0.5,width-0.5,height+0.5,1,RGB(255,0,0),RGB(255,0,0));

	if( dfs_done )
	{
		for(i=2; i<height; i++)
		{
			for(j=2; j<width; j++)
			{
				if( visited[i][j-1] && visited[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j, i+1, 5, RGB(100,150,150));
				}
				if( visited[i-1][j] && visited[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j+1, i, 5, RGB(100,150,150));
				}
			}
		}

		for(j=2;j<width;j++)
		{
			if(visited[height-1][j]&&visited[height-1][j-1])
				DrawLine_I(j,height,j+1,height,5,RGB(100,150,150));
		}

		for(i=0; i<stacknum-1; i++)
		{
			DrawLine_I(S[i].x+1, S[i].y+1, S[i+1].x+1, S[i+1].y+1, 5, RGB(30,30,30));
		}
	}

	
}

void DFS()
{
	if( dfs_done )
		return;

	int x=1, y=1;

	visited[y][x] = true;
	stacknum = 0;
	S[stacknum].y = y;
	S[stacknum].x = x;
	stacknum++;

	while(1)
	{
		int block=0; 

	
		if( y == height-1 && x == width-2)
		{
			S[stacknum].y = y;
			S[stacknum].x = x;
			stacknum++;
			visited[y][x] = true;
			break;
		}
		
	
		if( y < height-1)
		{
			if( visited[y+1][x] == false && realmaze[y+1][x] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited[y+1][x] = true;
				y++;
				block = 1;
				continue;
			}
		}


		if( x < width-1 )
		{
			if( visited[y][x+1] == false && realmaze[y][x+1] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited[y][x+1] = true;
				x++;
				block = 1;
				continue;
			}
		}
		
		if( y > 1 )
		{
			if( visited[y-1][x] == false && realmaze[y-1][x] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited[y-1][x] = true;
				y--;
				block = 1;
				continue;
			}
		}

		if( x > 1 )
		{
			if( visited[y][x-1] == false && realmaze[y][x-1] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited[y][x-1] = true;
				x--;
				block = 1;
				continue;
			}
		}

		if( block == 0 )
		{
			stacknum--;
			x = S[stacknum].x;
			y = S[stacknum].y;
		}
	}

	dfs_done = true;
}
