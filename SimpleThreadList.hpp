#ifndef SIMPLE_THREAD_LIST_HPP
#define SIMPLE_THREAD_LIST_HPP

/**
 * 线程相关类实现
 *
 * 欢迎补充！
 **/

#include <list>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/type_traits.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

#ifndef NAMESPACE_SWITCH_TOOL
    #define NAMESPACE_SWITCH_TOOL
    #define OPEN_NAMESPACE_SWITCHTOOL       namespace Switch { \
												namespace Tool {
    #define CLOSE_NAMESPACE_SWITCHTOOL      	}; \
											};
    #define USING_NAMESPACE_SWITCHTOOL      using namespace Switch::Tool;
#endif


OPEN_NAMESPACE_SWITCHTOOL


class SimpleThreadList : public boost::noncopyable
{
public:
    typedef std::list< boost::thread* >::iterator iterator;
public:
    SimpleThreadList(void)
    {
        m_nMaxThreadNum = 0;
        m_bStopFlag = false;
    }

    SimpleThreadList(unsigned int max, const boost::function< void() >& func)
    {
        m_nMaxThreadNum = max;
        m_oFunc = func;

        for (unsigned int i = 0; i < max; ++i)
        {
			m_lpThread.push_back(new boost::thread(m_oFunc));
        }
        m_bStopFlag = false;
    }

    ~SimpleThreadList(void)
    {
    	iterator iter, end;
    	end = m_lpThread.end();
    	for (iter = m_lpThread.begin(); iter != end; ++iter)
		{
			(*iter)->join();
			delete (*iter);
		}
    }

    bool set_thread_func(const boost::function< void() >& func)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        if (m_bStopFlag)
		{
			return false;
		}
        m_oFunc = func;

        return true;
    }

    bool set_max_thread_num(unsigned int max)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        if (m_bStopFlag || max <= m_nMaxThreadNum)
        {
            return false;
        }

        for (unsigned int i = m_nMaxThreadNum; i < max; ++i)
        {
            m_lpThread.push_back(new boost::thread(m_oFunc));
        }
        m_nMaxThreadNum = max;

        return true;
    }

    int get_max_thread_num(void)
    {
		boost::lock_guard< boost::mutex > guard(m_oMutex);
		return m_nMaxThreadNum;
    }

	int get_current_thread_num(void)
    {
		boost::lock_guard< boost::mutex > guard(m_oMutex);
		return m_lpThread.size();
    }

    void stop(void)
    {
    	boost::lock_guard< boost::mutex > guard(m_oMutex);
    	m_bStopFlag = true;

    	iterator iter, end;
    	end = m_lpThread.end();
    	for (iter = m_lpThread.begin(); iter != end; ++iter)
		{
			(*iter)->join();
			delete (*iter);
		}
		m_lpThread.clear();
    }


	/// TODO get besy/idle thread
private:
    std::list< boost::thread* >				m_lpThread;
    boost::mutex                            m_oMutex;
    boost::function< void() >               m_oFunc;
    unsigned int                            m_nMaxThreadNum;
    bool									m_bStopFlag;
};


CLOSE_NAMESPACE_SWITCHTOOL


#endif // SIMPLE_THREAD_LIST_HPP

