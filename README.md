# XSTL
实现c++ STL的一部分内容

# 目录

    XSTL
    │  .gitignore                   git提交时忽略的内容
    │  README.md                    readme
    │  XSTL.sln                     vs2015解决方案文件,可采用vs2015直接打开
    │  模块说明.md                   STL库中的各个模块说明
    │  
    └─XSTL                          项目文件夹
        │  main.cpp                 主函数入口
        │  test.cpp                  
        │  test_deque.cpp
        │  XSTL.vcxproj             vs2015工程文件
        │  
        ├─header                    包含了头文件，实现的XSTL模板库位于此文件夹中
        │  │  allocator.h
        │  │  stl_alloc.h
        │  │  stl_construct.h
        │  │  stl_deque.h
        │  │  stl_iterator.h
        │  │  stl_list.h
        │  │  stl_uninitialized.h
        │  │  stl_vector.h
        │  │  type_traits.h
        │  │  
        │  └─test                   测试代码的头文件在此文件夹中
        │          test.h
        │          test_deque.h
        │          test_list.h
        │          test_vector.h
        │          
        └─test                      测试代码的源文件位于此文件夹中
                test_list.cpp
                test_vector.cpp