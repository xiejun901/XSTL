#ifndef _STL_ALLOC_H_
#define _STL_ALLOC_H_
/*��ͷ�ļ������˿ռ�������*/
#include<stdlib.h>//������malloc��free

#if 0
#include<new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(1)//system("pause")
#endif

namespace XX{
	//��һ��������
	template<int inst>
	class __malloc_alloc_template{
	private:
		static void *oom_malloc(size_t);//��������ڴ�ʱ����out of memory�����
		static void *oom_realloc(void *p, size_t);//�ڵ�ַ�����·����ڴ����out of memoryʱ�����
		static void(*__malloc_alloc_oom_handler)();//�������ʧ�ܵĺ���,����ط��Ǹ�����ָ�룬__malloc_alloc_oom_handlerָ��һ���������ú����������� void()

	public:
		static void *allocate(rsize_t n){
			void *result = malloc(n);//ʹ��mallocֱ�ӷ����ڴ�
			if (0 == result)//����ʧ��
				result = oom_malloc(n);
			return result;
		}
		static void deallocate(void *p, size_t n){
			free(p);//ֱ�ӽ��ڴ�free��
		}
		static void *reallocate(void *p, rsize_t oldSize, rsize_t newSize){
			void *result = realloc(p, newSize);
			if (0 == result)//����ʧ��
				result = oom_realloc(p, newSize);
			return result;
		}

		//����c++��set_new_handler()�������ڴ����ʧ�ܵ����
		/*�����һ������ֵΪ����ָ��ĺ������������β������Ǻ���ָ�룬ʵ����f
		* �β����ͣ�void(),f��һ������Ϊvoid()�ĺ���ָ�룺void(*f)() ���������f
		* ����ֵ���ͣ����ص���һ������ָ�룬void()
		* void({*set_malloc_handler([void(*f())])})()
		*������������
		*    using F=void();
		*    F *set_malloc_handler(F *f)
		*    {
		*    }
		*    using FP=void(*)();
		*    FP set_malloc_handler(FP f)
		*    {
		*    }*/
		static void(*set_malloc_handler(void(*f)()))(){
			void(*old)() = __malloc_alloc_oom_handler;
			__malloc_alloc_oom_handler = f;
			return old;
		}
	};
	//��ʼ��__malloc_alloc_oom_handler������__malloc_alloc_oom_handlerΪһ������ָ���ʼ��Ϊ0
	template<int inst>
	void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

