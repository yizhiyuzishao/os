#pragma once
#pragma warning(disable:4996)

#include "Process.h"
#include "Process.cpp"

int entertime = 0; //ȫ�ֱ��������ڱ�ʾ���̽����ʱ������
int SIZE = 0;
int InterruptType = -1; //�ж����ͣ�1����Խ���жϣ�2����ȱ���ж�,3�����ڴ����жϣ������FIFO��


typedef struct
{
	Space s; //ռ�ÿ�ָ��ѭ������(��ʼ��Ϊ��)�����ȫ�ֱ���numberʵ��
	int num; //���̱��
} S_Space;
S_Space v[MAX / e] = { NULL }; 
int front = 0;                 //��¼������Ԫ��λ��
int number = 0;                //ȫ�ֱ�������number�������ڴ�Ķ�



bool FIFO(Space &pav, Space &p);//�滻�㷨��FIFO
WORD* PrintAddress(Space &pav, Space &a, int processId, int segId, int offset); //��ַӳ��
WORD* MissSegInt(Space &pav, Space &a, int processId, int segId, int offset); //ȱ���жϴ���



//�滻�㷨,FIFO
bool FIFO(Space &pav, Space &p)
{ //��̭�㷨�������ö���v�Ķ�ͷԪ�أ�FIFO��������洢���н�����Ϣ�е�A.seg[i].start���бȽϣ���ͬ���������Ϣ�����޸�
	for (int i = 0; i < A[v[front].num].seg_size; i++)
		if (A[v[front].num].seg[i].start == v[front].s)
		{
			A[v[front].num].seg[i].status = 0;
			A[v[front].num].seg[i].start = NULL;
			SIZE = SIZE - A[v[front].num].seg[i].length;
			p = A[v[front].num].seg[i].start;
			A[v[front].num].has_allocated--;
			break;
		};
	front++;
	Reclaim(pav, p);
	p = v[front].s;
	return true;
}

//��ַӳ��
WORD* PrintAddress(Space &pav, Space &a,int processId, int segId, int offset)
{ 
	//�����ж�����
	InterruptType = -1;
	WORD *q;
	if (offset > A[processId].seg[segId].length) {
		//����Խ��
		InterruptType = 1;
		return NULL;
	}
	else {
		if (A[processId].seg[segId].status) //�ö����ڴ���
		{
			q = A[processId].seg[segId].start + offset * sizeof(WORD);
		}
		else //�öβ����ڴ���
		{
			//ȱ���ж�����
			InterruptType = 2;
			//ȱ���жϴ���
			q = MissSegInt(pav, a, processId, segId, offset);
		}
		return q;
	}
}

//ȱ���жϴ���
WORD* MissSegInt(Space &pav, Space &a, int processId, int segId, int offset) {
	WORD *q;
	for (;;)
		if (SIZE + A[processId].seg[segId].length <= MAX)
		{
			a = AllocBoundTag(pav, A[processId].seg[segId].length);
			if (!a) {
				InterruptType = 3;
				FIFO(pav, a);
			}
			else {
				SIZE += A[processId].seg[segId].length;
				A[processId].has_allocated++;
				A[processId].seg[segId].start = a;
				v[number % (MAX / e)].s = A[processId].seg[segId].start;
				v[number % (MAX / e)].num = processId;
				A[processId].seg[segId].status = 1;
				A[processId].seg[segId].time = entertime;
				entertime++;
				q = A[processId].seg[segId].start + offset * sizeof(WORD);
				number++;
				return q;
			}	
		}
		else {
			InterruptType = 3;
			FIFO(pav, a);
		}
}

