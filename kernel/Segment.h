#pragma once
#include "Memory.h"
#include "Memory.cpp"
//段
typedef struct Segment
{
	WORD *start; //物理段起始地址
	int length; // 段长
	int status; //是否在内存中，0表示不在，1表示在
	int time; //存储进程进入时间
} Segment;
