#pragma once
#include <stdlib.h>
//�ڴ���
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

void initMemory(Space &pav);//��ʼ���ڴ�
Space AllocBoundTag(Space &pav, int n); //�����ڴ�
void Reclaim(Space &pav, Space p);//�����ڴ