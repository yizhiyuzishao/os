#pragma once
#include <string.h>
#include "Segment.h"
#define Max_Segment 10
#define LIST_INIT_SIZE 10
//进程
typedef struct Process
{
	int ID;     //进程号
	Segment seg[Max_Segment]; //seg中存储的是每段的信息,每个进程最多分配10个段
	char name[20]; //进程名
	int seg_size;   //进程包含的段数
	int has_allocated; //已分配内存的段数
} Process;

Process* A;

void initProcess();//初始化进程
int CreateProcess(char name[20], int segnum, int segsize[]);//创建进程
