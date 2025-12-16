//G2.9版标准库中的list

template <class T> struct list_node {
    typedef void* void_pointer;
    void_pointer prev;
    void_pointer next;
    T data;
};

template <class T,class Alloc=alloc> class list {
    protected:
    typedef list_node<T> node;

    public:
    typedef node* link_type;
    typedef _list_iterator<T,T&,T*> iterator;
//链表空间不连续，所以iterator就不能是一个普通的指针
    //所以这个iterator需要是个class，能够做到++后，可以指向下一个元素的地址
    protected:
    link_type head;
};

template<class T,class Ref,class Ptr>
struct _list_iterator {
    //为了让iterator看起来像一个指针
    //就需要大量的操作符重载
};

//为了区分++i与i++,加了int这一参数，只是为了区分，实际上没有意义。
self& operator++() {//前++
    node=(link_type)((*node).next);
    return *this;
}
self operator++(int) {//后++
    self temp=*this;
    ++*this;
    return temp;
}//这其中的操作符已经被重载过了