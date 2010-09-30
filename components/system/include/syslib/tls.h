#ifndef SYSLIB_TLS_HEADER
#define SYSLIB_TLS_HEADER

namespace syslib
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ThreadLocalStorage
{
  public:
    typedef xtl::function<void (void* data)> CleanupHandler;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ThreadLocalStorage  ();
    ThreadLocalStorage  (const CleanupHandler& cleanup);
    ThreadLocalStorage  (void (*cleanup)(void*));
    ~ThreadLocalStorage ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetValue (void* data);
    void* GetValue () const;

  private:
    ThreadLocalStorage (const ThreadLocalStorage&); //no impl
    ThreadLocalStorage& operator = (const ThreadLocalStorage&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

#endif
