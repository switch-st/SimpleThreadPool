#ifndef SIMPLE_JOB_HPP
#define SIMPLE_JOB_HPP

/**
 * 欢迎补充！
 **/

#include <list>
#include <boost/thread.hpp>
#include <boost/thread/condition.hpp>
#include <boost/type_traits.hpp>
#include <boost/bind.hpp>

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
template < typename T >
class SimpleJob
{
public:
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
        bool flag = false;

        m_oMutex.lock();
        if (m_eStat >= SJS_DONE)
        {
            flag = true;
            val = m_tRetVal;
        }
        m_oMutex.unlock();

        return flag;
    }

    SimpleJobStatus GetJobStatus(void)
    {
        return m_eStat;
    }

private:
    boost::function< T() >              m_oFunc;
    boost::mutex                        m_oMutex;
    boost::condition                    m_oCond;
    SimpleJobStatus                     m_eStat;
    T                                   m_tRetVal;

};

template < >
class SimpleJob < void >
{
public:
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
        return m_eStat;
    }

private:
    boost::function< void() >           m_oFunc;
    boost::mutex                        m_oMutex;
    boost::condition                    m_oCond;
    SimpleJobStatus                     m_eStat;

};


class SimpleJobList
{
public:
    SimpleJobList(void);





private:





};



















CLOSE_NAMESPACE_SWITCHTOOL



#endif // SIMPLE_JOB_HPP

