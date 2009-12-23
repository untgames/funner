#ifndef MEDIALIB_ADOBE_XFL_COLLECTION_HEADER
#define MEDIALIB_ADOBE_XFL_COLLECTION_HEADER

#include <cstddef>

namespace xtl
{

//forward declaration
template <class T> class iterator;

}

namespace media
{

namespace adobe
{

namespace xfl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Item> class ICollection
{
  public:
    typedef xtl::iterator<Item>       Iterator;
    typedef xtl::iterator<const Item> ConstIterator;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� / �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t Size    () const = 0;
    virtual bool   IsEmpty () const = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Iterator      CreateIterator () = 0;
    virtual ConstIterator CreateIterator () const = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t Insert (Item&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Remove (size_t index) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Clear () = 0;
    
  protected:
    virtual ~ICollection () {}
};

}

}

}

#endif
