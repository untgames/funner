#ifndef SYSLIB_MUTEX_HEADER
#define SYSLIB_MUTEX_HEADER

#include <stl/auto_ptr.h>

namespace syslib
{

//implementation forwards
class Condition;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Mutex
{
  friend class Condition;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Mutex  ();
    ~Mutex ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool TryLock ();
    void Lock    ();
    bool TryLock (size_t wait_in_milliseconds);
    void Lock    (size_t wait_in_milliseconds);
    void Unlock  ();

  private:
    Mutex  (const Mutex&); //no impl
    Mutex& operator = (const Mutex&); //no impl
    
    void* Handle ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Lock
{
  public:
    Lock  (Mutex& in_Mutex);
    ~Lock ();

  private:
    Lock (const Lock&); //no impl
    Lock& operator = (const Lock&); //no impl
    
  private:
    Mutex& mutex;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��� �������������� � XTL
///////////////////////////////////////////////////////////////////////////////////////////////////
void lock   (Mutex&);
void unlock (Mutex&);

#include <syslib/detail/mutex.inl>

}

#endif
