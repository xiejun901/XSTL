#ifndef _STL_ALLOC_H_
#define _STL_ALLOC_H_
/*此头文件定义了空间配置器*/
#include<stdlib.h>//定义了malloc，free

#if 0
#include<new>
#define __THROW_BAD_ALLOC throw bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(1)//system("pause")
#endif

namespace XX{
	//第一级配置器
	template<int inst>
	class __malloc_alloc_template{
	private:
		static void *oom_malloc(size_t);//处理分配内存时出现out of memory的情况
		static void *oom_realloc(void *p, size_t);//在地址上重新分配内存出现out of memory时的情况
		static void(*__malloc_alloc_oom_handler)();//处理分配失败的函数,这个地方是个函数指针，__malloc_alloc_oom_handler指向一个函数，该函数的类型是 void()

	public:
		static void *allocate(rsize_t n){
			void *result = malloc(n);//使用malloc直接分配内存
			if (0 == result)//分配失败
				result = oom_malloc(n);
			return result;
		}
		static void deallocate(void *p, size_t n){
			free(p);//直接将内存free掉
		}
		static void *reallocate(void *p, rsize_t oldSize, rsize_t newSize){
			void *result = realloc(p, newSize);
			if (0 == result)//分配失败
				result = oom_realloc(p, newSize);
			return result;
		}

		//仿照c++的set_new_handler()来处理内存分配失败的情况
		/*这儿是一个返回值为函数指针的函数，函数的形参类型是函数指针，实参是f
		* 形参类型：void(),f是一个类型为void()的函数指针：void(*f)() 这儿定义了f
		* 返回值类型：返回的是一个函数指针，void()
		* void({*set_malloc_handler([void(*f())])})()
		*可以这样做：
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
	//初始化__malloc_alloc_oom_handler，定义__malloc_alloc_oom_handler为一个函数指针初始化为0
	template<int inst>
	void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

	//oom_malloc的实现
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
	//oom_realloc的实现
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

	//第二级配置器
	//相关参数
	//超过128字节则直接调用第一级配置器，第二级配置器用了16个free-list来管理可分配的内存，大小分别为8,16,24.....127
	//当我们需要分配10个字节大小的内存时，会向系统申请（10+7）&（~7）=16个字节的内存，那么就会从freelist[1]当中来取

	enum{ __ALIGN = 8 };//小区块上调边界，
	enum{ __MAX_BYTES = 128 };//小区块的上限
	enum{ __NFREELISTS = __MAX_BYTES / __ALIGN };//free-list 的个数

	////放类中后面静态变量定义的时候会出错，不知道为什么,找到出错的原因了，类外边用类里边的类型定义时，或者是类型别名时，要显示的指明typename
	//union obj{
	//	union obj* free_list_link;
	//	char client_data[1];
	//};

	//未考虑过多线程的东西 。。。先把这个留着吧。。万一哪天要来改呢
	template<bool threads, int inst>
	class __default_alloc_template{
	private:
		//将要申请的内存调整为8的倍数，比如20会调整为24;
		static size_t round_up(size_t nbytes){
			return (nbytes + __ALIGN - 1) & ~(__ALIGN - 1);
		}
		/*这个地方是一个技巧，union的类型占空间只占其成员最大的那个那么大，比如下面这个占空间是1个字节，这样就不会耗费额外的空间了，
		*在内存分配中，如果内存没分配出去，这一个字节就用来当链表用，用来指向下一个空着的空间，即从第一字段看进去，这个obj是一个obj*的指针，
		*如果分配出去了，显然这个链表就不需要了，那么这个指针就当地址用，即从第二字段看进去用，是一个char*的指针。*/
		union obj{
			union obj* free_list_link;
			char client_data[1];
		};
		//用来存自由链表，我估摸着这个volatile是不是因为如果是多线程的话，其他线程有可能改变了自由链表的大小，所以要加这个限定字
		static obj * volatile free_list[__NFREELISTS];
		//来判断需要分配的内存处于freeList的哪个元素中，比如要分配10个字节的空间，那么应该从freeList[1]中取
		static size_t free_list_index(size_t nbytes){
			return (nbytes - 1) / __ALIGN;
		}
		//当freeList中没有可分配的空间时，从内存池中取得空间加入freeList中，并返回一个大小为n的区块
		static void *refill(size_t n);
		//配置一大块共nobjs个，大小为size的空间
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

	//静态变量的定义
	template<bool threads, int inst>
	char * __default_alloc_template<threads, inst>::start_free = 0;

	template<bool threads, int inst>
	char * __default_alloc_template<threads, inst>::end_free = 0;

