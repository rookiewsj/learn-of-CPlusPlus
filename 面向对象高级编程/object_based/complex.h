#ifndef COMPLEX
#define COMPLEX

class complex{

    public:
        complex(double i=0,double j=0):re(i),im(j){};//初值列：是一种特殊的构造函数语法，用于在创建对象时初始化类的成员变量
        complex & operator+=(const complex&);
        inline double get_real() const{return re;}//该const表示这个函数不会改变类中的数据
        inline double get_imag() const{return im;}

    private:
        double re,im;

    friend complex& __doapl (complex *, const complex&);
};

inline complex& __dopal(complex* ths,const complex& r){
  ths->re += r.re;
  ths->im += r.im;
  return *ths;
}

inline complex& complex::operator+=(const complex& r){
    // this.im+=r.get_imag;
    // this.re+=r.get_real;
    // return *this;
    //由于某些考量，会把这些工作交给另一个函数去做，标准库中这个函数叫_doapl
    return __doapl(this,r);
}

inline complex operator+(const complex& a,const complex& b){
    return complex(a.get_real+b.get_real,a.get_imag+b.get_imag);
}

#endif