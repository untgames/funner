#ifndef COMMONLIB_THREAD_HEADER
#define COMMONLIB_THREAD_HEADER

#include <xtl/functional_fwd>

namespace common
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
const int THREAD_CANCELED_EXIT_CODE = -1; //�� ���������� ���������� ����

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Thread
{
  public:
    typedef xtl::function<int ()> Function;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Thread  ();
    Thread  (const Function& thread_function);
    Thread  (const char* name, const Function& thread_function);
    Thread  (const Thread&);
    ~Thread ();

    Thread& operator = (const Thread&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Cancel ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    int Join (); //return exit code

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Thread&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Thread GetCurrent ();

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Thread&, Thread&);

}

#endif
