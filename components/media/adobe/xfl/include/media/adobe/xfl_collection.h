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
///������ � �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const Item& operator [] (size_t index) const = 0;
    virtual       Item& operator [] (size_t index) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t Capacity () const = 0;
    virtual void   Reserve  (size_t count) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t Add (Item&) = 0;

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Item> class INamedCollection: public ICollection<Item>
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������� �� ����� (� ������ ���������� - ����������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Item&       operator [] (const char* name) = 0;
    virtual const Item& operator [] (const char* name) const = 0;
    
    using ICollection<Item>::operator [];

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� �� ����� (� ������ ���������� ���������� 0)
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Item*       Find (const char* name) = 0;
    virtual const Item* Find (const char* name) const = 0;
};

}

}

}

#endif
