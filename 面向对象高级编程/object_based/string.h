//
// Created by OMEN on 2025/11/26.
//

#ifndef PRACTIC_STRING_H
#define PRACTIC_STRING_H

#include<cstring>
class String {
public:
    //big three:拷贝构造、拷贝赋值、析构函数
    String(const char* cstr=0);
    String(const String& str);
    String& operator=(const String&);//& is it allow?
    //String & operator<<(const)
    ~String();
    inline char* get_c_str() const{return data;}

private:
    char * data;
};

inline String::String(const char *cstr) {
    if (cstr) {
        data=new char[strlen(cstr)+1];
        strcpy(data,cstr);
    }else {
        data=new char[1];
        *data='\0';
    }


}
inline String::String(const String &str) {
    data=new char[strlen(str.data)+1];
    strcpy(data,str.data);
}

inline String& String::operator=(const String &str) {
    if (this==&str) {
        return *this;
    }//自我赋值
    //retun this 返回的是指向当前对象的指针 return *this 返回的是当前对象的引用
    delete[] data;
    data=new char[strlen(str.data)+1];//+1 means need one space to set "\0"
    //data=str.data;这样写是错误的，这会导致内存的泄露data是一个指针，不是数据
    strcpy(data,str.data);
    return *this;
}

inline String::~String() {
    delete [] data;
}

#include<iostream>
using namespace std;
ostream& operator<<(ostream& os,const String & str) {
    os<<str.get_c_str();//非成员函数
    return os;
}

#endif //PRACTIC_STRING_H