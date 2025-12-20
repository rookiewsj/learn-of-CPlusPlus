#include<iostream>
//书中的代码经过简化，但只要能够知道release()是用来干嘛的就可以理解
template <class T> class auto_ptr {//虽然，这个智能指针已经被弃用了。但其类声明值得看一看
    public:
        explicit auto_ptr(T* p=0):ptr(p){}//explicit
        template<class U> auto_ptr(auto_ptr<U>& rhs):ptr(rhs.release()){}
        //在这串代码片段中，release() 函数的定义其实缺失了，但它是 auto_ptr 机制的核心。
        //rhs.release() 的作用是交出所有权。它让 rhs（Right Hand Side，即被拷贝的那个对象）放弃对指针的控制，并返回该指针，以便让新对象接管它。
        ~auto_ptr(){delete ptr;}
        template<class U> auto_ptr<U>& operator=(auto_ptr<U>& rhs) {
            if (this!=&rhs) reset(rhs.release());
            return *this;
        }
        //big three

        T& operator*()const{return *ptr;}
        T* operator->()const{return ptr;}
        //为实现类指针的class所要做的努力
        T* get() const{return ptr;}

    private:
        T* ptr;
};
int main() {
    return 0;
}
    //
// Created by OMEN on 2025/12/16.
//