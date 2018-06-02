#ifndef __SUN_MEMPOOL_H__
#define __SUN_MEMPOOL_H__
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "dlist.h"
//提供预分配或者用时分配方式，分配最小64BYTE空间、并以此为基准依次*2的空间
//若申请空间超过最大可申请内存大小则 使用malloc 
#define UNIT_BASE_SIZE (32)
#define MAX_POOL_TYPE 16 //单元池最大类型数 依次为 UNIT_BASE_SIZE *1 UNIT_BASE_SIZE *2 ...UNIT_BASE_SIZE *MAX_POOL_TYPE


#define SPECIAL_POOL_TYPE MAX_POOL_TYPE

#define UNIT_POOL_TOTAL_CNT  (MAX_POOL_TYPE+1) 


typedef struct tag_UINT_PARAM
{
    unsigned char c_pre_malloc;     //0 不进行预分配 1 预分配
    unsigned int n_pre_size;        //预分配大小
    unsigned int n_step;            //超出后 增加的步长
    unsigned char c_gc_rate;        //未使用空间比例超过该值进行回收 1-99 
}uint_param;

typedef void (*f_pool_free)(void* p_st_pool_mgr,void *p_data);

typedef void* (*f_pool_malloc)(void* p_pool_unit,unsigned int size);
typedef struct tag_UNIT_POOL
{
    union
    {
        struct
        {
            dlist dl_can_use ;               //可使用空间链表
            unsigned short n_mem_size;          //内存单元空间 
            uint_param st_ut_param;             //参数
            unsigned int n_mem_total_cnt;       //分配的总空间
        };
        struct
        {
            dlist dl_special;            
        };
    };
    unsigned short  unit_type;           //单元池类型
    f_pool_free pool_free;              //释放内存时的指针
    f_pool_malloc pool_malloc;
}unit_pool;


//内存池管理定义
typedef struct tag_POOL_MGR
{
    unsigned char b_analy;                                  //1 启用分析 0 不启用 
    unit_pool *ut_pool_arr;                  //单元池 
}pool_mgr;



#define DNODE_PTR(ptr) ((dnode*)(((unsigned char*)ptr)-sizeof(dnode)-sizeof(unsigned short)))
 
#define UNIT_POOL_TYPE(ptr) (((unsigned short*)((((unsigned char* ) ptr)-sizeof(unsigned short)))))[0]

#define ENABLE_ANALY(p_pool_mgr)    (p_pool_mgr->b_analy = 1)  


//初始化
int init_pool_mgr(pool_mgr* p_st_pool_mgr);

//从内存池申请指定大小的内存
void *pool_malloc(pool_mgr* p_st_pool_mgr,unsigned int nsize);

//释放从内存池申请的内存
void pool_free(pool_mgr* p_st_pool_mgr,void *p_data);

//销毁内存池 在程序 最后执行
void destroy_mgr(pool_mgr* p_st_pool_mgr);

//释放未使用的内存单元
void gc_pool(pool_mgr* p_st_pool_mgr);

#define sun_malloc(st_poolmgr,size)                                            \
do                                                                             \
{                                                                              \
    if(pool_mgr->bAnaly == 1)                                                  \
    {                                                                          \
        return pool_malloc(pool_mgr,size);                                     \
    }                                                                          \
    else                                                                       \
    {                                                                          \
        return pool_malloc(pool_mgr,size);                                     \
    }                                                                          \
}while(0);

#define sun_free(pool_mgr,addr)                                                \
    do {                                                                       \
        if(pool_mgr->bAnaly == 1)                                              \
        {                                                                      \
            pool_free(pool_mgr,addr);                                          \
        }                                                                      \
        else                                                                   \
        {                                                                      \
            pool_free(pool_mgr,addr);                                          \
        }                                                                      \
    }while(0)



#endif