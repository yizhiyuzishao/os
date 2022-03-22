#include "Memory.h"
//初始化内存
void initMemory(Space &pav)
{
	Space p;
	p = (WORD *)malloc((MAX + 2) * sizeof(WORD));
	p->tag = 1; //设置低址边界，以防查找左右邻块时出错
	pav = p + 1;
	pav->rlink = pav->a.llink = pav;
	pav->tag = 0;
	pav->size = MAX;
	p = FootLoc(pav);
	p->a.uplink = pav;
	p->tag = 0;
	(p + 1)->tag = 1; //设置高址边界，以防查找左右邻块时出错
}


//分配内存
Space AllocBoundTag(Space &pav, int n)
{ /* 若有不小于n的空闲块,则分配相应的存储块,并返回其首地址;否则返回NULL */
	/* 若分配后可利用空间表不空，则pav指向表中刚分配过的结点的后继结点 */
	Space p, f;
	for (p = pav; p && p->size < n && p->rlink != pav; p = p->rlink)
		;
	if (!p || p->size < n)
		return NULL;
	else
	{
		f = FootLoc(p);
		pav = p->rlink;
		if (p->size - n <= e)
		{
			if (pav == p)
				pav = NULL;
			else
			{
				pav->a.llink = p->a.llink;
				p->a.llink->rlink = pav;
			}
			p->tag = f->tag = 1;
		}
		else
		{
			f->tag = 1;
			p->size -= n;
			f = FootLoc(p);
			f->tag = 0;
			f->a.uplink = p;
			p = f + 1;
			p->tag = 1;
			p->size = n;
		}
		return p;
	}
}
//回收内存
void Reclaim(Space &pav, Space p)
{ //边界标识法的回收算法,s、t分别指向释放块的左、右邻块(空闲时)的首地址
	Space s = (p - 1)->a.uplink, t = p + p->size;
	int l = (p - 1)->tag, r = (p + p->size)->tag; /* l、r分别指示释放块的左、右邻块是否空闲 */
	if (!pav)                                     // 可利用空间表空
	{
		pav = p->a.llink = p->rlink = p;

		p->tag = 0;
		(FootLoc(p))->a.uplink = p;
		(FootLoc(p))->tag = 0;
	}
	else //可利用空间表不空
	{
		if (l == 1 && r == 1) //左右邻区均为占用块
		{
			p->tag = 0;
			(FootLoc(p))->a.uplink = p;
			(FootLoc(p))->tag = 0;
			pav->a.llink->rlink = p;
			p->a.llink = pav->a.llink;
			p->rlink = pav;
			pav->a.llink = p;
			pav = p;
		}
		else if (l == 0 && r == 1) // 左邻区为空闲块,右邻区为占用块,合并左邻块和释放块
		{
			s = (p - 1)->a.uplink;
			s->size += p->size;
			t = FootLoc(p);
			t->a.uplink = s;
			t->tag = 0;
		}
		else if (l == 1 && r == 0) //右邻区为空闲块,左邻区为占用块,合并右邻块和释放块
		{
			p->tag = 0;
			p->a.llink = t->a.llink;
			p->a.llink->rlink = p;
			p->rlink = t->rlink;
			p->rlink->a.llink = p;
			p->size += t->size;
			(FootLoc(t))->a.uplink = p;
			if (pav == t)
				pav = p;
		}
		else //左右邻区均为空闲块
		{
			s->size += p->size + t->size;
			t->a.llink->rlink = t->rlink;
			t->rlink->a.llink = t->a.llink;
			(FootLoc(t))->a.uplink = s;
			if (pav == t)
				pav = s;
		}
	}
	p = NULL; //令刚释放的结点的指针为空
}