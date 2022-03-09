#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	endwin();
	system("clear");
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(9,WIDTH+10);
	printw("SCORE");
	DrawBox(10,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(11,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX)
{
	// user code
	int i, j;
	//블록이 4X4 행렬이므로 이중loop를 사용하여 check
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		for(j = 0; j < BLOCK_WIDTH; j++)
		{
			if(block[currentBlock][blockRotate][i][j])
			{
				if((i + blockY) >= HEIGHT || (i + blockY) < 0 || (j + blockX) < 0 || (j + blockX) >= WIDTH)
					return 0;
				if(field[i + blockY][j + blockX] == 1)
					return 0;
			}//해당 필드에 이미 블록이 있거나, 블록이 필드의 최대 범위를 벗어나는 경우
			//블록을 놓을 수 없으므로 0을 리턴한다. 
		}
	}
	return 1;//위의 조건을 모두 만족하지 않을 경우, 1을 리턴하여 블록을 놓을 수 있음을 알린다. 

}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX)
{
	// user code
	//이전 좌표에서 지워져야 할 부분을 지우기 위해 command를 입력받기 전의 상태로 돌린다. 
	switch(command)
	{
		case KEY_UP:
			blockRotate = (blockRotate - 1) % 4;
			if(blockRotate < 0)
				blockRotate = 3;
			break;
		case KEY_DOWN:
			blockY--;
			break;
		case KEY_RIGHT:
			blockX--;
			break;
		case KEY_LEFT:
			blockX++;
			break;
		default:
			break;
	}
	

	int i, j;//해당 위치가 필드 내에 있다면 그 위치에 "."을 추가한다. 
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		for(j = 0; j < BLOCK_WIDTH; j++)
		{
			if(block[currentBlock][blockRotate][i][j] && i + blockY >= 0)
			{
				move(i + blockY + 1, j + blockX + 1);
				printw(".");
			}
		}
	}
	
	switch(command)//블록을 command를 입력받은 후의 상태로 돌린다. 
	{
		case KEY_UP:
			blockRotate = (blockRotate + 1) % 4;
			break;
		case KEY_DOWN:
			blockY++;
			break;
		case KEY_RIGHT:
			blockX++;
			break;
		case KEY_LEFT:
			blockX--;
			break;
		default:
			break;
	}//해당 블록의 모습을 출력한다. 
	DrawBlock(blockY, blockX, currentBlock, blockRotate, ' ');
	move(HEIGHT, WIDTH + 10);

}

void BlockDown(int sig)
{
	// user code
	//CheckToMove를 이용해, 블록이 아래로 내려갈 수 있다면 아래로 한 칸 옮긴다. 
	if(CheckToMove(field, nextBlock[0], blockRotate, blockY + 1, blockX))
	{
		blockY++;
		DrawChange(field, KEY_DOWN, nextBlock[0], blockRotate, blockY, blockX);
	}
	else//블록이 아래로 내려갈 수 없는 경우
	{
		if(blockY == -1)//만약 블록이 y축 범위를 벗어날 경우(새로 더 쌓이지 못 할 경우)
			gameOver = 1; //게임오버

		AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		//새로운 블록을 필드에 추가한다(위치를 고정)
		score += DeleteLine(field);	//만약 채워서 사라진 라인이 있다면, 점수를 추가한다. 

		nextBlock[0] = nextBlock[1];
		nextBlock[1] = nextBlock[2];
		nextBlock[2] = rand()%7;
		//다음 블록을 현재 블록으로 바꾸고, 새로운 다음 블록을 만든다. 
		
		blockRotate = 0;
		blockY = -1;
		blockX = WIDTH / 2 - 2;
		//새로 만든 블록의 정보 초기화

		DrawNextBlock(nextBlock);
		//다음 블록을 NextBlock박스에 그려준다. 
		DrawField();
		PrintScore(score);
		DrawBlock(blockY, blockX, nextBlock[0], blockRotate, ' ');
		//필드와 점수판을 갱신하고, 새로운 현재 블록을 그린다. 
	}

	timed_out = 0;

}

void AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX)
{
	// user code
	int i, j;
	//블록의 크기 4X4만큼 이중loop를 통해 블록이 놓여지는 위치의 field값을 1로 바꾸어
	//블록이 놓여졌음을 표시한다.
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		for(j = 0; j < BLOCK_WIDTH; j++)
		{
			if(block[currentBlock][blockRotate][i][j])
			{
				f[blockY + i][blockX + j] = 1;
			}
		}
	}


}

int DeleteLine(char f[HEIGHT][WIDTH])
{
	// user code
	int i, j, k;
	int lflag=0;
	int linecount=0;

	for(i=HEIGHT-1;i>=0;i--)
	{
		for(j=0;j<WIDTH;j++)
		{
			if(f[i][j]==0)
				break;

			if(f[i][j]==1&&j==WIDTH-1)
				lflag=1;
		}

		if(lflag==1)
		{
			linecount++;

			for(j=i;j>0;j--)
			{
				for(k=0;k<WIDTH;k++)
				{
					f[j][k]=f[j-1][k];
				}
			}
			
			for(k=0;k<WIDTH;k++)
				f[0][k]=0;

			lflag=0;
			i++;
		}
	}

	return (linecount*linecount*100);
}

void DrawShadow(int y, int x, int blockID,int blockRotate){
	// user code
}

void createRankList(){
	// user code
}

void rank(){
	// user code
}

void writeRankFile(){
	// user code
}

void newRank(int score){
	// user code
}

void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수

	// user code

	return max;
}

void recommendedPlay(){
	// user code
}
