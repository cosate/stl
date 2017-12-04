#ifndef GRTW_STL_ALLOC_H
#define GRTW_STL_ALLOC_H

#include<cstdlib>

namespace grtw
{
	using oomh = void();
	
	class malloc_alloc
	{
	private:
		static void oom_malloc(size_t);
		static void oom_realloc(void*, size_t);

		static oomh* malloc_alloc_oom_handler;

	public:
		static void* allocate(size_t n);
		static void deallocate(void*, size_t);
		static void* reallocate(void* p, size_t, size_t);
		static oomh* set_malloc_handler(oomh*);
	};


	#define ALIGN 8
	#define MAX_BYTES 128
	#define NFREELISTS 16

	class default_alloc
	{
	private:
		union obj
		{
			union obj* free_list_link;
			char client_data[1];
		};
		static obj* free_lists[NFREELISTS];

		static char* start_free;
		static char* end_free;
		static size_t heap_size;

	private:
		static size_t round_up(size_t);
		static size_t free_list_index(size_t);
		static void* refill(size_t);
		static char* chunk_alloc(size_t, int&);

	public:
		static void* allocate(size_t);
		static void deallocate(void*, size_t);
		static void* reallocate(void*, size_t, size_t);
	};
}

#endif