/*
    MySTL auto_ptr
*/

#ifndef MYSTL_AUTO_PTR_HEADER
#define MYSTL_AUTO_PTR_HEADER

#include <cstddef>

#include <stl/config.h>

namespace stl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ��� ���������� auto_ptr
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> 
struct auto_ptr_ref
{
  auto_ptr_ref (T* p);

  T* ptr;  
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������-���������, ��������������� ��� ������ � "��������" ������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class auto_ptr
{
  typedef T* (auto_ptr::*unspecified_bool_type)() const throw ();
  public:
    typedef T element_type;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    explicit auto_ptr  (element_type* = 0) throw ();
             auto_ptr  (auto_ptr&) throw ();
             auto_ptr  (auto_ptr_ref<T>) throw ();
             ~auto_ptr ();
             
    template <class T1> auto_ptr (auto_ptr<T1>&) throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    auto_ptr& operator = (auto_ptr&) throw ();
    auto_ptr& operator = (auto_ptr_ref<T>) throw ();
    
    template <class T1> auto_ptr& operator = (auto_ptr<T1>&) throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� � ����������� auto_ptr<T>
///////////////////////////////////////////////////////////////////////////////////////////////////
    template <class T1> operator auto_ptr_ref<T1> () throw ();
    template <class T1> operator auto_ptr<T1> () throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    element_type& operator *  () const throw ();
    element_type* operator -> () const throw ();
    element_type* get         () const throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� 0
///////////////////////////////////////////////////////////////////////////////////////////////////
    operator unspecified_bool_type () const throw () { return ptr ? &auto_ptr::get : 0; } //������� ���������� ���� ��� �������� if (p)
    bool     operator !            () const throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �� �������� (������ �� ���������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    element_type* release () throw ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void reset (element_type* = 0) throw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void swap (auto_ptr&);

  private:
    T* ptr;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
void swap (auto_ptr<T>&, auto_ptr<T>&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������� ��������� (������������� �������)
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> T* get_pointer (const auto_ptr<T>&);

#include <stl/detail/auto_ptr.inl>

}

#endif
