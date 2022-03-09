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
int mode=0;

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

typedef struct queue
{
	int x;
	int y;
	int fromx;
	int fromy;
}queue;

int front,rear;

char** realmaze;
stack* S;
queue* Q;
int** visited_d;
int** visited_b;
bool dfs_done = false;
bool bfs_done=false;
int width=0, height=0, stacknum=0;

bool readFile(const char* filename){
	//start of the user code
	mode=0;
	char tmp;
	int i=0, j=0;

	height=0;
	width=0;
	stacknum=0;

	FILE* fp = fopen(filename, "r");

	if( fp == NULL )
		return false;
	
	dfs_done = false;
	bfs_done=false;

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
	Q=(queue*)malloc(sizeof(queue)*(height+1)*width);

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

	visited_d=(int**)malloc(sizeof(int*)*height);
	for(i=0;i<height;i++)
		visited_d[i]=(int*)malloc(sizeof(int)*width);
	visited_b=(int**)malloc(sizeof(int*)*height);
	for(i=0;i<height;i++)
		visited_b[i]=(int*)malloc(sizeof(int)*width);

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			visited_d[i][j] = false;
			visited_b[i][j] = false;

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
		free(visited_b[i]);
				free(visited_d[i]);

	}

	free(visited_b);
	free(visited_d);
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

	if(mode==1){
	if( dfs_done )
	{
		for(i=2; i<height; i++)
		{
			for(j=2; j<width; j++)
			{
				if( visited_d[i][j-1] && visited_d[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j, i+1, 5, RGB(150,80,150));
				}
				if( visited_d[i-1][j] && visited_d[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j+1, i, 5, RGB(150,80,150));
				}
			}
		}

		for(j=2;j<width;j++)
		{
			if(visited_d[height-1][j]&&visited_d[height-1][j-1])
				DrawLine_I(j,height,j+1,height,5,RGB(150,80,150));
		}

		for(i=0; i<stacknum-1; i++)
		{
			DrawLine_I(S[i].x+1, S[i].y+1, S[i+1].x+1, S[i+1].y+1, 5, RGB(30,30,30));
		}
	}
	}

	if(mode==2){
	if( bfs_done )
	{
		for(i=2; i<height; i++)
		{
			for(j=2; j<width; j++)
			{
				if( visited_b[i][j-1] && visited_b[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j, i+1, 5, RGB(150,80,150));
				}
				if( visited_b[i-1][j] && visited_b[i-1][j-1] == true )
				{
					DrawLine_I(j, i, j+1, i, 5, RGB(150,80,150));
				}
				
			}
		}

		for(j=2;j<width;j++)
		{
			if(visited_b[height-1][j]&&visited_b[height-1][j-1])
				DrawLine_I(j,height,j+1,height,5,RGB(150,80,150));
		}

		fromx=Q[rear].fromx;
		fromy=Q[rear].fromy;
		tox=Q[rear].x;
		toy=Q[rear].y;			
		DrawLine_I(fromx+1,fromy+1,tox+1,toy+1,5,RGB(30,30,30));

		for(i=rear-1;i>=0;i--)
		{
			tox=Q[i].x;
			toy=Q[i].y;
			if(tox==fromx&&toy==fromy)
			{
				fromx=Q[i].fromx;
				fromy=Q[i].fromy;
				DrawLine_I(fromx+1,fromy+1,tox+1,toy+1,5,RGB(30,30,30));
			}
		}
	}
	}
}

void DFS()
{
	if( dfs_done )
	{
		mode=1;
		dfs_done=true;
		return;
	}

	int x=1, y=1;
	int i, j;

	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			visited_d[i][j] = false;
		}
	}

	visited_d[y][x] = true;
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
			visited_d[y][x] = true;
			break;
		}
		
		if( y < height-1)
		{
			if( visited_d[y+1][x] == false && realmaze[y+1][x] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited_d[y+1][x] = true;
				y++;
				block = 1;
				continue;
			}
		}

		if( x < width-1 )
		{
			if( visited_d[y][x+1] == false && realmaze[y][x+1] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited_d[y][x+1] = true;
				x++;
				block = 1;
				continue;
			}
		}
		
		if( y > 1 )
		{
			if( visited_d[y-1][x] == false && realmaze[y-1][x] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited_d[y-1][x] = true;
				y--;
				block = 1;
				continue;
			}
		}

		if( x > 1 )
		{
			if( visited_d[y][x-1] == false && realmaze[y][x-1] == ' ' )
			{
				S[stacknum].y = y;
				S[stacknum].x = x;
				stacknum++;
				visited_d[y][x-1] = true;
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

void BFS()
{
	if(bfs_done)
	{
		mode=2;
		bfs_done=true;
		return;
	}

	int i=0,j=0;
	int x=1,y=1;
	
	for(i=0; i<height; i++)
	{
		for(j=0; j<width; j++)
		{
			visited_b[i][j] = false;
		}
	}

	visited_b[1][1]=true;

	front=-1;
	rear=0;
	Q[rear].y=y;
	Q[rear].x=x;
	Q[rear].fromx=x;
	Q[rear].fromy=y;
	rear++;

	while(1)
	{
		front++;
		y=Q[front].y;
		x=Q[front].x;

		if(y==height-1&&x==width-2)
		{
			Q[rear].y=y;
			Q[rear].x=x;
			Q[rear].fromx=x;
			Q[rear].fromy=y;
			visited_b[y][x]=true;
			break;
		}

		if(y<height-1)
		{
			if(visited_b[y+1][x]==false && realmaze[y+1][x]==' ')
			{
				Q[rear].y=y+1;
				Q[rear].x=x;
				Q[rear].fromx=x;
				Q[rear].fromy=y;
				rear++;
				visited_b[y+1][x]=true;
				visited_b[y][x] = true;
			}
		}

		if(x<width-1)
		{
			if(visited_b[y][x+1]==false&&realmaze[y][x+1]==' ')
			{
				Q[rear].y=y;
				Q[rear].x=x+1;
				Q[rear].fromx=x;
				Q[rear].fromy=y;
				rear++;
				visited_b[y][x+1]=true;
				visited_b[y][x] = true;
			}
		}

		if(y>1)
		{
			if(visited_b[y-1][x]==false&&realmaze[y-1][x]==' ')
			{
				Q[rear].y=y-1;
				Q[rear].x=x;
				Q[rear].fromx=x;
				Q[rear].fromy=y;
				rear++;
				visited_b[y-1][x]=true;
				visited_b[y][x] = true;
			}
		}

		if(x>1)
		{
			if(visited_b[y][x-1]==false&&realmaze[y][x-1]==' ')
			{
				Q[rear].y=y;
				Q[rear].x=x-1;
				Q[rear].fromx=x;
				Q[rear].fromy=y;
				rear++;
				visited_b[y][x-1]=true;
				visited_b[y][x] = true;
			}
		}
	}
	bfs_done=true;
}