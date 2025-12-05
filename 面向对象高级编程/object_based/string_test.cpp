#include<iostream>
#include "string.h"
using namespace std;
int main() {
    String s1("world");//s1()会报错，String s1()会被解析为函数声明而不是对象创建
    //应该使用 String s1或 String s1("")
    String s2("hello");

    String s3(s1);
    cout<<s3<<endl;
    s3=s2;
    cout<<s3<<endl;
    return 0;
}

//