#ifndef BOUND_VOLUMES_SPHERE_HEADER
#define BOUND_VOLUMES_SPHERE_HEADER

#include <mathlib.h>

namespace bound_volumes
{

//forward declarations
template <class T> class axis_aligned_box;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> class sphere
{
  public:
    typedef T               element_type;
    typedef math::vec<T, 3> vec_type;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    sphere ();
    sphere (const vec_type& center, const element_type& radius);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const vec_type& center () const;
    element_type    radius () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void set_radius  (const element_type&);
    void set_center  (const vec_type&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void reset (const vec_type& center = vec_type (0), const element_type& radius = element_type (0));

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� �������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    element_type volume () const; //�������������� ����� �����

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool empty (const element_type& eps = default_epsilon) const; //��������: r < eps

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� � �������������� �����
///  ���� ������� ������ < 0 - ���������� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    sphere& operator += (const vec_type&);
    sphere& operator += (const sphere&);
    sphere& operator += (const axis_aligned_box<T>&); //???
    sphere  operator +  (const vec_type&) const;
    sphere  operator +  (const sphere&) const;
    sphere  operator +  (const axis_aligned_box&) const; //???

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� �������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    sphere& operator *= (const math::matrix<T, 4>&);
    sphere& operator *= (const math::quat<T>&);
    sphere  operator *  (const math::matrix<T, 4>&) const;
    sphere  operator *  (const math::quat<T>&) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������� �������������� ����� � ���������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool intersects (const sphere&) const;
    bool intersects (const axis_aligned_box<T>&) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������: �������� �� �������������� ����� ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool contains (const vec_type& point) const;
    bool contains (const sphere& sphere) const;
    bool contains (const axis_aligned_box<T>& box) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool equal (const sphere&, const element_type& eps = default_epsilon) const;

    bool operator == (const sphere&) const;
    bool operator != (const sphere&) const;

  private:
    vec_type     sphere_center;
    element_type sphere_radius;    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef sphere<int>    spherei;
typedef sphere<float>  spheref;
typedef sphere<double> sphered;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� �������������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> sphere<T> operator * (const math::matrix<T, 4>&, const sphere<T>&);
template <class T> sphere<T> operator * (const math::quat<T>&, const sphere<T>&);

#include <bv/detail/sphere.inl>

}

#endif
