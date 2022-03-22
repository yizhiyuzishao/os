#pragma once
#include <stdlib.h>
//内存字
typedef struct WORD
{
	union {
		WORD *llink;
		WORD *uplink;
	} a;
	int tag;
	int size;
	WORD *rlink;
} WORD, head, foot, *Space;

#define MAX 128
#define e 1        //e
#define FootLoc(p) (p) + (p)->size - 1

void initMemory(Space &pav);//初始化内存
Space AllocBoundTag(Space &pav, int n); //分配内存
void Reclaim(Space &pav, Space p);//回收内存