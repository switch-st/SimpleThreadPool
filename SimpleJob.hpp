#ifndef SIMPLE_JOB_HPP
#define SIMPLE_JOB_HPP

/**
 * 任务相关类实现
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


enum SimpleJobStatus
{
    SJS_INIT,               // 任务创建
    SJS_WAIT,               // 等待运行
    SJS_CALL,               // 运行中
    SJS_DONE                // 运行结束
};

/// T是回调函数返回值类型
template < typename T = int >
class SimpleJob
{
public:
	SimpleJob() {}
    template < typename FUNC >
    SimpleJob(FUNC func)
    {
        m_oFunc = boost::bind(func);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1 >
    SimpleJob(FUNC func, T1 t1)
    {
        m_oFunc = boost::bind(func, t1);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2 >
    SimpleJob(FUNC func, T1 t1, T2 t2)
    {
        m_oFunc = boost::bind(func, t1, t2);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3)
    {
        m_oFunc = boost::bind(func, t1, t2, t3);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7, t8);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7, t8, t9);
        m_eStat = SJS_WAIT;
    }

    SimpleJob(const SimpleJob< T >& job)
    {
    	m_oFunc = job.m_oFunc;
    	m_eStat = job.m_eStat;
    }

	SimpleJob< T >& operator=(const SimpleJob< T >& job)
	{
    	m_oFunc = job.m_oFunc;
    	m_eStat = job.m_eStat;

    	return *this;
	}

    T CallJob(void)
    {
        m_oMutex.lock();
        m_eStat = SJS_CALL;
        m_oMutex.unlock();

        m_tRetVal = m_oFunc();

        m_oMutex.lock();
        m_eStat = SJS_DONE;
        m_oMutex.unlock();

        return m_tRetVal;
    }

    bool GetReturnValue(T& val)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        if (m_eStat >= SJS_DONE)
        {
            val = m_tRetVal;
            return true;
        }

        return false;
    }

    SimpleJobStatus GetJobStatus(void)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_eStat;
    }

private:
    boost::function< T() >              m_oFunc;
    boost::mutex                        m_oMutex;
    SimpleJobStatus                     m_eStat;
    T                                   m_tRetVal;
};

template <>
class SimpleJob < void >
{
public:
	SimpleJob() {}
    template < typename FUNC >
    SimpleJob(FUNC func)
    {
        m_oFunc = boost::bind(func);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1 >
    SimpleJob(FUNC func, T1 t1)
    {
        m_oFunc = boost::bind(func, t1);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2 >
    SimpleJob(FUNC func, T1 t1, T2 t2)
    {
        m_oFunc = boost::bind(func, t1, t2);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3)
    {
        m_oFunc = boost::bind(func, t1, t2, t3);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7, t8);
        m_eStat = SJS_WAIT;
    }
    template < typename FUNC, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9 >
    SimpleJob(FUNC func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9)
    {
        m_oFunc = boost::bind(func, t1, t2, t3, t4, t5, t6, t7, t8, t9);
        m_eStat = SJS_WAIT;
    }

    SimpleJob(const SimpleJob< void >& job)
    {
    	m_oFunc = job.m_oFunc;
    	m_eStat = job.m_eStat;
    }

	SimpleJob< void >& operator=(const SimpleJob< void >& job)
	{
    	m_oFunc = job.m_oFunc;
    	m_eStat = job.m_eStat;

    	return *this;
	}

    void CallJob(void)
    {
        m_oMutex.lock();
        m_eStat = SJS_CALL;
        m_oMutex.unlock();

        m_oFunc();

        m_oMutex.lock();
        m_eStat = SJS_DONE;
        m_oMutex.unlock();
    }

    SimpleJobStatus GetJobStatus(void)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_eStat;
    }

private:
    boost::function< void() >           m_oFunc;
    boost::mutex                        m_oMutex;
    SimpleJobStatus                     m_eStat;

};


class SimpleJobList : public boost::noncopyable
{
public:
    typedef std::list< SimpleJob< void > >::iterator iterator;

public:
    SimpleJobList(void)
    {
        m_nMaxJobNum = 0;
        m_bStopFlag = false;
    }

    SimpleJobList(unsigned int max)
    {
        m_nMaxJobNum = max;
        m_bStopFlag = false;
    }

    bool set_max_job_num(unsigned int max)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        if (max <= m_nMaxJobNum)
        {
            return false;
        }
        m_nMaxJobNum = max;

        return true;
    }

    int get_max_job_num(void)
    {
		boost::lock_guard< boost::mutex > guard(m_oMutex);
		return m_nMaxJobNum;
    }

	int get_current_job_num(void)
    {
		boost::lock_guard< boost::mutex > guard(m_oMutex);
		return m_lJobList.size();
    }

    bool push_back(const SimpleJob< void >& job)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        if (m_bStopFlag || m_lJobList.size() >= m_nMaxJobNum)
        {
            return false;
        }

        m_lJobList.push_back(job);

        return true;
    }

    bool pop_front(SimpleJob< void >& job)
    {
		boost::lock_guard< boost::mutex > guard(m_oMutex);

		if (!m_bStopFlag || m_lJobList.size() > 0)
		{
			job = m_lJobList.front();
			m_lJobList.pop_front();

			return true;
		}

		return false;
    }

    iterator begin()
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_lJobList.begin();
    }

    iterator end()
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_lJobList.end();
    }

    iterator erase(iterator iter)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_lJobList.erase(iter);
    }

    iterator erase(iterator begin, iterator end)
    {
        boost::lock_guard< boost::mutex > guard(m_oMutex);

        return m_lJobList.erase(begin, end);
    }

    void stop(void)
    {
    	boost::lock_guard< boost::mutex > guard(m_oMutex);
    	m_bStopFlag = true;
		notify_all_add_job();
		notify_all_get_job();
    }

	void lock_add_job(void)
	{
		m_oFullMutex.lock();
	}
	void unlock_add_job(void)
	{
		m_oFullMutex.unlock();
	}
	bool can_add_job(void)
    {
    	boost::lock_guard< boost::mutex > guard(m_oMutex);
		return m_bStopFlag || m_nMaxJobNum > m_lJobList.size();
    }
    void wait_add_job(void)
    {
		m_oFullCond.wait(m_oFullMutex, boost::bind(&SimpleJobList::can_add_job, this));
    }
    void notify_one_add_job(void)
    {
    	m_oFullCond.notify_one();
    }
    void notify_all_add_job(void)
    {
    	m_oFullCond.notify_all();
    }
	void lock_get_job(void)
	{
		m_oEmptyMutex.lock();
	}
	void unlock_get_job(void)
	{
		m_oEmptyMutex.unlock();
	}
	bool can_get_job(void)
	{
		boost::lock_guard< boost::mutex > guard(m_oMutex);
        return m_bStopFlag || m_lJobList.size() > 0;
	}
    void wait_get_job(void)
    {
		m_oEmptyCond.wait(m_oEmptyMutex, boost::bind(&SimpleJobList::can_get_job, this));
    }
    void notify_one_get_job(void)
    {
    	m_oEmptyCond.notify_one();
    }
    void notify_all_get_job(void)
    {
    	m_oEmptyCond.notify_all();
    }

private:
    std::list< SimpleJob< void > >				m_lJobList;
    boost::mutex                                m_oMutex;
    boost::mutex                                m_oFullMutex;
    boost::condition							m_oFullCond;
    boost::mutex                                m_oEmptyMutex;
    boost::condition							m_oEmptyCond;
    unsigned int								m_nMaxJobNum;
    bool										m_bStopFlag;
};


CLOSE_NAMESPACE_SWITCHTOOL


#endif // SIMPLE_JOB_HPP

