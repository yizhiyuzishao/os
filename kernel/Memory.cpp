#include "Memory.h"
//��ʼ���ڴ�
void initMemory(Space &pav)
{
	Space p;
	p = (WORD *)malloc((MAX + 2) * sizeof(WORD));
	p->tag = 1; //���õ�ַ�߽磬�Է����������ڿ�ʱ����
	pav = p + 1;
	pav->rlink = pav->a.llink = pav;
	pav->tag = 0;
	pav->size = MAX;
	p = FootLoc(pav);
	p->a.uplink = pav;
	p->tag = 0;
	(p + 1)->tag = 1; //���ø�ַ�߽磬�Է����������ڿ�ʱ����
}


//�����ڴ�
Space AllocBoundTag(Space &pav, int n)
{ /* ���в�С��n�Ŀ��п�,�������Ӧ�Ĵ洢��,���������׵�ַ;���򷵻�NULL */
	/* �����������ÿռ���գ���pavָ����иշ�����Ľ��ĺ�̽�� */
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
//�����ڴ�
void Reclaim(Space &pav, Space p)
{ //�߽��ʶ���Ļ����㷨,s��t�ֱ�ָ���ͷſ�������ڿ�(����ʱ)���׵�ַ
	Space s = (p - 1)->a.uplink, t = p + p->size;
	int l = (p - 1)->tag, r = (p + p->size)->tag; /* l��r�ֱ�ָʾ�ͷſ�������ڿ��Ƿ���� */
	if (!pav)                                     // �����ÿռ���
	{
		pav = p->a.llink = p->rlink = p;

		p->tag = 0;
		(FootLoc(p))->a.uplink = p;
		(FootLoc(p))->tag = 0;
	}
	else //�����ÿռ����
	{
		if (l == 1 && r == 1) //����������Ϊռ�ÿ�
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
		else if (l == 0 && r == 1) // ������Ϊ���п�,������Ϊռ�ÿ�,�ϲ����ڿ���ͷſ�
		{
			s = (p - 1)->a.uplink;
			s->size += p->size;
			t = FootLoc(p);
			t->a.uplink = s;
			t->tag = 0;
		}
		else if (l == 1 && r == 0) //������Ϊ���п�,������Ϊռ�ÿ�,�ϲ����ڿ���ͷſ�
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
		else //����������Ϊ���п�
		{
			s->size += p->size + t->size;
			t->a.llink->rlink = t->rlink;
			t->rlink->a.llink = t->a.llink;
			(FootLoc(t))->a.uplink = s;
			if (pav == t)
				pav = s;
		}
	}
	p = NULL; //����ͷŵĽ���ָ��Ϊ��
}