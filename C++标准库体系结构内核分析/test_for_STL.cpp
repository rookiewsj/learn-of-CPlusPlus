using namespace std;
const long ASIZE  =   500000L;
//我想将多个容器的测试，放在同一个程序里，但我又想保持测试的独立性
//因此，我会使用namespace
#include<array>//
#include<iostream>
#include<ctime>
#include<cstdlib>//这个头文件用于存放

long get_a_target_long() {//从用户输入获取一个long
    long target=0;
    cout<<"target (0~"<<RAND_MAX<<"):";
    //RAND_MAXRAND_MAX是 C/C++ 标准库中定义的一个常量，代表了 rand()函数所能返回的最大值
    cin>>target;
}

int compareLongs(const void* a,const void* b) {
    return ( *(long*)a - *(long*)b );
}
//void*是一个无类型的指针
//可以指向任何类型的数据对象的内存地址，但其本身不包含所指向数据的类型信息
//为什么要这样写呢？
//为什么不直接传进去两个long型的参数呢？

namespace jj01//array容器的测试程序
{
    void test_array() {//由于调用了STL中的array，所以这里测试的是标准库中的array
        cout<<"test_array--------------------"<<endl;
        array<long,ASIZE> c;
        clock_t timestart=clock();
        for (long i=0;i<ASIZE;++i) {
            c[i]=rand();
        }
        cout<<"milliseconds: "<<(clock()-timestart)<<endl;
        cout<<"array-size: "<<c.size()<<endl;//
        cout<<"array-front: "<<c.front()<<endl;//
        cout<<"array-back: "<<c.back()<<endl;//
        cout<<"attay-data: "<<c.data()<<endl;//

        long target=get_a_target_long();

        timestart=clock();
        ::qsort(c.data(),ASIZE,sizeof(long),compareLongs);


    }

}
// Created by OMEN on 2025/11/29.
//
int main() {
    std::cout<<"hello"<<std::endl;
    jj01::test_array();
    return 0;
}