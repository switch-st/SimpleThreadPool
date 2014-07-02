#ifndef SIMPLE_THREAD_POOL_HPP
#define SIMPLE_THREAD_POOL_HPP

/**
 * 一个简单的线程池
 * 采用boost线程库
 * 尽提供创建和销毁一组线程的方法
 * 线程函数须采用boost线程库编写
 * 欢迎补充！
 **/

#include <stdarg.h>
#include <boost/thread.hpp>

#ifndef NAMESPACE_SWITCH_TOOL
    #define NAMESPACE_SWITCH_TOOL
    #define OPEN_NAMESPACE_SWITCHTOOL       namespace Switch { \
												namespace Tool {
    #define CLOSE_NAMESPACE_SWITCHTOOL      	}; \
											};
    #define USING_NAMESPACE_SWITCHTOOL      using namespace Switch::Tool;
#endif


OPEN_NAMESPACE_SWITCHTOOL

typedef void SimpleThreadFunc(void);


class SimpleThreadPool
{
public:
	SimpleThreadPool(void)
	{
		m_nMaxPoolSize = 0;
	}

	SimpleThreadPool(int size)
	{
		if (size >= 0) {
			m_nMaxPoolSize = size;
		} else {
			m_nMaxPoolSize = 0;
		}
	}

	~SimpleThreadPool(void)
	{
		StopThreadPool();
	}

public:
	int	AddThread(SimpleThreadFunc* func)
	{
		if (func == NULL || m_TGroup.size() >= m_nMaxPoolSize) {
			return -1;
		}

		m_TGroup.create_thread(func);

		return 0;
	}

	void StopThreadPool(void)
	{
		m_TGroup.interrupt_all();
		m_TGroup.join_all();
	}

	///设置线程池大小，只允许设置一次
	int SetMaxPoolSize(int size)
	{
		if (size < 0) {
			return -1;
		}

		if (m_nMaxPoolSize == 0) {
			m_nMaxPoolSize = size;

			return 0;
		}

		return -1;
	}

	/// 获取线程池大小
	int GetMaxPoolSize(void)
	{
		return m_nMaxPoolSize;
	}

	/// 获取线程池当前大小
	int GetPoolSize(void)
	{
		return m_TGroup.size();
	}

private:
	boost::thread_group				m_TGroup;
	unsigned int 					m_nMaxPoolSize;
};




CLOSE_NAMESPACE_SWITCHTOOL




#endif // SIMPLE_THREAD_POOL_HPP

