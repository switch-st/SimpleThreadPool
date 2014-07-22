SimpleThreadPool
================

地址
https://github.com/switch-st/SimpleThreadPool.git

说明
 * 
 * 一个简单的线程池 v0.3
 * 采用boost线程库
 * 线程函数须采用boost线程库编写
 * 线程函数如有参数，可使用boost::bind传入参数
 * 编译时链接libboost_thread和libboost_system
 * 
 * 分为两种模式，函数模式和任务模式。
 * 函数模式，为每一个传入的函数创建一个线程，函数返回则线程退出；
 * 任务模式，将函数封装为任务，任务在线程池内排队，按顺序执行，
 *				执行完成后，任务退出，线程等待。
 * 
 * 欢迎补充！

调用
	调用方式详见测试文件test.cpp。

			by switch
			switch.st@gmail.com

