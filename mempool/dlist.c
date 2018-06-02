#include "dlist.h"
#include <stdio.h>
#include <stdlib.h>
int init_dlist(dlist** pp_dlist)
{
    *pp_dlist = (dlist*)malloc(sizeof(dlist));
    if(NULL == *pp_dlist )
    {
        return 0;
    }                
    (*pp_dlist)->p_dhead = NULL;                                               
    (*pp_dlist)->elem_cnt = 0;
    return 1;                                                                                                              
}

void dlist_add(dlist* p_dlist,dnode *p_dnode)
{
    if(NULL == p_dlist->p_dhead)                                                 
    {      
		p_dlist->p_dhead = p_dnode;
        p_dlist->p_dhead->p_next = NULL;                                       
        p_dlist->p_dhead->p_prev = NULL;                                       
    }                                                                          
    else                                                                       
    {                                                                          
        p_dnode->p_prev = NULL;                                            
        p_dnode->p_next = p_dlist->p_dhead ;                               
        p_dlist->p_dhead->p_prev = p_dnode ;                               
        p_dlist->p_dhead = p_dnode;                                                                             
    }                                                                          
    p_dlist->elem_cnt += 1;
     
}

// void dlist_add_arr(dlist* p_dlist,dnode *p_dnode_arr,int node_cnt)
// {
//     dnode *p_org_node_h = p_dlist->dhead;
//     dnode *p_node_tail = NULL;      //新加入的尾部节点 
//     p_dlist->dhead = p_dnode_arr;
//     p_dnode_arr[0].p_prev = NULL;
//     p_dnode_arr[0].p_next = p_dnode_arr + 1;
//     p_dnode_arr[node_cnt-1].p_prev = p_dnode_arr + (node_cnt-2) ;

//     if(NULL == p_org_node_h)
//     {
//         p_dnode_arr[node_cnt-1].p_next = NULL;
//     }
//     else
//     {
//         p_org_node_h->p_prev = p_dnode_arr + (node_cnt-1);
//         p_dnode_arr[node_cnt-1].p_next = p_org_node_h; 
//     }

//     for(int index = 1;index < node_cnt;index++)
//     {
//         p_dnode_arr[index].p_prev = p_dnode_arr[index-1];
//         p_dnode_arr[index].p_next = p_dnode_arr[index+1];
//     }      
// }

void dlist_delete(dlist* p_dlist, dnode *p_dnode)
{                         
    /* 头节点 */                                                               
    if(p_dnode == p_dlist->p_dhead)                                             
    {                                                                          
        /* 只有一个节点 */                                                      
        if(p_dlist->elem_cnt == 1)                    
        {                                                                                                                           
            p_dlist->p_dhead = NULL;
        }                                                                      
        else                                                                   
        {                                                                      
            p_dlist->p_dhead = p_dnode->p_next;                                  
            p_dnode->p_next->p_prev = NULL;                                      
        }                                                                      
    }                                                                          
    else                                                                       
    {                
		if (p_dnode->p_prev)
		{
			p_dnode->p_prev->p_next = p_dnode->p_next;
		}
        
		if (p_dnode->p_next)
		{
			p_dnode->p_next->p_prev = p_dnode->p_prev;
		}
                                     
    }
    p_dlist->elem_cnt -= 1;                                        
}

int dlist_is_empty(dlist *p_dlist)
{
    return p_dlist->p_dhead == NULL ? 1:0;
}