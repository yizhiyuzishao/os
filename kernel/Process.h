#pragma once
#include <string.h>
#include "Segment.h"
#define Max_Segment 10
#define LIST_INIT_SIZE 10
//����
typedef struct Process
{
	int ID;     //���̺�
	Segment seg[Max_Segment]; //seg�д洢����ÿ�ε���Ϣ,ÿ������������10����
	char name[20]; //������
	int seg_size;   //���̰����Ķ���
	int has_allocated; //�ѷ����ڴ�Ķ���
} Process;

Process* A;

void initProcess();//��ʼ������
int CreateProcess(char name[20], int segnum, int segsize[]);//��������
