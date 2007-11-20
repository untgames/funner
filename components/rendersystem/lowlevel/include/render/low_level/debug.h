#ifndef RENDER_LOW_LEVEL_DEBUG_HEADER
#define RENDER_LOW_LEVEL_DEBUG_HEADER

#include <stddef.h>

namespace render
{

namespace low_level
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ���������� � ���������� ������� 
///////////////////////////////////////////////////////////////////////////////////////////////////
class IPropertyList
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t GetSize () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� � ��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const char* GetKey   (size_t index) = 0;
    virtual const char* GetValue (size_t index) = 0;

  protected:
    virtual ~IPropertyList () {}

  private:
    IPropertyList& operator = (const IPropertyList&); //no impl
};

}

}

#endif
