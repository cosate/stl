#ifndef GRTW_STL_ALLOC_H
#define GRTW_STL_ALLOC_H

#include<cstdlib>
#include<new>

namespace grtw
{
	using oomh = void();
	
	class malloc_alloc
	{
	public:
		static void* allocate(size_t);
		static void deallocate(void*, size_t);
		static void* reallocate(void*, size_t, size_t);

		static oomh* set_malloc_handler(oomh*);

	private:
		static void* oom_malloc(size_t n);
		static void* oom_realloc(void* p, size_t n);

		static oomh* malloc_alloc_oom_handler;
	};

	oomh* malloc_alloc::malloc_alloc_oom_handler = 0;

	void* malloc_alloc::allocate(size_t n)
	{
		void* res = malloc(n);
		if(0 == res)
			res = oom_malloc(n);
		return res;
	}

	void malloc_alloc::deallocate(void* p, size_t)
	{
		free(p);
	}

	void* malloc_alloc::reallocate(void* p, size_t, size_t new_size)
	{
		void* res = realloc(p, new_size);
		if(0 == res)
			res = oom_realloc(p, new_size);
		return res;
	}

	oomh* malloc_alloc::set_malloc_handler(oomh* p)
	{
		oomh* old = malloc_alloc_oom_handler;
		malloc_alloc_oom_handler = p;
		return old;
	}

	void* malloc_alloc::oom_malloc(size_t n)
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
	void* malloc_alloc::oom_realloc(void* p, size_t n)
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

	#define ALIGN 8
	#define MAX_BYTES 128
	#define NFREELISTS 16

	class default_alloc
	{
	public:
		static void* allocate(size_t);
		static void deallocate(void*, size_t);
		static void* reallocate(void*, size_t, size_t);

	private:
		static size_t round_up(size_t);
		static size_t free_list_index(size_t);
		static void* refill(size_t);
		static char* chunk_alloc(size_t, int&);

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
	};

	char* default_alloc::start_free = 0;
	char* default_alloc::end_free = 0;
	size_t heap_size = 0;
	default_alloc::obj* default_alloc::free_lists[NFREELISTS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

	size_t default_alloc::round_up(size_t bytes)
	{
		return (bytes + ALIGN - 1) &~(ALIGN - 1);
	}

	size_t default_alloc::free_list_index(size_t bytes)
	{
		return ((bytes + ALIGN - 1)/ALIGN - 1);
	}

	void* default_alloc::allocate(size_t n)
	{
		if(n > MAX_BYTES)
		{
			return malloc_alloc::allocate(n);
		}

		int index = free_list_index(n);
		obj* res = free_lists[index];
		if(res)
		{
			free_lists[index] = res->next;
			return res;
		}
		else
		{
			void* r = refill(round_up(n));
			return r;
		}
	}

	void default_alloc::deallocate(void* p, size_t n)
	{
		if(n > MAX_BYTES)
		{
			free(p);
			return;
		}
		else
		{
			int index = free_list_index(n);
			obj* ptr = static_cast<obj*>p;
			ptr->next = free_lists[index];
			free_lists[index] = q;
		}
	}

	void* default_alloc::reallocate(void* p, size_t old_size, size_t new_size)
	{
		deallocate(p, old_size);
		p = allocate(new_size);
		return p;
	}

	void* default_alloc::refill(size_t n)
	{
		int numofobjs = 20;
		char* res = chunk_alloc(n, numofobjs);
		if(numofobjs == 1)
			return res;


	}

	char* default_alloc::chunk_alloc(size_t bytes, int& n)
	{
		char* res;
		size_t bytes_required = n * bytes;
		size_t bytes_left = end_free - start_free;

		if(bytes_left >= bytes_required)
		{
			res = start_free;
			start_free += bytes_required;
			return res;
		}
		else if(bytes_left >= bytes)
		{
			n = (int)(bytes_left / bytes);
			bytes_required = n * bytes;
			res = start_free;
			start_free += bytes_required;
			return res;
		}
		else
		{
			size_t byte_to_get = 2 * bytes_required + round_up(heap_size >> 4);
			if(bytes_left > 0)
			{

			}

			start_free = (char*)malloc(byte_to_get);
			if(start_free == 0)
			{

			}

			heap_size += byte_to_get;
			end_free = start_free + byte_to_get;
			return chunk_alloc(bytes, n);
		}
	}
}

#endif