	template<bool threads, int inst>
	size_t __default_alloc_template<threads, inst>::heap_size = 0;
	//注意这儿这个typename的用法
	template<bool threads, int inst>
	typename __default_alloc_template<threads, inst>::ptr_obj volatile __default_alloc_template<threads, inst>::free_list[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	//allocate实现
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::allocate(size_t n){
		obj * volatile *my_free_list;
		obj * result;
		if (n > __MAX_BYTES){//调用第一级分配器
			return malloc_alloc::allocate(n);
		}
		//找到大小合适的一个free_list
		my_free_list = free_list + free_list_index(n);
		result = *my_free_list;
		//如果当前free_list中没得了，就要从新填充这个free_list
		if (result == 0){
			//填充并返回一个大小为round（n）的区块
			void *r = refill(round_up(n));
			return r;
		}
		//让当前这个指向下一块
		*my_free_list = result->free_list_link;
		return result;
	}
	//deallocate实现
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
	//reallocate实现,没有将原来内存里的东西拷贝出来，只是重新分配了合适大小的内存
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::reallocate(void *p, size_t old_size, size_t new_size)
	{
		deallocate(p, old_size);
		p = allocate(nes_size);
	}
	//refill实现，从内存池中取得内存连接到free_list的对应位置上边去
	template<bool threads, int inst>
	void *__default_alloc_template<threads, inst>::refill(size_t n){
		int nobjs = 20;
		//从内存池总取得内存
		char *chunk = chunk_alloc(n, nobjs);
		obj* volatile *my_free_list;
		obj *result;
		obj *current_obj, *next_obj;
		if (nobjs == 1)
			return chunk;
		result = (obj *)chunk;
		my_free_list = free_list + free_list_index(n);//找到要放入的位置
		*my_free_list = current_obj = (obj*)(chunk + n);//放进去
		for (int i = 1; i < nobjs - 1; i++){
			next_obj = (obj*)((char*)current_obj + n);
			current_obj->free_list_link = next_obj;
			current_obj = next_obj;
		}
		current_obj->free_list_link = 0;
		return result;
	}

	//chunk_alloc实现，从内存池去得nobjs个大小为n的空间；如果内存池不够了就扩大内存池
	template<bool threads, int inst>
	char *__default_alloc_template<threads, inst>::chunk_alloc(size_t n, int &nobjs){
		char *result;
		size_t total_bytes = n*nobjs;
		size_t left_bytes = end_free - start_free;
		//够分，很好，分出去
		if (left_bytes >= total_bytes){
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//不够分，但是够分一部分！那就分一部分吧（left/n）这么多个
		else if (left_bytes >= n){
			nobjs = left_bytes / n;
			total_bytes = n*nobjs;
			result = start_free;
			start_free += total_bytes;
			return result;
		}
		//一个都不够分
		else{
			size_t bytes_to_get = 2 * total_bytes + round_up(heap_size >> 4);//右移4位的原因应该是为了让每次增加的量不至于太多
			//如果left_bytes还有，那么把剩下的这一点点给编入合适的free_list中，剩余量一定是8的倍数，因为每一次分配，申请取出都是8的倍数
			if (left_bytes > 0){
				obj * volatile *my_free_list = free_list + free_list_index(left_bytes);
				((obj *)start_free)->free_list_link = *my_free_list;
				*my_free_list = ((obj *)start_free);
			}
			start_free = (char *)malloc(bytes_to_get);
			if (0 == start_free){
				//如果没分配到,没分到的话就从现在的free_list里面扣吧。。。把剩下的拿过来填上，感觉好节约,从比当前这个大的里面拿
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
				//如果确实没分到
				end_free = 0;
				start_free = (char *)malloc_alloc::allocate(bytes_to_get);
			}
			heap_size += bytes_to_get;
			end_free = start_free + bytes_to_get;
			return(chunk_alloc(n, nobjs));
		}
	}

	//两级空间配置器设置
#ifdef __USE_MALLOC
	//typedef __malloc_alloc_template<0> malloc_alloc;
	typedef malloc_alloc alloc;
#else
	using  alloc = __default_alloc_template<false, 0>;
#endif

	//包装一个符合stl接口的类看，因为一二级分配器分配出来的内存都是按字节为单位的(void *)类型的
	template<typename T, typename Alloc = alloc>
	class simple_alloc{
	public:
		//分配n个T的内存
		static T *allocate(size_t n){
			return 0 == n ? 0 : (T*)Alloc::allocate(n*sizeof(T));
		}
		//分配一个T的内存
		static T *allocate(void){
			return (T*)Alloc::allocate(sizeof(T));
		}
		//归还内存
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