# C++标准库(STL)与泛型编程
___
## 目录
* ### [概述](#概述)
* ### [第一部分.通过一个test程序浅识STL(如何使用容器)](#第一部分通过一个test程序浅识STL如何使用容器)
  * #### [序列式容器(sequence container)]()
    * ##### [如何使用array]()
    * ##### [如何使用vector]()
    * ##### [如何使用list]()
    * ##### [如何使用deque]()
    * ##### [如何使用stack]()
    * ##### [如何使用queue]()
  * #### [关联式容器(associative container)]()
    * 
### [第二部分.通过源码深入认识STL(Container为主)]()
* #### [空间分配器(allocator)]()
* #### [迭代器概念与traits编程技法]()
### [第三部分.通过源码深入认识STL(Algorithm为主)]()
### [第四部分.扩充STL]()

## 概述

&emsp;&emsp;如Effective C++书中所写，C++不像是一种单一的语言，更像是一个语言联邦。其中包括C语言、面向对象、泛型编程、STL四个部分。
其中面向对象编程与泛型编程，我认为是数据结构与算法的两个不同的侧重面。**面向对象**更多的是将数据结构作为主题，将数据与处理这些数据的算法放到一起形成一个类。(这样想实际上有一些局限，这更像是object based，实际上object oriented才是面向对象的精髓)。
而**泛型编程**更多的是将算法作为主体，由于对数据的操作无非就是增、删、改、查。对数据的操作是类似，但对于不同的数据结构，要实现这些操作，无论是在逻辑上，还是在物理上都是不同的。很容易就会提出一个疑问：如果将算法作为主题，能不能写出不依赖特定数据的通用算法呢？
这也就是泛型编程的目的。  
&emsp;&emsp;**我们为什么要学习STL呢？或者说学习STL有什么好处？**  
1、STL在物理上，大部分是通过泛型编程实现的，学习STL能够帮助我们学习泛型编程。
2、 

> 由于篇幅原因，不好详细说明，以下是一些相关的知识：
> * 面向对象与泛型编程的比较，点[这里]()
> * 面向对象高级编程的相关知识，点[这里]()
> * 泛型编程的相关知识，点[这里]()

### STL的六大组件
&emsp;&emsp;我们已经学过数据结构与算法，可以想到**容器**(Container)就是用来存放各种数据的数据结构。
我们想要把数据放入容器，数据就要占据内存，这就产生了一个问题：放进去的数据要占据那些内存呢？即如何分配内存呢？  
&emsp;&emsp;我们希望在使用的时候，只要考虑把数据放进去，把数据拿出来，就可以了，不用考虑内存的相关问题。
所以，为了实现这一目的，我们就需要**分配器**(Allocator)来支持容器(Container)。  
&emsp;&emsp;解决了如何存取数据这个问题之后，我们需要思考如何对容器中的数据进行操作？这就需要相应的**算法**(Algorithm)。  
与面向对象不同，STL是以泛型思维作为设计观念的。所以，我们会把算法作为主体，将处理数据的操作抽离出来，称为算法(Algorithm)。  
&emsp;&emsp;我们将容器与算法分了开来，那么算法要如何对容器中相应的数据进行操作呢？这就需要一座桥梁来连接算法与容器，这座桥梁就是**迭代器**(Iterator)。  

<img src="image/stl-1-1.png">
STL六大组件的交互关系：Container通过Allocator取得数据储存空间，Algorithm通过Iterator存取Container内容，Functor可以协助Algorithm完成不同的策略变化，Adapter可以修饰或套接Functor。

___
## 第一部分.通过一个test程序浅识STL(如何使用容器)

___
## 第二部分.通过源码深入认识STL(Container为主)
### 2.1 空间分配器(allocator)

### 2.2 迭代器概念与traits编程技法
___
**迭代器的重要性？为什么需要学迭代器？**  
&emsp;&emsp;从STL的中心思想入手，
STL的中心思想：将容器与算法分开，彼此独立设计，最后再用一个胶着剂将它们撮合在一起。
而容器和算法的泛型化，从物理实现上并不困难，C++的class template 和function template可分别达成目标。
所以，如何设计出两者之间的良好胶着剂，即如何设计出良好的迭代器？这才是难题。  
___  

