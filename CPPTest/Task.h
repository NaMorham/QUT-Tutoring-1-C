#ifndef __AMH__TASK_H__
#define __AMH__TASK_H__

#include <time.h>

enum eTaskType
{
    TT_ACCOUNT,     // Account tasks
    TT_CUSTOMER,    // Customer Tasks
    TT_REPORT       // Reports
};

class Task
{
public:
    Task(const eTaskType type, const time_t lastRunTime, const time_t nextRunTime,
        const time_t repeatTime)
        : m_type(type), m_lastRunTime(lastRunTime), m_nextRunTime(nextRunTime), m_repeatTime(repeatTime) 
    {
    }
    virtual ~Task() { }

    // the implementation of these functions must be thread safe
    virtual const int PreTaskSetup() = 0;       // Any functionality that must be completed before the task (loading/collecting data from the store)
    virtual const int RunTask() = 0;            // The actual processing of the task
    virtual const int PostTaskCleanup() = 0;    // Any post task processing (commit to DB)

    virtual const int Execute()
    {
        int result = 0;
        result = PreTaskSetup();
        if (result != 0)
        {
            // Log it
            return result;
        }
        result = RunTask();
        if (result != 0)
        {
            // Log it
            return result;
        }
        result = PostTaskCleanup();
        if (result != 0)
        {
            // Log it
            return result;
        }
    }
private:
    eTaskType m_type;
    time_t m_lastRunTime;     // last time the task was run
    time_t m_nextRunTime;     // when the task is scheduled
    time_t m_repeatTime;      // if non 0 - when it will be next scheduled
};

#endif // __AMH__TASK_H__
