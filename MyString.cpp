//
// Created by 覃立中 on 2021/4/1.
//实现自己string类
//

#include <iostream>
#include <string.h>

using namespace std;

class MyString
{
public:
    MyString(const char* str = NULL);   //构造函数
    MyString(const MyString& rhs);      //复制构造函数

    ~MyString();  //析构函数

    MyString& operator = (const MyString& rhs);  //=重载， [],(), ->, =必粗重载为成员函数
    char& operator [] (size_t index); //[]重载， [],(), ->, =必粗重载为成员函数

    friend ostream& operator << (ostream& os, const MyString& rhs); //重载输出
    friend istream& operator >> (istream& in, const MyString& rhs); //重载输入

    size_t length();
private:
    char* m_str;
    size_t size;
};
/**************************构造/拷贝构造/析构函数**************************/
//构造函数
MyString::MyString(const char* str)
{
    if (NULL == str)
    {
        size = 0;
        m_str = new char[1];
        m_str[size] = '\0';
    }else
    {
        size = strlen(str);
        m_str = new char[size + 1];
        strncpy(m_str, str, size);
        m_str[size] = '\0';
    }
}

//复制构造函数
MyString::MyString(const MyString& rhs)
{
    size = rhs.size;
    m_str = new char[size + 1];
    strncpy(m_str, rhs.m_str, size);
    m_str[size] = '\0';

    cout << "copy construct function" << endl;
}

//析构函数
MyString::~MyString()
{
    if (NULL != m_str)
    {
        delete []m_str;
        m_str = NULL;
    }
}

/******************************运算符重载******************************/
//重载输出，重载为友元函数
ostream& operator << (ostream& os, const MyString& rhs)
{
    os << rhs.m_str << endl;
    return os;
}

//重载输入，重载为友元函数
istream& operator >> (istream& in, const MyString& rhs)
{
    in >> rhs.m_str;
    return in;
}

//[]重载，必须重载为成员函数
char& MyString::operator [] (size_t index)
{
    if (index >= size)
    {
        cout << "illegal memory acess!" << endl;
    }

    return  m_str[index];
}

//=重载，必须重载为成员函数
MyString& MyString::operator = (const MyString& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    delete []m_str;

    size = rhs.size;
    m_str = new char[size + 1];
    strncpy(m_str, rhs.m_str, size);
    m_str[size] = '\0';

    cout << "operator = function" << endl;
    return *this;
}

/******************************普通成员函数******************************/
size_t MyString::length()
{
    return size;
}

int main(int argc, char **argv)
{
    MyString s1 = "123456";
    MyString s2(s1);

    cout << "s1.length() = " << s1.length() << endl;
    cout << s1;

    cout << "s2.length() = " << s2.length() << endl;
    cout << s2;

    MyString s3;
    s3 = s2;
    cout << "s3.length() = " << s3.length() << endl;
    cout << s3;

    cout << "s3[2] = " << s3[2] << endl;
    return 0;
}

