#include <iostream>
#include <unistd.h>

#include <boost/bind.hpp>

#include "SimpleThreadPool2.hpp"

using namespace std;
using namespace boost;
USING_NAMESPACE_SWITCHTOOL

double func1(void* p)
{
    int num = *(int*)p;
    for(int i = 0; i < num * 3; ++i)
    {
        cout << "func1 : " << num << endl;
        //sleep(1);
    }

    return 1.2;
}

void func2(void)
{
    cout << "func2 : " << endl;
}

class A
{
public:
    int fa(int num)
    {
        cout << "in A::fa num : " << num << endl;

        return 5;
    }
};


int main(int argc, char** argv)
{
    int num = 1;
    int* p = &num;
    SimpleJob< double > sj(func1, (void*)p);
    cout << "return = " << sj.CallJob() << endl;

    SimpleJob< void > sj2(func2);
    sj2.CallJob();

    A a;
    SimpleJob< int > sj1(&A::fa, &a, 10);
    cout << "return = " << sj1.CallJob() << endl;


    return 0;

    SimpleThreadPool pool;

    pool.SetMaxPoolSize(10);

    int num1 = 1;
    int* p1 = &num1;
    pool.AddThread(boost::bind(func1, (void*)p1));
    int num2 = 2;
    int* p2 = &num2;
    pool.AddThread(boost::bind(func1, (void*)p2));
    int num3 = 3;
    int* p3 = &num3;
    pool.AddThread(boost::bind(func1, (void*)p3));
    pool.AddThread(func2);

    while(1)
    {
        cout << "\t\t\tthread pool size = " << pool.GetPoolSize() << endl;
        if (pool.GetPoolSize() == 0)
        {
            break;
        }
        sleep(1);
    }

    pool.StopThreadPool();

    //pause();

    return 0;
}



