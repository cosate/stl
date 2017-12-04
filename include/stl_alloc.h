#ifndef GRTW_STL_ALLOC_H
#define GRTW_STL_ALLOC_H

#include<cstdlib>
#include<new>

namespace grtw
{
	using oomh = void();
	
	class malloc_alloc
	{
	private:
		static void* oom_malloc(size_t n)
		{
			oomh* my_malloc_alloc_handler;
			void* res;

			while(1)
			{
				my_malloc_handler = malloc_alloc_oom_handler;
				if(0 == my_malloc_handler)
				{
					throw std::bad_alloc();
				}
				(*my_malloc_handler)();
				res = malloc(n);
				if(res)
					return res;
			}
		}
		static void* oom_realloc(void* p, size_t n)
		{
			oomh* my_malloc_handler;
			void* res;
			while(1)
			{
				my_malloc_handler = malloc_alloc_oom_handler;
				if(0 == my_malloc_handler)
				{
					throw std::bad_alloc();
				}
				(*my_malloc_handler)();
				res = realloc(p, n);
				if(res)
					return res;
			}
		}

		static oomh* malloc_alloc_oom_handler;

	public:
		static void* allocate(size_t n)
		{
			void* res = malloc(n);
			if(0 == res)
				res = oom_malloc(n);
			return res;
		}

		static void deallocate(void* p, size_t)
		{
			free(p);
		}

		static void* reallocate(void* p, size_t, size_t new_size)
		{
			void* res = realloc(p, new_size);
			if(0 == res)
				res = oom_realloc(p, new_size);
			return res;
		}

		static oomh* set_malloc_handler(oomh* p)
		{
			oomh* old = malloc_alloc_oom_handler;
			malloc_alloc_oom_handler = p;
			return old;
		}
	};

	oomh* malloc_alloc::malloc_alloc_oom_handler = 0;


	#define ALIGN 8
	#define MAX_BYTES 128
	#define NFREELISTS 16

	class default_alloc
	{
	private:
		union obj
		{
			union obj* next;
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