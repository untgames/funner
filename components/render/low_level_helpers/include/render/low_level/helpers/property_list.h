#ifndef RENDER_LOW_LEVEL_HELPERS_PROPERTY_LIST_HEADER
#define RENDER_LOW_LEVEL_HELPERS_PROPERTY_LIST_HEADER

#include <stl/auto_ptr.h>

#include <render/low_level/debug.h>

namespace render
{

namespace low_level
{

namespace helpers
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class PropertyList: virtual public IPropertyList
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PropertyList ();
    ~PropertyList ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetSize ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� � ��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetKey   (size_t index);
    const char* GetValue (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t AddProperty   (const char* key, const char* value);
    void   RemovePropery (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

  private:
    PropertyList (const PropertyList&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DefaultPropertyList: virtual public IPropertyList
{
  public:    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetSize ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� � ��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetKey   (size_t index);
    const char* GetValue (size_t index);
};

}

}

}

#endif
