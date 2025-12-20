#include <iostream>

template<class T> struct MyIter{
    typedef T value_type;//内嵌型别声明
    T* ptr;
    MyIter(T* p=0):ptr(p){}
    T& operator*() const{
        return *ptr;
    }
};

template<class T> typename T::value_type func(T ite) {
    return *ite;
}
int main(){
    MyIter<int> ite(new int(1));
    std::cout<<func(ite)<<std::endl;
    return 0;
}

