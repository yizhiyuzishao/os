#include "Process.h"
//��ʼ������
void initProcess() {
	A = (Process *)malloc(LIST_INIT_SIZE * sizeof(Process));
	for (int i = 0; i < LIST_INIT_SIZE; i++) {
		A[i].ID = -1;
		A[i].seg_size = -1;
		A[i].has_allocated = -1;
		for (int j = 0; j < Max_Segment; j++) {
			A[i].seg[j].status = 0;
			A[i].seg[j].length = -1;
			A[i].seg[j].time = -1;
			A[i].seg[j].start = NULL;
		}
	}
}
int NUMBER = 0;



//��������,����ֵ:1������̴����ɹ���2������̶�������10
int CreateProcess(char name[20], int segnum, int segsize[])
{ //���ն�����̼�������Ϣ
	//�������Ķ�������10������2
	if (segnum > 10)
		return 2;

	A[NUMBER].ID = NUMBER;
	strcpy_s(A[NUMBER].name, name);
	A[NUMBER].seg_size = segnum;

	for (int i = 0; i < A[NUMBER].seg_size; i++)
	{
		A[NUMBER].seg[i].length = segsize[i];
	}
	NUMBER++;
	//���̴����ɹ�������1
	return 1;
}