#pragma once
#define NODE_MAX_NUM 100


void F1();
void F2(const char* fn);
char* F3(int n);

bool Cycle_check( int p[]);
bool dfs(int p[], int flag[], int c);

struct CASES{
	int k;
	int x[NODE_MAX_NUM];
	int y[NODE_MAX_NUM];
};

extern int testCaseNum;
extern int currentCase;
extern int P[NODE_MAX_NUM];


extern int testCaseNum;
extern int currentCase;

extern CASES *testcases;
extern char *resultString;