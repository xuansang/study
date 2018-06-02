#ifndef __SUNSET_DLIST_H__
#define __SUNSET_DLIST_H__


//双向链表 插入时从链表头插入
typedef struct tag_DNODE
{
	struct tag_DNODE *p_next;
	struct tag_DNODE *p_prev;
	void  *p_data;
}dnode;

typedef struct tag_dlist
{
	dnode *p_dhead;                 //    链表头               
	unsigned int elem_cnt;          //    链表大小
}dlist;


//初始化 双向链表
int init_dlist(dlist** pp_dlist);

//添加至双向链表 （从头插入）
void dlist_add(dlist* p_dlist, dnode *p_dnode);

//删除节点
void dlist_delete(dlist* p_dlist, dnode *p_dnode);

//链表是否为空
int dlist_is_empty(dlist *p_dlist);

#endif