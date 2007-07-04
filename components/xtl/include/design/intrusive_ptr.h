#ifndef DESIGN_INTRUSIVE_POINTER_HEADER
#define DESIGN_INTRUSIVE_POINTER_HEADER

#include <design/smart_ptr.h>

namespace design
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ��������� ������ �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
struct default_intrusive_strategy
{
  static T*   clone   (T* ptr);
  static void release (T* ptr);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ��������� ������ ������� �������� COM-���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
struct com_intrusive_strategy
{
  static T*   clone   (T* ptr);
  static void release (T* ptr);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������������� ��������� �� ������ ��������� ������ ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T,class Strategy=default_intrusive_strategy<T> >
class intrusive_ptr: public smart_ptr_storage<T*>
{
  typedef smart_ptr_storage<T*> base;
  public:
    typedef typename base::element_type element_type;
    typedef element_type*               pointer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    intrusive_ptr  () {}
    intrusive_ptr  (element_type*,bool addref = true);
    intrusive_ptr  (const intrusive_ptr&);
    ~intrusive_ptr ();

    template <class T1> intrusive_ptr (const intrusive_ptr<T1,Strategy>&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    intrusive_ptr& operator = (element_type*);
    intrusive_ptr& operator = (const intrusive_ptr&);

    template <class T1> intrusive_ptr& operator = (const intrusive_ptr<T1,Strategy>&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    using base::operator *;
    using base::operator ->;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    using base::swap;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �� ������ ������� COM-��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class com_ptr: public intrusive_ptr<T,com_intrusive_strategy<T> >
{
  typedef intrusive_ptr<T,com_intrusive_strategy<T> > base;
  public:
    typedef typename base::element_type element_type;

    com_ptr ();
    com_ptr (element_type*,bool addref = true);
    com_ptr (const com_ptr&);

    template <class T1> com_ptr (const com_ptr<T1>&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T1,class T2,class Strategy>
intrusive_ptr<T1,Strategy> static_pointer_cast (const intrusive_ptr<T2,Strategy>&);

template <class T1,class T2,class Strategy>
intrusive_ptr<T1,Strategy> const_pointer_cast (const intrusive_ptr<T2,Strategy>&);

template <class T1,class T2,class Strategy>
intrusive_ptr<T1,Strategy> dynamic_pointer_cast (const intrusive_ptr<T2,Strategy>&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T,class Strategy>
void swap (intrusive_ptr<T,Strategy>&,intrusive_ptr<T,Strategy>&);

template <class T>
void swap (com_ptr<T>&,com_ptr<T>&);

#include <design/impl/ptr_intrusive.inl>

}

#endif
