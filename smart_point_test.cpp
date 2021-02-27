//
// Created by 覃立中 on 2021/2/27.
//

#include<iostream>
#include <memory>

using namespace std;

/*
 * 我们应该避免在 stl 容器中使用 std::auto_ptr:因为当用算法对容器操作的时候（如最常见的容器元素遍历），
   很难避免不对容器中的元素实现赋值传递，这样便会使容器中多个元素被置为空指针，这不是我们想看到的，会造成很多
   意想不到的错误。
 */
void test_0()
{
    printf("-----------------------test_0(std::auto_ptr测试)-----------------------\n");

    //测试拷贝构造
    std::auto_ptr<int> sp1(new int(8));
    std::auto_ptr<int> sp2(sp1);
    if (sp1.get() != NULL)
    {
        std::cout << "sp1 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp1 is empty." << std::endl;
    }

    if (sp2.get() != NULL)
    {
        std::cout << "sp2 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp2 is empty." << std::endl;
    }

    //测试赋值
    std::auto_ptr<int> sp3(new int(8));
    std::auto_ptr<int> sp4;
    sp4 = sp3;
    if (sp3.get() != NULL)
    {
        std::cout << "sp3 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp3 is empty." << std::endl;
    }

    if (sp4.get() != NULL)
    {
        std::cout << "sp4 is not empty." << std::endl;
    }
    else
    {
        std::cout << "sp4 is empty." << std::endl;
    }

}

/*
 * std::unique_ptr 对象初始化三种方式
   （1）std::unique_ptr<int> sp1(new int(123));
   （2）std::unique_ptr<int> sp2;  sp2.reset(new int(123));
   （3）std::unique_ptr<int> sp3 = std::make_unique<int>(123);(c++14才支持)

 *std::unique_ptr 禁止复制语义，为了达到这个效果，std::unique_ptr 类的拷贝构造函数和
  赋值运算符（operator =）被标记为 delete。也就是说对于test_0的情况如果用std::unique_ptr编译阶段就会报错

 *
 */
void test_1()
{
    printf("\n-----------------------test_1(std::unique_ptr测试)-----------------------\n");
    std::unique_ptr<int> sp1(new int(123));

    std::unique_ptr<int> sp2(std::move(sp1));//sp1不再持有堆内存的引用，变成一个空的智能指针对象。

    std::unique_ptr<int> sp3;
    sp3 = std::move(sp2);//sp2 不再持有堆内存的引用，变成一个空的智能指针对象。

    //cout << "*sp2 = " << *sp2 <<endl;
    cout << "*sp3 = " << *sp3 <<endl;
}

/*
 * std::unique_ptr 对其持有的资源具有独占性，而 std::shared_ptr 持有的资源可以在多个 std::shared_ptr 之间共享，
   每多一个 std::shared_ptr 对资源的引用，资源引用计数将增加 1，每一个指向该资源的 std::shared_ptr 对象析构时，
   资源引用计数减 1，最后一个 std::shared_ptr 对象析构时，发现资源计数为 0，将释放其持有的资源。

 *std::shared_ptr 提供了一个 use_count() 方法来获取当前持有资源的引用计数

 * std::shared_ptr 对象初始化三种方式
   （1）std::shared_ptr<int> sp1(new int(123));
   （2）std::shared_ptr<int> sp2;  sp2.reset(new int(123));
   （3）std::shared_ptr<int> sp3 = std::make_shared<int>(123);
 */

class A
{
public:
    A()
    {
        std::cout << "A constructor" << std::endl;
    }

    ~A()
    {
        std::cout << "A destructor" << std::endl;
    }
};

void test_2()
{
    printf("\n-----------------------test_2(std::shared_ptr测试)-----------------------\n");
    //初始化方式1
    std::shared_ptr<A> sp1(new A());

    std::cout << "use count: " << sp1.use_count() << std::endl;

    //初始化方式2
    std::shared_ptr<A> sp2(sp1);
    std::cout << "use count: " << sp1.use_count() << std::endl;

    sp2.reset();
    std::cout << "use count: " << sp1.use_count() << std::endl;

    {
        std::shared_ptr<A> sp3 = sp1;
        std::cout << "use count: " << sp1.use_count() << std::endl;
    }

    std::cout << "use count: " << sp1.use_count() << std::endl;
}

int main(int argc, char **argv) {
    test_0();
    test_1();
    test_2();

    return 0;
}