//
// Created by 覃立中 on 2021/4/1.
//实现自己复数类
//

#include <iostream>
#include <string.h>

using namespace std;

class MyComplex
{
public:
    MyComplex(double real = 0.0, double img = 0.0); //构造函数
    MyComplex(const MyComplex& rhs);                //拷贝构造函数
    ~MyComplex(){}                                  //析构函数

    MyComplex& operator = (const MyComplex& rhs);                //赋值运算符重载
    friend ostream& operator << (ostream& os, const MyComplex& rhs); //输出运数符重载
    MyComplex operator + (const MyComplex& rhs);
private:
    double m_real; //实部
    double m_img;  //虚部
};

/**************************构造/拷贝构造/析构函数**************************/
//构造函数
MyComplex::MyComplex(double real, double img)
{
    m_real = real;
    m_img = img;
}

//拷贝构造函数
MyComplex::MyComplex(const MyComplex& rhs)
{
    m_real = rhs.m_real;
    m_img = rhs.m_img;

    cout << "copy construct function" << endl;
}

MyComplex MyComplex::operator + (const MyComplex& rhs)
{
    MyComplex c(m_real + rhs.m_real, m_img + rhs.m_img);

    return  c;
}
/******************************运算符重载******************************/
//重载输出，重载为友元函数
ostream& operator << (ostream& os, const MyComplex& rhs)
{
    os << "(" << rhs.m_real << ", " << rhs.m_img << ")" << endl;
    return os;
}

//=重载，必须重载为成员函数
MyComplex& MyComplex::operator = (const MyComplex& rhs)
{
    m_real = rhs.m_real;
    m_img = rhs.m_img;

    cout << "operator = function" << endl;
    return *this;
}

int main(int argc, char **argv)
{
    MyComplex c1(3.2, 10);
    cout << c1;

    MyComplex c2;
    c2 = c1;
    cout << c2;

    MyComplex c;
    c = c1 + c2;
    cout << c;

    return 0;
}