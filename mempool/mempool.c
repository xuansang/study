#include "mempool.h"

//根据申请的内存大小选取 unit_pool ,返回NULL时则无可用 unit_pool
static inline unit_pool* _get_uint_pool(pool_mgr* p_st_pool_mgr,unsigned int mem_size);

//从指定单元内存池中获取空间,没有就扩展，有则获取
static inline void* _get_mem_from_pool(unit_pool *p_ut_pool);

//单元池中内存使用完 扩充
static inline int  _expand_unit_pool(unit_pool *p_ut_pool,int mem_cnt);

//从指定单元内存池中获取空间，前提 存在可用空间
static inline void *_get_unit_mem(unit_pool *p_ut_pool);

static inline void* _special_get_mem(unit_pool *p_ut_pool,unsigned int nsize);

static inline  void  unit_pool_free(void *object,void *p_data)
{
    dnode *p_dnode = NULL;
    unit_pool *p_ut_pool = (unit_pool *)object;
    p_dnode = DNODE_PTR(p_data);
    dlist_add(&(p_ut_pool->dl_can_use),p_dnode);
	p_ut_pool->n_mem_total_cnt += 1;
}

static void * unit_pool_malloc(void* object, unsigned int size )
{
    unit_pool *p_ut_pool = (unit_pool *)object;
    return _get_mem_from_pool(p_ut_pool) ;
}

static void special_free(void *object , void *p_data)
{
    dnode *p_dnode = NULL;
    unit_pool *p_ut_pool = (unit_pool *)object;
    p_dnode = DNODE_PTR(p_data);
    dlist_delete(&(p_ut_pool->dl_can_use),p_dnode);
    free(p_dnode);
}



static void* specal_malloc(void *object , unsigned int size)
{
    unsigned char *p_mem_ptr = NULL;
    dnode *p_dnode = NULL;
    unit_pool *p_ut_pool = (unit_pool *)object;
    p_mem_ptr = malloc( size + sizeof(dnode) + sizeof(unsigned short));
	if (NULL == p_mem_ptr)
	{
		return NULL;
	}
	memcpy(p_mem_ptr + sizeof(dnode), &(p_ut_pool->unit_type), sizeof(unsigned short));
    
    p_dnode = (dnode *)p_mem_ptr;
    p_dnode->p_data = p_mem_ptr+sizeof(dnode)+sizeof(unsigned short);
    dlist_add(&(p_ut_pool->dl_special),p_dnode);
    return  p_dnode->p_data;
}
//static int  _init_unit_pool(unit_pool *p_ut_pool,uint_param *p_unit_param);


static int _init_unit_pool(unit_pool *p_ut_pool,unsigned short  unit_type)
{
    p_ut_pool->unit_type = unit_type; 
    p_ut_pool->n_mem_size = (unit_type+1) *32;
	p_ut_pool->st_ut_param.c_gc_rate = 60;
	p_ut_pool->st_ut_param.c_pre_malloc = 1;
	p_ut_pool->st_ut_param.n_pre_size = 500;
	p_ut_pool->st_ut_param.n_step = 500;
    p_ut_pool->pool_free = unit_pool_free;
    p_ut_pool->pool_malloc = unit_pool_malloc;
    if(!p_ut_pool->st_ut_param.n_pre_size )
    {
        return 1;
    }
    
    //预分配空间失败
    if(!_expand_unit_pool(p_ut_pool,p_ut_pool->st_ut_param.n_pre_size))
    {
        return 0;
    }
    
    return 1;
}

//初始化
int init_pool_mgr(pool_mgr* p_st_pool_mgr)
{
    memset(p_st_pool_mgr,0,sizeof(pool_mgr));
	p_st_pool_mgr->ut_pool_arr = malloc(sizeof(unit_pool)* UNIT_POOL_TOTAL_CNT );
	if (NULL == p_st_pool_mgr->ut_pool_arr)
	{
		return 0;
	}
	memset(p_st_pool_mgr->ut_pool_arr, 0, sizeof(unit_pool)* UNIT_POOL_TOTAL_CNT);

    for(int i = 0; i < MAX_POOL_TYPE;i++)
    {
        if(!_init_unit_pool(p_st_pool_mgr->ut_pool_arr + i,i))
        {
            return 0 ;
        }    
    }
    p_st_pool_mgr->ut_pool_arr[SPECIAL_POOL_TYPE].pool_free = special_free;
    p_st_pool_mgr->ut_pool_arr[SPECIAL_POOL_TYPE].pool_malloc = specal_malloc ;
	p_st_pool_mgr->ut_pool_arr[SPECIAL_POOL_TYPE].unit_type = SPECIAL_POOL_TYPE;
	return 1;
}

