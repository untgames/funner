#include <syslib/timer.h>
#include <platform/platform.h>
#include <xtl/function.h>
#include <common/exception.h>
#include <time.h>

using namespace syslib;
using namespace common;

#ifdef _MSC_VER
  #pragma warning (disable : 4355) //'this' : used in base member initializer list
#endif

namespace
{

//����������� ���������� �����������, ��������� � ������ ���������� ���������
size_t milliseconds ()
{
  return size_t (clock () * 1000.0f / CLOCKS_PER_SEC);
}

}

/*
    �������� ���������� �������
*/

struct Timer::Impl
{
  Timer&            timer;      //������
  TickHandler       handler;    //���������� ������������ �������
  size_t            period;     //������ ������������ (� ������������)
  Platform::timer_t sys_timer;  //���������� ���������� �������
  size_t            start_time; //����� ������ �������
  
  Impl  (Timer& in_timer, const TickHandler& in_handler);
  ~Impl ();
  
  void SetTimer  (size_t period);
  void KillTimer ();
  
  static void TimerHandler (void*);
};

/*
    Impl
*/

Timer::Impl::Impl (Timer& in_timer, const TickHandler& in_handler)
  : timer (in_timer), handler (in_handler), period (0), sys_timer (0)
  {}

Timer::Impl::~Impl ()
{
  KillTimer ();
}

void Timer::Impl::SetTimer (size_t in_period)
{
  if (sys_timer && period == in_period)
    return;
    
  KillTimer ();  
  
  period = in_period;
  
  sys_timer  = Platform::CreateTimer (period, &TimerHandler, this);
  start_time = milliseconds ();  
}

void Timer::Impl::KillTimer ()
{
  if (!sys_timer)
    return;
    
  Platform::KillTimer (sys_timer);
  
  sys_timer = 0;
}

void Timer::Impl::TimerHandler (void* user_data)
{
  Impl* impl = (Impl*)user_data;

  impl->handler (impl->timer);
}

/*
    ����������� / ����������
*/

Timer::Timer (const TickHandler& in_handler, size_t period_in_milliseconds, TimerState initial_state)
  : impl (new Impl (*this, in_handler))
{
  SetPeriod (period_in_milliseconds);
  SetState (initial_state);
}

Timer::~Timer ()
{
  delete impl;
}

/*
    ����������
*/

const Timer::TickHandler& Timer::Handler () const
{
  return impl->handler;
}

/*
    ������
*/

size_t Timer::Period () const
{
  return impl->period;
}

void Timer::SetPeriod (size_t period_in_milliseconds)
{  
  impl->SetTimer (period_in_milliseconds);
}

/*
    ������������ / ������������� ������ �������
*/

void Timer::SetState (TimerState state)
{
  switch (state)
  {
    case TimerState_Running: impl->SetTimer (impl->period); break;
    case TimerState_Paused:  impl->KillTimer (); break;
    default:                 RaiseInvalidArgument ("syslib::Timer::SetState", "state", state); break;
  }
}

TimerState Timer::State () const
{
  return impl->sys_timer ? TimerState_Running : TimerState_Paused;
}

/*
    ���������� ����������, ��������� � ������� ������ �������
*/

size_t Timer::ElapsedMilliseconds () const
{
  return milliseconds () - impl->start_time;
}