	//oom_malloc��ʵ��
	template<int inst>
	void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
	{
		void(*my_malloc_handler)() = __malloc_alloc_oom_handler;
		void *result;
		for (;;){
			if (0 == my_malloc_handler){
				__THROW_BAD_ALLOC;
			}
			else{
				(*my_malloc_handler)();
				result = malloc(n);
				if (result)
					return result;
			}
		}
	}
	//oom_realloc��ʵ��
	template<int inst>
	void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t newSize)
	{
		void(*my_malloc_handler)() = __malloc_alloc_oom_handler;
		void *result;
		for (;;){
			if (0 == my_malloc_handler){
				__THROW_BAD_ALLOC;
			}
			else{
				(*my_malloc_hander)();
				result = realloc(p, newSize);
				if (result)
					return result;
			}
		}
	}

	using malloc_alloc = __malloc_alloc_template<0>;

	//�ڶ���������
	//��ز���
	//����128�ֽ���ֱ�ӵ��õ�һ�����������ڶ�������������16��free-list������ɷ�����ڴ棬��С�ֱ�Ϊ8,16,24.....127
	//��������Ҫ����10���ֽڴ�С���ڴ�ʱ������ϵͳ���루10+7��&��~7��=16���ֽڵ��ڴ棬��ô�ͻ��freelist[1]������ȡ

	enum{ __ALIGN = 8 };//С�����ϵ��߽磬
	enum{ __MAX_BYTES = 128 };//С���������
	enum{ __NFREELISTS = __MAX_BYTES / __ALIGN };//free-list �ĸ���

	////�����к��澲̬���������ʱ��������֪��Ϊʲô,�ҵ������ԭ���ˣ������������ߵ����Ͷ���ʱ�����������ͱ���ʱ��Ҫ��ʾ��ָ��typename
	//union obj{
	//	union obj* free_list_link;
	//	char client_data[1];
	//};

	//δ���ǹ����̵߳Ķ��� �������Ȱ�������Űɡ�����һ����Ҫ������
	template<bool threads, int inst>
	class __default_alloc_template{
	private:
		//��Ҫ������ڴ����Ϊ8�ı���������20�����Ϊ24;
		static size_t round_up(size_t nbytes){
			return (nbytes + __ALIGN - 1) & ~(__ALIGN - 1);
		}
		/*����ط���һ�����ɣ�union������ռ�ռ�ֻռ���Ա�����Ǹ���ô�󣬱����������ռ�ռ���1���ֽڣ������Ͳ���ķѶ���Ŀռ��ˣ�
		*���ڴ�����У�����ڴ�û�����ȥ����һ���ֽھ������������ã�����ָ����һ�����ŵĿռ䣬���ӵ�һ�ֶο���ȥ�����obj��һ��obj*��ָ�룬
		*��������ȥ�ˣ���Ȼ�������Ͳ���Ҫ�ˣ���ô���ָ��͵���ַ�ã����ӵڶ��ֶο���ȥ�ã���һ��char*��ָ�롣*/
		union obj{
			union obj* free_list_link;
			char client_data[1];
		};
		//���������������ҹ��������volatile�ǲ�����Ϊ����Ƕ��̵߳Ļ��������߳��п��ܸı�����������Ĵ�С������Ҫ������޶���
		static obj * volatile free_list[__NFREELISTS];
		//���ж���Ҫ������ڴ洦��freeList���ĸ�Ԫ���У�����Ҫ����10���ֽڵĿռ䣬��ôӦ�ô�freeList[1]��ȡ
		static size_t free_list_index(size_t nbytes){
			return (nbytes - 1) / __ALIGN;
		}
		//��freeList��û�пɷ���Ŀռ�ʱ�����ڴ����ȡ�ÿռ����freeList�У�������һ����СΪn������
		static void *refill(size_t n);
		//����һ��鹲nobjs������СΪsize�Ŀռ�
		static char *chunk_alloc(size_t size, int &nobjs);

		static char *start_free;
		static char *end_free;
		static size_t heap_size;

	public:
		using ptr_obj = obj *;
		static void *allocate(size_t n);
		static void deallocate(void *p, size_t n);
		static void *reallocate(void *p, size_t old_size, size_t new_size);
	};

	//��̬�����Ķ���
	template<bool threads, int inst>
	char * __default_alloc_template<threads, inst>::start_free = 0;

	template<bool threads, int inst>
	char * __default_alloc_template<threads, inst>::end_free = 0;

	template<bool threads, int inst>
	size_t __default_alloc_template<threads, inst>::heap_size = 0;
	//ע��������typename���÷�
	template<bool threads, int inst>
	typename __default_alloc_template<threads, inst>::ptr_obj volatile __default_alloc_template<threads, inst>::free_list[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//allocateʵ��
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::allocate(size_t n){
		obj * volatile *my_free_list;
		obj * result;
		if (n > __MAX_BYTES){//���õ�һ��������
			return malloc_alloc::allocate(n);
		}
		//�ҵ���С���ʵ�һ��free_list
		my_free_list = free_list + free_list_index(n);
		result = *my_free_list;
		//�����ǰfree_list��û���ˣ���Ҫ����������free_list
		if (result == 0){
			//��䲢����һ����СΪround��n��������
			void *r = refill(round_up(n));
			return r;
		}
		//�õ�ǰ���ָ����һ��
		*my_free_list = result->free_list_link;
		return result;
	}
	//deallocateʵ��
	template<bool threads, int inst>
	void __default_alloc_template<threads, inst>::deallocate(void *p, size_t n){
		obj *q = (obj*)p;
		obj * volatile *my_free_list;
		if (n > __MAX_BYTES){
			malloc_alloc::deallocate(p, n);
			return;
		}
		my_free_list = free_list + free_list_index(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;

	}
	//reallocateʵ��,û�н�ԭ���ڴ���Ķ�������������ֻ�����·����˺��ʴ�С���ڴ�
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::reallocate(void *p, size_t old_size, size_t new_size)
	{
		deallocate(p, old_size);
		p = allocate(nes_size);
	}
	//refillʵ�֣����ڴ����ȡ���ڴ����ӵ�free_list�Ķ�Ӧλ���ϱ�ȥ
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::refill(size_t n){
		int nobjs = 20;
		//���ڴ����ȡ���ڴ�
		char *chunk = chunk_alloc(n, nobjs);
		obj* volatile *my_free_list;
		obj *result;
		obj *current_obj, *next_obj;
		if (nobjs == 1)
			return chunk;
		result = (obj *)chunk;
		my_free_list = free_list + free_list_index(n);//�ҵ�Ҫ�����λ��
		*my_free_list = current_obj = (obj*)(chunk + n);//�Ž�ȥ
		for (int i = 1; i < nobjs - 1; i++){
			next_obj = (obj*)((char*)current_obj + n);
			current_obj->free_list_link = next_obj;
			current_obj = next_obj;
		}
		current_obj->free_list_link = 0;
		return result;
	}

	//chunk_allocʵ�֣����ڴ��ȥ��nobjs����СΪn�Ŀռ䣻����ڴ�ز����˾������ڴ��
	template<bool threads, int inst>
	char *__default_alloc_template<threads, inst>::chunk_alloc(size_t n, int &nobjs){
		char *result;
		size_t total_bytes = n*nobjs;
		size_t left_bytes = end_free - start_free;
		//���֣��ܺã��ֳ�ȥ
		if (left_bytes >= total_bytes){
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//�����֣����ǹ���һ���֣��Ǿͷ�һ���ְɣ�left/n����ô���
		else if (left_bytes >= n){
			nobjs = left_bytes / n;
			total_bytes = n*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//һ����������
		else{
			size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);//����4λ��ԭ��Ӧ����Ϊ����ÿ�����ӵ���������̫��
			//���left_bytes���У���ô��ʣ�µ���һ����������ʵ�free_list�У�ʣ����һ����8�ı�������Ϊÿһ�η��䣬����ȡ������8�ı���
			if (left_bytes > 0){
				obj * volatile *my_free_list = free_list + free_list_index(left_bytes);
				((obj *)start_free)->free_list_link = *my_free_list;
				*my_free_list = ((obj *)start_free);
			}
			start_free = (char *)malloc(bytes_to_get);
			if (0 == start_free){
				//���û���䵽,û�ֵ��Ļ��ʹ����ڵ�free_list����۰ɡ�������ʣ�µ��ù������ϣ��о��ý�Լ,�ӱȵ�ǰ������������
				int i;
				obj * volatile *my_free_list, *p;
				for (i = n; i <= __MAX_BYTES; i += __ALIGN){
					my_free_list = free_list + free_list_index(i);
					p = *my_free_list;
					if (0 != p){
						*my_free_list = p->free_list_link;
						start_free = (char *)p;
						end_free = start_free + i;
						return(chunk_alloc(n, nobjs));
					}
				}
				//���ȷʵû�ֵ�
				end_free = 0;
				start_free = (char *)malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return(chunk_alloc(n, nobjs));
		}
	}

	//�����ռ�����������
#ifdef __USE_MALLOC
	//typedef __malloc_alloc_template<0> malloc_alloc;
	typedef malloc_alloc alloc;
#else
	using  alloc = __default_alloc_template<false, 0>;
#endif

	//��װһ������stl�ӿڵ��࿴����Ϊһ��������������������ڴ涼�ǰ��ֽ�Ϊ��λ��(void *)���͵�
	template<typename T, typename Alloc = alloc>
	class simple_alloc{
	public:
		//����n��T���ڴ�
		static T *allocate(size_t n){
			return 0 == n ? 0 : (T*)Alloc::allocate(n*sizeof(T));
		}
		//����һ��T���ڴ�
		static T *allocate(void){
			return (T*)Alloc::allocate(sizeof(T));
		}
		//�黹�ڴ�
		static void deallocate(T *p, size_t n){
			if (0 != n)
				Alloc::deallocate(p, n*sizeof(T));
		}
		static void deallocate(T *p){
			Alloc::deallocate(p, sizeof(T));
		}
	};
}

#endif