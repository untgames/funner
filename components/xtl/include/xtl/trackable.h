#ifndef XTL_TRACKABLE_HEADER
#define XTL_TRACKABLE_HEADER

#include <xtl/signal.h>

namespace xtl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, ����������� � ���� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class trackable
{
  public:
    typedef slot<void ()>     slot_type;
    typedef function<void ()> function_type;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    trackable  () {}
    trackable  (const trackable&) {}
    ~trackable ();

    trackable& operator = (const trackable&) { return *this; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/�������� ������������ �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    connection connect_tracker (const function_type& handler);
    connection connect_tracker (slot_type& handler);
    connection connect_tracker (const function_type& handler, trackable& owner);

    template <class Fn> void disconnect_tracker (Fn);

    void disconnect_all_trackers ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t num_trackers () const;

  private:
    typedef signal<void ()> signal_type;

  private:
    signal_type sig;
};

#include <xtl/detail/trackable.inl>

}

#endif
