///
/// @file PropSharedLock.h
/// @brief base class to lock/unlock property data by multiple readers
/// @author Jun Jiang <jun.jiang@izenesoft.com>
/// @date Created 2012-06-25
///

#ifndef SF1R_PROP_SHARED_LOCK_H
#define SF1R_PROP_SHARED_LOCK_H

#include <boost/thread.hpp>


class PropSharedLock
{
public:
    typedef boost::shared_mutex MutexType;
    typedef boost::shared_lock<MutexType> ScopedReadLock;
    typedef boost::unique_lock<MutexType> ScopedWriteLock;

    class ScopedReadBoolLock;
    class ScopedWriteBoolLock;

    virtual ~PropSharedLock() {}

    MutexType& getMutex() const { return mutex_; }

    void lockShared() const { mutex_.lock_shared(); }

    void unlockShared() const { mutex_.unlock_shared(); }

protected:
    mutable MutexType mutex_;
};

class PropSharedLock::ScopedReadBoolLock
{
public:
    ScopedReadBoolLock(PropSharedLock::MutexType& mutex, bool isLock)
        : lock_(mutex, boost::defer_lock)
    {
        if (isLock)
        {
            lock_.lock();
        }
    }

private:
    PropSharedLock::ScopedReadLock lock_;
};

class PropSharedLock::ScopedWriteBoolLock
{
public:
    ScopedWriteBoolLock(PropSharedLock::MutexType& mutex, bool isLock)
        : lock_(mutex, boost::defer_lock)
    {
        if (isLock)
        {
            lock_.lock();
        }
    }

private:
    PropSharedLock::ScopedWriteLock lock_;
};


#endif // SF1R_PROP_SHARED_LOCK_H
