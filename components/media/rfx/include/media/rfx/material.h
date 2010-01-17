#ifndef MEDIALIB_RFX_MATERIAL_HEADER
#define MEDIALIB_RFX_MATERIAL_HEADER

#include <common/property_map.h>

namespace media
{

namespace rfx
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Material
{  
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Material  ();
    Material  (const Material&);
    ~Material ();

    Material& operator = (const Material&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Material Clone () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name     () const;
    void        SetName  (const char* name);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetEffect (const char* name);
    const char* Effect    () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
          common::PropertyMap& Properties ();
    const common::PropertyMap& Properties () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Material&);

  private:
    struct Impl;
    
    Material (Impl*);
    
  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Material&, Material&);

}

}

#endif
