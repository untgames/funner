#ifndef COMMON_ASYNC_HEADER
#define COMMON_ASYNC_HEADER

#include <xtl/exception.h>
#include <xtl/functional_fwd>
#include <xtl/singleton_default.h>

namespace common
{

namespace detail
{

class IAsyncAction;
class IAsyncResult;

}

//forward declaration
class AsyncResult;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> struct AsyncResultType       { typedef T&   Type; };
template <>        struct AsyncResultType<void> { typedef void Type; };

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Ret> AsyncResult async_invoke (const xtl::function<Ret ()>&);
template <class Ret> AsyncResult async_invoke (const xtl::function<Ret ()>&, const xtl::function<void (AsyncResult&)>& callback);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AsyncResult
{
  template <class Ret> friend AsyncResult async_invoke (const xtl::function<Ret ()>&);
  template <class Ret> friend AsyncResult async_invoke (const xtl::function<Ret ()>&, const xtl::function<void (AsyncResult&)>& callback);
  public:
    typedef xtl::function<void (AsyncResult&)> CallbackHandler;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AsyncResult  ();
    AsyncResult  (const AsyncResult&);
    ~AsyncResult ();

    AsyncResult& operator = (const AsyncResult&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������� �������� / �������� ���������� �������� / ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsCompleted   () const;
    void WaitCompleted ();

    template <class Ret> typename AsyncResultType<Ret>::Type  Result ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (AsyncResult&);
    
  private:
    struct Impl;
  
    AsyncResult (Impl*);
    AsyncResult (detail::IAsyncAction*);
    AsyncResult (detail::IAsyncAction*, const CallbackHandler&);
    
    detail::IAsyncResult* Result ();

  private:
    Impl* impl;
};

template <>
AsyncResultType<void>::Type AsyncResult::Result<void> ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (AsyncResult&, AsyncResult&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������, ����������� ��� ���������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class AsyncException: virtual public xtl::exception
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AsyncException  ();
    AsyncException  (const std::exception&);
    AsyncException  (const AsyncException&);
    ~AsyncException () throw ();
    
    AsyncException& operator = (const AsyncException&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� �������� xtl::exception
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* what   () const throw ();
    void        vtouch (const char* format, va_list args) throw ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (AsyncException&);
  
  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (AsyncException&, AsyncException&);

#include <common/detail/async.inl>

}

#endif