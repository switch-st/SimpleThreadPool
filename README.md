SimpleThreadPool
================

地址
https://github.com/switch-st/SimpleThreadPool.git

说明
 * 基于boost线程组概念封装的超简单的线程池
 * 一个简单的线程池
 * 采用boost线程库
 * 仅提供创建和销毁一组线程的方法
 * 线程函数须采用boost线程库编写
 *
 * 欢迎补充！

调用
	#include <SimpleThreadPool.hpp>

	USING_NAMESPACE_SWITCHTOOL

	SimpleThreadFunc tFunc1, tFunc2; 	// 线程回调函数
	SimpleThreadPool tPool(10);
	tPool.AddThread(&tFunc1);
	tPool.AddThread(&tFunc2);

	cout << "Max = " << tPoll.GetMaxPoolSize() << endl;
	cout << "Curr = " << tPoll.GetPoolSize() << endl;

	pause();

	tPoll.StopThreadPool();


			by switch
			switch.st@gmail.com

