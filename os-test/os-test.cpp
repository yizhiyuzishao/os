// os-test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <stdio.h>
#include "../kernel/define.h"

void Print_free(Space p)
{ //输出内存的空闲块状态
	Space h, f;
	if (p)
	{
		h = p;
		f = FootLoc(h);
		do
		{
			printf("空闲块首址为%u，空闲块大小为%d\n", h->a.uplink, h->size);
			h = h->rlink;
			f = FootLoc(h);
		} while (h != p);
	}
}
void Print_used(S_Space p[])
{ //输出p数组所指的已分配空间
	int i;
	for (i = front; i < MAX / e; i++)
		if (p[i].s)
		{
			printf("段%d的首地址=%u ", i, p[i].s); /* 输出结点信息 */
			printf("段的大小=%d\n", p[i].s->size);
		}
}
void Print_Process()
{ //输出段表信息
	int i, n;

	printf("请输入进程号：");
	scanf("%d", &n);
	printf("进程名为：%s\n", A[n].name);
	printf("虚拟段号 状态位 内存起始地址 长度 进程进入时间\n");
	for (i = 0; i < A[n].seg_size; i++)
	{
		printf("%8d %6d %12u %4d", i, A[n].seg[i].status, A[n].seg[i].start, A[n].seg[i].length);
		printf("%12d", A[n].seg[i].time);
		printf("\n");
	}
}

void createP() {
	int pro_num;//要创建多少个进程
	char pro_name[20]; //进程名称
	int seg_num;//进程的段数
	int seg_size[10] = {-1};//每个进程段的大小，每个进程规定最多10个段
	printf("请输入要创建的进程的个数:");
	scanf("%d", &pro_num);
	if (pro_num <= 0) {
		printf("进程个数要大于0，请重新输入:");
		scanf("%d", &pro_num);
	}
	for (int i = 0; i < pro_num; i++)
	{
		printf("请输入要创建的第%d个进程的名称:", i + 1);
		scanf("%s", &pro_name);
		printf("请输入要创建的第%d个进程的段数:", i + 1);
		scanf("%d", &seg_num);
		if (!(seg_num > 0 && seg_num <= 10)) {
			printf("每个进程中段的个数要大于0并且小于等于10，请重新输入:");
			scanf("%d", &seg_num);
		}
		for (int j = 0; j < seg_num; j++) {
			printf("请输入要创建的第%d个进程的第%d个段的长度:", i + 1, j + 1);
			scanf("%d", &seg_size[j]);
		}
		int a = CreateProcess(pro_name, seg_num, seg_size);
		if (a == 1) {
			printf("第%d个进程创建成功！\n", i + 1);
		}
		else
		{
			printf("第%d个进程创建失败！\n", i + 1);
		}
	}
}

void printA(Space &pav, Space &p) {
	int process_ID; //进程号
	int seg_ID;//段号
	int offset;//段内偏移

	printf("请输入进程号:");
	scanf("%d", &process_ID);
	printf("请输入段号:");
	scanf("%d", &seg_ID);
	printf("请输入段内偏移:");
	scanf("%d", &offset);
	WORD* q = PrintAddress(pav, p, process_ID, seg_ID, offset);
	if (InterruptType == 1)
	{
		printf("越界中断!!!\n");
	}
	else
	{
		if (InterruptType == 3)
		{
			printf("内存空间不足!!!\n");
			printf("完成FIFO置换!!\n");
		}
		else if(InterruptType == 2)
		{
			printf("缺段中断!!!\n");
		}
		if (q)
		{
			printf("物理地址为:%12u\n", q);
		}
	}
}

int main()
{ //菜单
	//printf("结构体WORD为%d个字节\n", sizeof(WORD));
	Space pav, p; //pav为空闲块指针'
	int i;
	//初始化内存
	initMemory(pav);
	//初始化进程
	initProcess();
	//输入结束标志
	int flag = 1;
	char name1[] = "a";   int seg1[] = { 2,3,4 };
	CreateProcess(name1, 3, seg1);

	while (flag) {
		int i;
		printf("请选择您需要的功能：\n");
		printf("1.创建进程\n");
		printf("2.查看进程\n");
		printf("3.显示内存状态\n");
		printf("4.地址映射\n");
		printf("5.退出\n");
		scanf("%d", &i);
		system("cls");

		switch (i)
		{
		case 1:
			createP();
			system("pause");
			system("cls");
			break;
		case 2:
			Print_Process();
			system("pause");
			system("cls");
			break;
		case 3:
			//system("cls");
			printf("内存的空闲块状态:\n");
			Print_free(pav);
			printf("已分配的空间:\n");
			Print_used(v);
			system("pause");
			system("cls");
			
			break;
		case 4:
			printA(pav, p);
			system("pause");
			system("cls");

			break;
		case 5:
			system("cls");
			printf("谢谢使用！");
			flag = 0;
			break;

		default:
			printf("输入错误,请重新选择!\n");
			break;
		}
	}
	return 0;
}



