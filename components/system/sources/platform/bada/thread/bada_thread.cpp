#include "../shared.h"

using namespace syslib;
using namespace syslib::bada;

namespace
{

class ThreadImpl : public Osp::Base::Runtime::Thread
{
  public:
    ThreadImpl (IThreadCallback* in_callback)
      : callback (in_callback)
      {}

    Osp::Base::Object* Run ()
    {
      callback->Run ();

      return 0;
    }

  private:
    xtl::com_ptr<IThreadCallback> callback;
};

}


struct Platform::thread_handle
{
  ThreadImpl* thread;

  ~thread_handle ()
  {
    delete thread;
  }
};

/*
    �������� / �������� ����
*/

Platform::thread_t Platform::CreateThread (IThreadCallback* in_callback)
{
  try
  {
      //�������� ������������ ����������, ������ ������� ������������ ����

    if (!in_callback)
      throw xtl::make_null_argument_exception ("", "callback");

    xtl::com_ptr<IThreadCallback> callback (in_callback);

      //�������� ����

    stl::auto_ptr<thread_handle> handle (new thread_handle);

    handle->thread = new ThreadImpl (callback.get ());

    result r = handle->thread->Construct ();

    if (IsFailed (r))
      raise ("Osp::Base::Runtime::Thread::Construct", r);

    r = handle->thread->Start ();

    if (IsFailed (r))
      raise ("Osp::Base::Runtime::Thread::Start", r);

    return handle.release ();
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("syslib::BadaPlatform::CreateThread");
    throw;
  }
}

void Platform::DestroyThread (thread_t thread)
{
  if (!thread)
    return;

  delete thread;
}

/*
    �������� ���������� ����
*/

void Platform::JoinThread (thread_t thread)
{
  try
  {
    if (!thread)
      throw xtl::make_null_argument_exception ("", "thread");

    result r = thread->thread->Join ();

    if (IsFailed (r))
      raise ("Osp::Base::Runtime::Thread::Join", r);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("syslib::BadaPlatform::JoinThread");
    throw;
  }
}

/*
   ��������� �������������� ����
*/

size_t Platform::GetThreadId (thread_t thread)
{
  return (size_t)thread->thread;
}

size_t Platform::GetCurrentThreadId ()
{
  return (size_t)Osp::Base::Runtime::Thread::GetCurrentThread ();
}