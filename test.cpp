#include <iostream>
#include <unistd.h>

#include <boost/bind.hpp>

#include "SimpleThreadPool.hpp"

using namespace std;
using namespace boost;
USING_NAMESPACE_SWITCHTOOL

void func1(void* p)
{
    int num = *(int*)p;
    for(int i = 0; i < num * 3; ++i)
    {
        cout << "func1 : " << num << endl;
        sleep(1);
    }
}

void func2(void)
{
    cout << "func2 : " << endl;
}


int main(int argc, char** argv)
{
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



