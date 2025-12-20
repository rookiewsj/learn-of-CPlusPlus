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