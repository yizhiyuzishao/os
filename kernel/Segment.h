#pragma once
#include "Memory.h"
#include "Memory.cpp"
//��
typedef struct Segment
{
	WORD *start; //�������ʼ��ַ
	int length; // �γ�
	int status; //�Ƿ����ڴ��У�0��ʾ���ڣ�1��ʾ��
	int time; //�洢���̽���ʱ��
} Segment;