**那么，什么是迭代器呢？(迭代器概念)**  
&emsp;&emsp;迭代器是一种抽象的设计概念，现实程序语言中并没有直接对应于这个概念的实物。  
&emsp;&emsp;**iterator模式的定义**：
提供一种方法，使之能够依序访问某个容器所含的各个元素，而无需暴露该容器的内部表述方式.  
&emsp;&emsp;迭代器扮演容器与算法之间的胶合剂，是所谓的**泛型指针**。
从实现的角度来看，迭代器是一种将operator*、operator->、operator++、operator--等指针相关操作予以重载的class template（有点像类指针的类）  
&emsp;&emsp;我们根据定义不难发现，每种容器可能都有对应的iterator，下面是一个例子

```P115
#include<iostream>
#include<vector>
#include<list>
#include<deque>
#include<algorithm>
using namespace std;

template<class T,class inputiterator> inputiterator myfind(inputiterator first,inputiterator last,const T value) {
    while (first!=last&&*first!=value) {
        ++first;
    }
    return first;
}
//若不修改函数名，可能会出现函数调用不明确的问题
int main() {
    const int arraysize=7;
    int ia[7]={0,1,2,3,4,5,6};
    vector<int> ivect(ia,ia+arraysize);
    list<int> ilist(ia,ia+arraysize);
    deque<int> ideque(ia,ia+arraysize);

    vector<int>::iterator it1=myfind(ivect.begin(),ivect.end(),4);
    if (it1==ivect.end()) {
        cout<<"4 not found"<<endl;
    }else {
        cout<<*it1<<"found"<<endl;
    }

    list<int>::iterator it2=myfind(ilist.begin(),ilist.end(),5);
    if (it2==ilist.end()) {
        cout<<"5 not found"<<endl;
    }else {
        cout<<*it2<<"found"<<endl;
    }

    deque<int>::iterator it3=myfind(ideque.begin(),ideque.end(),7);
    if (it3==ideque.end()) {
        cout<<"7 not found"<<endl;
    }else {
        cout<<*it3<<"found"<<endl;
    }
    return 0;
}
```
&emsp;&emsp;通过这个例子，感觉迭代器好像依附在容器之下，**真的是这样吗？** 那么有没有独立、泛用的迭代器呢？我们又该如何设计呢？  
___
**如何设计、实现一个良好的iterator？ 一个良好的iterator需要具备什么东西？**  
&emsp;&emsp;我们想要设计出一个iterator，使其能够遍历container的元素，第一想法就是C语言中的指针。通过指针来指向容器中的各个元素，从而实现遍历。但是，指针的缺点很明显，它只是一个地址，既无法持有自己的状态又无法达到该有的适配性(注：如果难以理解，可以对照一下函数指针的缺点，请点[这里]())。  
&emsp;&emsp;所以，迭代器不能是一个单纯的指针，它应该是一种行为类似指针的对象，即是一种smart pointer。
因此为了实现这一目的，我们需要创建一个class，这个class是类指针的，所以我们需要对operator* 与operator->进行操作符重载。  
&emsp;&emsp;C++标准库中的auto_pr可供我们参考，源码：
```auto_ptr源码简化版
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
```
**练习：为list(链表)设计一个迭代器**  
&emsp;&emsp;要想为链表设计一个迭代器，首先要对list的实现细节非常了解





___
 **迭代器的五个相应型别**  
&emsp;&emsp;通过上面的一个例子，我们大体可以知道如何设计实现一个迭代器。但显然，这个迭代器还不够优秀。有时候，例如在算法中运用迭代器时，可能会需要知道关于迭代器的一些信息：
1. value type：迭代器所指对象的数据类型(型别)
2. difference type：两个迭代器之间的距离
3. reference type：迭代器的类型，能否改变迭代器所指对象的内容
4. pointer type：
5. iterator_category

这些信息被称为**迭代器相应型别**。

```声明内嵌型别
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
```