#include <iostream>
#include <unistd.h>

#include <boost/bind.hpp>

#include "SimpleThreadPool.hpp"

using namespace std;
using namespace boost;
USING_NAMESPACE_SWITCHTOOL


double func1(void* p)
{
    int num = *(int*)p;
    for(int i = 0; i < num * 3; ++i)
    {
        cout << "func1 : " << num << endl;
        sleep(1);
    }

    return 1.2;
}

void func2(void)
{
    cout << "func2 : " << endl;
}
int func3(int num)
{
    cout << "func3 : " << num << endl;
    sleep(1);
    return 0;
}

class A
{
public:
    int fa(int num)
    {
        cout << "in A::fa num : " << num << endl;
		sleep(1);
        return 5;
    }
};


int main(int argc, char** argv)
{
	cout << "type job pool" << endl;
    STJPool job_pool(10, 20);

    cout << "begin" << endl;
    for (int i = 0; i < 100; ++i)
	{
        A a;
        SJob job(&A::fa, &a, i);
        job_pool.add_job_block(job);
	}
	cout << "end" << endl;

	sleep(5);
	job_pool.stop();
	cout << "done" << endl;


	cout << endl << endl << endl;
	cout << "type function pool" << endl;
	STFPool func_pool;
	func_pool.SetMaxPoolSize(10);

    int num1 = 1;
    int* p1 = &num1;
    func_pool.AddThread(boost::bind(func1, (void*)p1));
    int num2 = 2;
    int* p2 = &num2;
    func_pool.AddThread(boost::bind(func1, (void*)p2));
    int num3 = 3;
    int* p3 = &num3;
    func_pool.AddThread(boost::bind(func1, (void*)p3));
    func_pool.AddThread(func2);

    while(1)
    {
        cout << "\t\t\tthread pool size = " << func_pool.GetPoolSize() << endl;
        if (func_pool.GetPoolSize() == 0)
        {
            break;
        }
        sleep(1);
    }

    func_pool.StopThreadPool();

	return 0;
}

