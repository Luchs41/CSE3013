#include "tetris.h"
#include <stdlib.h>

static struct sigaction act, oact;


int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));
	
	createRankList();
	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}
	writeRankFile();
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
	nextBlock[2]=rand()%7;
	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlockWithFeatures(blockY,blockX,nextBlock[0],blockRotate);
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

	DrawBox(10,WIDTH+10,4,8);

	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(20,WIDTH+10);
	printw("SCORE");
	DrawBox(21,WIDTH+10,1,8);
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
	move(22,WIDTH+11);
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
	for( i = 0; i < 4; i++ ){
			move(11+i,WIDTH+13);
			for( j = 0; j < 4; j++ ){
				if( block[nextBlock[2]][0][i][j] == 1 ){
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
	
	DrawField();	//새로운 정보에 맞게 화면을 그린다. 
	
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
	DrawBlockWithFeatures(blockY, blockX, currentBlock, blockRotate);
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

		score += AddBlockToField(field, nextBlock[0], blockRotate, blockY, blockX);
		//새로운 블록을 필드에 추가한다(위치를 고정)
		//추가로, 바닥에 닿은 면적만큼의 점수를 추가한다. 
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
		DrawBlockWithFeatures(blockY, blockX, nextBlock[0], blockRotate);
		//필드와 점수판을 갱신하고, 새로운 현재 블록을 그린다. 
	}

	timed_out = 0;

}

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX)
{
	// user code
	int i, j;
	int touched = 0;	//땅에 닿은 면적
	//블록의 크기 4X4만큼 이중loop를 통해 블록이 놓여지는 위치의 field값을 1로 바꾸어
	//블록이 놓여졌음을 표시한다.
	for(i = 0; i < BLOCK_HEIGHT; i++)
	{
		for(j = 0; j < BLOCK_WIDTH; j++)
		{
			if(block[currentBlock][blockRotate][i][j])
			{
				f[blockY + i][blockX + j] = 1;
				if(f[blockY + i + 1][blockX + j] == 1 || blockY + i + 1 == HEIGHT)
					touched++;
				//해당 필드의 칸이 차있거나, 필드의 바닥에 닿았을 경우
				//touched를 증가시킨다. 
			}
		}
	}

	int score = touched * 10;
	return score;


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

void DrawShadow(int y, int x, int blockID,int blockRotate)
{
	// user code
	while(CheckToMove(field, blockID, blockRotate, y + 1, x) == 1 && y < HEIGHT)
	{
		y++;
	}
	//블록의 y좌표를 움직일 수 있을 때까지 증가시킨다. 
	//(CheckToMove값이 1이거나 바닥에 닿은 경우)
	DrawBlock(y, x, blockID, blockRotate, '/');

}

void createRankList(){
	// user code

	//rank.txt 파일을 읽어들인다.
	//가장 첫 줄엔 rank의 갯수

	FILE* fp = fopen("rank.txt", "r");
	int i;
	int newscore;
	char newname[NAMELEN];

	if(fp == NULL)
	{
		printf("FILE ERROR!!\n");
		return ;
	}
	else
	{
		fscanf(fp, "%d", &ranknum);

		for(i = 0; i < ranknum; i++)
		{
			fscanf(fp, "%s", newname);
			fscanf(fp, "%d", &newscore);
			insertnode(newscore, newname, &head);
		}
	}
	
	
	//구현한 자료구조에 따라서
	//파일을 다 읽어들이면 됨.
}

void rank(){
	int from = 0, to = 0;
	char name[NAMELEN];
	int del;
	int i;
	int count = 0;
	int move = 0;
	Node* temp;
	clear();
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	switch(wgetch(stdscr)){
		case '1':
			echo();
			printw("X: ");
			scanw("%d",&from);
			printw("Y: ");
			scanw("%d",&to);
			noecho();
			printw("       name       |   score   \n");
			printw("------------------------------\n");

			if((to < from && to != 0) || from < 0 || to < 0 || from > ranknum || to > ranknum || head == NULL)
				printw("\nsearch failure: no rank in the list\n");

			else if(from == 0 && to == 0)
			{
				for(temp = head; temp != NULL; temp = temp->link)
				{
					fflush(stdin);
					printw("%s", temp->name);
					move(7 + move, 18);
					move++;
					printw("|	%d\n", temp->score);
				}
			}
			else if(from == 0 && to != 0)
			{
				for(temp = head; temp != NULL; temp = temp->link)
				{
					if(count == to)
					{
						break;
					}
					count++;

					printw("%s", temp->name);
					move(7 + move, 18);
					move++;
					printw("|	%d\n", temp->score);
				}
			}
			else if(from != 0 && to == 0)
			{
				for(temp = head; temp != NULL; temp = temp->link)
				{
					if(count == ranknum)
						break;

					count++;
					if(count >= from)
					{
						printw("%s", temp->name);
						move(7+move, 18);
						move++;
						printw("|	%d\n", temp->score);
					}
				}
			}
			else if(from != 0 && to != 0)
			{
				for(temp = head; temp != NULL; temp = temp->link)
				{
					if(count == to)
						break;
					count ++;
					if(count >= from)
					{
						printw("%s", temp->name);
						move(7 + move, 18);
						move++;
						printw("|	%d\n", temp->score);
					}
				}
			}
			//getch();

			break;
		case '2':
			printw("input the name: ");
			echo();
			getstr(name);
			noecho();
			printw("       name       |   score   \n");
			printw("------------------------------\n");
			searchByName(name);


			break;
		case '3':
			printw("input the rank: ");
			echo();
			scanw("%d",&del);
			noecho();

			if(!rankDelete(del))
			{
				printw("\nsearch failure: the rank not in the list\n");
			}
			else	
			{
				printw("\nresult: the rank deleted\n");
			}
			fflush(stdin);
			break;

		default: break;
	}
	getch();
	// user code
}

void searchByName(char name[NAMELEN])
{
	int move = 0;
	Node* temp;
	
	for(temp = head; temp != NULL; temp = temp->link)
	{
		if(strcmp(name, temp->name) == 0)
		{
			printw("%s", name);
			move(move + 6, 18);
			printw("|	%d\n", temp->score);
			move++;
		}
	}

	if(move == 0)	//해당 이름이 존재하지 않을 경우
	{
		printw("search failure: no name in the list\n");
	}
	fflush(stdin);

}

bool rankDelete(int del)
{
	Node* temp;
	temp = head;
	

	if(del <= 0 || ranknum == 0 || del > ranknum)
	{
		return false;
	}
	else
	{
		if(del == 1 && ranknum != 1)	//맨 앞의 랭킹 제거
		{
			head = head->link;
			ranknum--;
			return true;
		}
		if(del == 1 && ranknum == 1)	//rank의 원소가 하나일 때 랭킹 제거
		{
			head == NULL;
			ranknum--;
			return true;
		}
		if(del == ranknum)	//맨 뒤의 랭킹 제거
		{
			while(temp->link->link != NULL)
			{
				temp = temp->link;
			}
			temp->link = NULL;
			ranknum--;
			return true;
		}

		else	//그 밖의 경우
		{
			for(int i = 1; i < del - 1; i++)
			{
				temp = temp->link;
			}
			temp->link = temp->link->link;
			ranknum--;
			return true;
		}
		
		writeRankFile();
		createRankList();

	}
}

void writeRankFile(){
	// user code

	FILE* fp = fopen("rank.txt", "w");
	fprintf(fp, "%d\n", ranknum);
	int i;
	Node* temp = head;

	for(i = 0; i < ranknum; i++)
	{
		fprintf(fp, "%s %d\n", temp->name, temp->score);
		temp = temp->link;
	}
	fclose(fp);

}

void newRank(int score){
	// user code
	// 다음 코드 사이사이에 적절히 삽입

	char nameTemp[NAMELEN];
	clear();
	printw("your name: ");
	echo();
	getstr(nameTemp);
	noecho();
	ranknum++;
	insertnewnode(score, nameTemp, &head);

	//WriteRankFile();
}

void insertnewnode(int score, char name[NAMELEN], Node** head)
{
	Node* newNode;
	Node* prev;

	newNode = (Node*)malloc(sizeof(Node));
	newNode->score = score;
	strcpy(newNode->name, name);
	newNode->link = NULL;
	Node* temp = *head;

	if(*head == NULL)
	{
		*head = newNode;
		return ;
	}
	else
	{
		prev = temp;
		if(temp->score < score)
		{
			newNode->link = temp;
			*head = newNode;
			return ;
		}
		while((temp->score >= score) && (temp->link != NULL))
		{
			prev = temp;
			temp = temp->link;
		}
		if(temp->link != NULL)
		{
			newNode->link = temp;
			prev->link = newNode;
		}
		else
		{
			temp->link = newNode;
		}
	}
}

void insertnode(int score, char name[NAMELEN], Node** head)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	Node* last = *head;

	newNode->score = score;
	strcpy(newNode->name, name);
	newNode->link = NULL;

	if(*head == NULL)
	{
		*head = newNode;
		return ;
	}

	while(last->link != NULL)
	{
		last = last->link;
	}
	last->link = newNode;
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

void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate)
{
	DrawBlock(y, x, blockID, blockRotate, ' ');
	DrawShadow(y, x, blockID, blockRotate);
}