//从内存池申请指定大小的内存
void *pool_malloc(pool_mgr* p_st_pool_mgr,unsigned int nsize)
{
    unit_pool* p_cur_unit = _get_uint_pool( p_st_pool_mgr,nsize);
    if(NULL  == p_cur_unit)
    {
        //此处不会进入
        return NULL;
    }
    return p_cur_unit->pool_malloc(p_cur_unit,nsize);
}

//释放从内存池申请的内存
void pool_free(pool_mgr* p_st_pool_mgr,void *p_data)
{
    unsigned short unit_type = UNIT_POOL_TYPE(p_data);
    unit_pool *p_ut_pool = p_st_pool_mgr->ut_pool_arr + unit_type;
    p_ut_pool->pool_free(p_ut_pool,p_data);
}


void destroy_mgr(pool_mgr* p_st_pool_mgr)
{
	//默认从内存池申请的内存已被用户释放至内存池中
	//销毁内存池中申请的内存
	void *ptr = NULL;
	for (int i = 0; i < MAX_POOL_TYPE; i++)
	{
		while (p_st_pool_mgr->ut_pool_arr[i].dl_can_use.p_dhead != NULL)
		{
			ptr = p_st_pool_mgr->ut_pool_arr[i].dl_can_use.p_dhead;
			dlist_delete(&(p_st_pool_mgr->ut_pool_arr[i].dl_can_use),
				p_st_pool_mgr->ut_pool_arr[i].dl_can_use.p_dhead);
			free(ptr);
			
		}
		
	}
}

//释放未使用的内存单元
void gc_pool(pool_mgr* p_st_pool_mgr)
{
    
}

//根据申请的内存大小选取 unit_pool ,返回NULL时则无可用 unit_pool
static inline unit_pool* _get_uint_pool(pool_mgr* p_st_pool_mgr,unsigned int mem_size)
{
    for(int i = 0; i < MAX_POOL_TYPE ;i++)
    {
        if(mem_size <= p_st_pool_mgr->ut_pool_arr[i].n_mem_size)
        {
            return p_st_pool_mgr->ut_pool_arr + i;
        }
    }
    return p_st_pool_mgr->ut_pool_arr + (SPECIAL_POOL_TYPE) ;
}

static int _expand_unit_pool(unit_pool *p_ut_pool,int mem_cnt)
{
    unsigned char *p_expend_data = NULL;
    dnode *p_dnode = NULL;
    unsigned int node_len = p_ut_pool->n_mem_size + sizeof(dnode) + sizeof(unsigned short);
    p_expend_data = (unsigned char *)malloc(node_len*mem_cnt);
    if (NULL == p_expend_data)
    {
        return  0;
    }
    memset(p_expend_data,0,(p_ut_pool->n_mem_size + sizeof(dnode) + sizeof(unsigned short)*mem_cnt));
    for(int i = 0; i < mem_cnt ;i++)
    {	
        
        p_dnode = (dnode*)(p_expend_data+ (node_len*i)) ;
		//printf("p_dnode :%p\r\n", p_dnode);
        p_dnode->p_data = p_expend_data+ (node_len*i) +sizeof(dnode) + sizeof(unsigned short);
	
        dlist_add(&(p_ut_pool->dl_can_use),p_dnode);
    }
    p_ut_pool->n_mem_total_cnt +=  mem_cnt;
    return 1;
} 

static void *_get_unit_mem(unit_pool *p_ut_pool)
{
    void *p_data = NULL;
	if (NULL == p_ut_pool->dl_can_use.p_dhead)
	{
		printf("ERROR %s %d", __FUNCTION__, __LINE__);
		return NULL;
	}

    p_data = p_ut_pool->dl_can_use.p_dhead->p_data;
    dlist_delete(&(p_ut_pool->dl_can_use),p_ut_pool->dl_can_use.p_dhead);
	p_ut_pool->n_mem_total_cnt -= 1;
    return p_data; 
}

static void* _get_mem_from_pool(unit_pool *p_ut_pool)
{
    if(!dlist_is_empty(&(p_ut_pool->dl_can_use)))
    {
        return _get_unit_mem(p_ut_pool);    
    }
    
    if(!_expand_unit_pool(p_ut_pool,p_ut_pool->st_ut_param.n_step))
    {
        return NULL;
    }
    
    return _get_unit_mem(p_ut_pool);

}

static void* _special_get_mem(unit_pool *p_ut_pool,unsigned int nsize)
{
    unsigned char *p_mem_ptr = NULL;
    dnode *p_dnode = NULL;
    p_mem_ptr = (unsigned char *)malloc( nsize + sizeof(dnode)+ sizeof(unsigned short));
    if(NULL == p_mem_ptr)
    {
        return NULL;
    }
	memcpy(p_mem_ptr + sizeof(dnode), &(p_ut_pool->unit_type), sizeof(unsigned short));
    p_dnode = (dnode *)p_mem_ptr;
    p_dnode->p_data = p_mem_ptr+sizeof(dnode);
    dlist_add(&(p_ut_pool->dl_special),p_dnode);
    return  p_dnode->p_data;
}