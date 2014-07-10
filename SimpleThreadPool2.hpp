#ifndef SIMPLE_THREAD_POOL_HPP
#define SIMPLE_THREAD_POOL_HPP

/**
 * 一个简单的线程池 v0.2
 * 采用boost线程库
 * 线程函数须采用boost线程库编写
 * 线程函数如有参数，可使用boost::bind传入参数
 * 编译时链接libboost_thread和libboost_system
 *
 * 欢迎补充！
 **/

#include <list>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/bind.hpp>
#include <SimpleJob.hpp>


#ifndef NAMESPACE_SWITCH_TOOL
    #define NAMESPACE_SWITCH_TOOL
    #define OPEN_NAMESPACE_SWITCHTOOL       namespace Switch { \
												namespace Tool {
    #define CLOSE_NAMESPACE_SWITCHTOOL      	}; \
											};
    #define USING_NAMESPACE_SWITCHTOOL      using namespace Switch::Tool;
#endif


OPEN_NAMESPACE_SWITCHTOOL


//typedef void SimpleThreadFunc(void);





class SimpleThreadPool
{
public:
	SimpleThreadPool(void)
	{
		m_nMaxPoolSize = 0;
		m_pJoinThread = new boost::thread(boost::bind(&SimpleThreadPool::ThreadJoin, this));
	}

	SimpleThreadPool(unsigned int size)
	{
        m_nMaxPoolSize = 0;

		m_pJoinThread = new boost::thread(boost::bind(&SimpleThreadPool::ThreadJoin, this));
	}

	~SimpleThreadPool(void)
	{
	    m_pJoinThread->interrupt();
	    m_pJoinThread->join();
	    delete m_pJoinThread;

        StopThreadPool();
	}

public:
	template < typename T >
	int	AddThread(T func)
	{
	    m_TMutex.lock();
		if (m_lpThread.size() >= m_nMaxPoolSize) {
            m_TMutex.unlock();
			return -1;
		}

        m_lpThread.push_back(new boost::thread(func));
        m_TMutex.unlock();

		return 0;
	}

    /// 停止线程池
	int StopThreadPool(void)
	{
        std::list< boost::thread* >::iterator iter, end;

        end = m_lpThread.end();
        for (iter = m_lpThread.begin(); iter != end;)
        {
            boost::thread* p = *iter;
            p->interrupt();
            p->join();
            delete p;
        }

        return 0;
	}

	/// 设置线程池大小
	int SetMaxPoolSize(unsigned int size)
	{
        m_TMutex.lock();
        if (size > m_nMaxPoolSize || size >= m_lpThread.size())
        {
            m_nMaxPoolSize = size;
            m_TMutex.unlock();
            return 0;
        }
        m_TMutex.unlock();

        return -1;
	}

	/// 获取线程池大小
	int GetMaxPoolSize(void)
	{
	    m_TMutex.lock();
	    int size = m_nMaxPoolSize;
	    m_TMutex.unlock();

		return size;
	}

	/// 获取线程池当前大小
	int GetPoolSize(void)
	{
	    m_TMutex.lock();
	    int size = m_lpThread.size();
	    m_TMutex.unlock();

		return size;
	}

private:
    void ThreadJoin(void)
    {
        std::list< boost::thread* >::iterator iter, end;

        while(1)
        {
            m_TMutex.lock();
            end = m_lpThread.end();
            for (iter = m_lpThread.begin(); iter != end;)
            {
                if ((*iter)->timed_join(boost::posix_time::microseconds(1)))
                {
                    boost::thread* p = *iter;
                    iter = m_lpThread.erase(iter);
                    delete p;
                }
                else
                {
                    ++iter;
                }
            }
            m_TMutex.unlock();

            boost::this_thread::sleep(boost::posix_time::milliseconds(1));
        }
    }

private:
    boost::mutex                    m_TMutex;
	std::list< boost::thread* >     m_lpThread;
	boost::thread*                  m_pJoinThread;
	unsigned int 					m_nMaxPoolSize;
};




CLOSE_NAMESPACE_SWITCHTOOL




#endif // SIMPLE_THREAD_POOL_HPP

