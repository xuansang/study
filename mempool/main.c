#include "mempool.h"
#include <stdlib.h>
#include <time.h> 


#ifdef MEM_POOL 
#define MALLOC(size) pool_malloc(&st_pool_mgr, size)
#define FREE(ptr)    pool_free(&st_pool_mgr,ptr)
#else
#define MALLOC(size) malloc(size)
#define FREE(ptr)	free(ptr)
#endif


int main()
{	
	pool_mgr st_pool_mgr;

	if (!init_pool_mgr(&st_pool_mgr))
	{
		printf("init_pool_mgr error");
	}
	printf("----------\r\n");
	void *ptr_arr_32[128];
	//void *ptr_arr_special[1000];
	
	int size = 30;
	for (int j = 0; j < 1000000; j++)
	{	
		size = 31;
		for (int i = 0; i < 128; i++)
		{
			size += 1;
			ptr_arr_32[i] = MALLOC(size);
		}

		for (int i = 0; i < 128; i++)
		{
			FREE(ptr_arr_32[i]);
		}
	}
	
	//destroy_mgr(&st_pool_mgr);
	
	return 0;
}