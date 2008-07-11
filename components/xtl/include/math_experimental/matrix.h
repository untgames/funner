#ifndef MATHLIB_MATRIX_HEADER
#define MATHLIB_MATRIX_HEADER
#include "forward.h"
#include "functional.h"
#include <stddef.h>


#ifdef _MSC_VER  
  #pragma pack(push,1)
#endif

#ifdef minor
#undef minor
#endif




namespace math
{

//forward declaration
template <class Type> class quat;
template <class Type, size_t Size> class vec;



/////////////////////////////////////////////////////////////////////////////////////////////
///�������
/////////////////////////////////////////////////////////////////////////////////////////////
template <class Type, size_t SizeX, size_t SizeY/*=SizeX*/>
class matrix
{
  public:
    typedef vec<Type, SizeY>              vector;     //������ ������
    typedef typename vector::value_type value_type; //��� ���������
    
    enum { size_y = SizeY, 
           size_x = SizeX,  
           size   = SizeX };

////////////////////////////////////////////////////////////////////////////////////////////
///�����������
////////////////////////////////////////////////////////////////////////////////////////////
    matrix ();
    matrix (const matrix& src);
    matrix (const Type& a);  //a ����� �������� �� ������� ���������
    matrix (const Type*);                                            
    
    template <class T1, class T2,  class Fn>
      matrix(const T1& a, const T2& b, Fn fn);

    template <class T1,  class Fn>
      matrix(const T1& src, Fn fn);


      //��� ������������� ����������� ������������� ��������
      template <class T1>           matrix (const T1&, void (*eval)(matrix&, const T1&));

////////////////////////////////////////////////////////////////////////////////////////////
///��������������
////////////////////////////////////////////////////////////////////////////////////////////
  const vec<Type, SizeX>  column  (size_t j) const;

        vector& operator [] (size_t index)       { return x [index]; }
  const vector& operator [] (size_t index) const { return x [index]; }

////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
  const matrix   operator -  () const;

////////////////////////////////////////////////////////////////////////////////////////////
///������������
////////////////////////////////////////////////////////////////////////////////////////////
//  matrix&  operator = (const quat<Type>&);  //������ ��� ������ 3-�� � 4-�� �������
    matrix&  operator = (const Type&);
    matrix&  operator = (const matrix&);

////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������������� ��������
////////////////////////////////////////////////////////////////////////////////////////////
    matrix&      operator += (const matrix&);
    matrix&      operator -= (const matrix&);
    matrix&	 operator *= (const Type& a);
    matrix&	 operator /= (const Type&);

    const matrix operator *  (const Type& a) const;
    const matrix operator /  (const Type&)   const; 


///////////////////////////////////////////////////////////////////////////////////////////

    const matrix operator +  (const matrix&) const;
    const matrix operator -  (const matrix&) const;

///////////////////////////////////////////////

    template<size_t Size2Y>  
     const matrix<Type, SizeX, Size2Y> operator *  (const matrix<Type, SizeY, Size2Y>&) const;

    template<class T, size_t Size>
     friend matrix<T, Size>&          operator *= (matrix<T, Size>&, const matrix<T, Size>&);

    template<class T, size_t Size>
     friend const matrix<T, Size>     operator /  (const matrix<T, Size>&, const matrix<T, Size>&);

    template<class T, size_t Size>
     friend matrix<T, Size>&	     operator /= (matrix<T, Size>&, const matrix<T, Size>&);

//////////////////////////////////////////////////////////////////////////////////////////

    friend const matrix operator * (const Type& a, const matrix& m) { return m*a; }

////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ���������
////////////////////////////////////////////////////////////////////////////////////////////
    bool operator == (const matrix&) const;
    bool operator != (const matrix&) const;             


////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������/�������
////////////////////////////////////////////////////////////////////////////////////////////
  
   const matrix<Type, SizeX-1, SizeY>   remove_row        (size_t)        const; 
   const matrix<Type, SizeX, SizeY-1>   remove_column     (size_t)        const;
   const matrix<Type, SizeX-1, SizeY-1> remove_row_column (size_t, size_t) const;

////////////////////////////////////////////////////////////////////////////////////////////
///���������������� �������
////////////////////////////////////////////////////////////////////////////////////////////
   const matrix<Type, SizeY, SizeX>  transpose ();

////////////////////////////////////////////////////////////////////////////////////////////
  private:
    vector x [SizeX];  

};


////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������� � ����������
////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
const quat<T> matrix_to_quat (const matrix<T, 3>&);

template <class T>
const quat<T> matrix_to_quat (const matrix<T, 4>&);


////////////////////////////////////////////////////////////////////////////////////////////
///������������
////////////////////////////////////////////////////////////////////////////////////////////

template<class T, size_t Size>
const T det (const matrix<T, Size, Size>&);

////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���
////////////////////////////////////////////////////////////////////////////////////////////
    
template<class T, size_t Size>
const matrix<T, Size, Size> three_angle_view  (const matrix<T, Size, Size>&, int&);

////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����������
////////////////////////////////////////////////////////////////////////////////////////////

template<class T, size_t Size>
const T mathematical_add (const matrix<T, Size>&,  size_t, size_t);

////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
////////////////////////////////////////////////////////////////////////////////////////////

template<class T, size_t Size>
const matrix<T, Size> invert (const matrix<T, Size>&);

////////////////////////////////////////////////////////////////////////////////////////////
///������������ �������
////////////////////////////////////////////////////////////////////////////////////////////

template<class T, size_t Size>
const matrix<T, Size> normalize (const matrix<T, Size>&);

////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����
////////////////////////////////////////////////////////////////////////////////////////////

typedef matrix<float,2,2>         mat2f;
typedef matrix<float,3,3>         mat3f;
typedef matrix<float,4,4>         mat4f;
typedef matrix<double,2,2>        mat2d;
typedef matrix<double,3,3>        mat3d;
typedef matrix<double,4,4>        mat4d;
typedef matrix<int,2,2>           mat2i;
typedef matrix<int,3,3>           mat3i;
typedef matrix<int,4,4>           mat4i;

#include <math_experimental/impl/matrix.inl>

#ifdef _MSC_VER
  #pragma pack(pop)
#endif

}



#endif
