#pragma once
#pragma warning(disable:4996)

#include "Process.h"
#include "Process.cpp"

int entertime = 0; //全局变量，用于表示进程进入的时间序列
int SIZE = 0;
int InterruptType = -1; //中断类型，1代表越界中断，2代表缺段中断,3代表内存满中断（会采用FIFO）


typedef struct
{
	Space s; //占用块指针循环队列(初始化为空)，配合全局变量number实现
	int num; //进程编号
} S_Space;
S_Space v[MAX / e] = { NULL }; 
int front = 0;                 //记录队列首元素位置
int number = 0;                //全局变量，第number个进入内存的段



bool FIFO(Space &pav, Space &p);//替换算法，FIFO
WORD* PrintAddress(Space &pav, Space &a, int processId, int segId, int offset); //地址映射
WORD* MissSegInt(Space &pav, Space &a, int processId, int segId, int offset); //缺段中断处理



//替换算法,FIFO
bool FIFO(Space &pav, Space &p)
{ //淘汰算法，可利用队列v的队头元素（FIFO），再与存储所有进程信息中的A.seg[i].start进行比较，相同则对其中信息进行修改
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

//地址映射
WORD* PrintAddress(Space &pav, Space &a,int processId, int segId, int offset)
{ 
	//重置中断类型
	InterruptType = -1;
	WORD *q;
	if (offset > A[processId].seg[segId].length) {
		//发生越界
		InterruptType = 1;
		return NULL;
	}
	else {
		if (A[processId].seg[segId].status) //该段在内存中
		{
			q = A[processId].seg[segId].start + offset * sizeof(WORD);
		}
		else //该段不在内存中
		{
			//缺段中断类型
			InterruptType = 2;
			//缺段中断处理
			q = MissSegInt(pav, a, processId, segId, offset);
		}
		return q;
	}
}

//缺段中断处理
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

