#ifndef COMMON_PROPERTY_MAP_HEADER
#define COMMON_PROPERTY_MAP_HEADER

#include <stl/string_fwd>

#include <xtl/intrusive_ptr.h>

namespace math
{

//forward declarations
template <class T, unsigned int Size> class vector;
template <class T, unsigned int Size> class matrix;

typedef vector<float, 4> vec4f;
typedef matrix<float, 4> mat4f;

}

namespace common
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum PropertyType
{
  PropertyType_String,
  PropertyType_Integer,
  PropertyType_Float,
  PropertyType_Vector,  
  PropertyType_Matrix, 

  PropertyType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
const char* get_name (PropertyType);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class PropertyMap
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PropertyMap  ();
    ~PropertyMap ();
    PropertyMap  (const PropertyMap&);
    
    PropertyMap& operator = (const PropertyMap&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PropertyMap Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Hash          () const; //���������� DataHash � StructureHash
    size_t DataHash      () const; //��� ������
    size_t StructureHash () const; //��� ��������� ����������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* PropertyName    (size_t index) const;
    void        SetPropertyName (size_t index, const char* name);
    void        SetPropertyName (const char* old_name, const char* new_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PropertyType PropertyType (size_t index) const;
    common::PropertyType PropertyType (const char* name) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetPropertyType (size_t index, common::PropertyType type);
    void SetPropertyType (const char* name, common::PropertyType type);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    int  IndexOf   (const char* name) const;
    bool IsPresent (const char* name) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetProperty (const char* name, const char* value);
    void SetProperty (const char* name, const stl::string& value);
    void SetProperty (const char* name, int value);
    void SetProperty (const char* name, float value);    
    void SetProperty (const char* name, const math::vec4f& value);   
    void SetProperty (const char* name, const math::mat4f& value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetProperty (size_t property_index, const char* value);
    void SetProperty (size_t property_index, const stl::string& value);
    void SetProperty (size_t property_index, int value);
    void SetProperty (size_t property_index, float value);
    void SetProperty (size_t property_index, const math::vec4f& value);    
    void SetProperty (size_t property_index, const math::mat4f& value);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetProperty (const char* name, stl::string& result) const;
    void GetProperty (const char* name, int& result) const;
    void GetProperty (const char* name, float& result) const;
    void GetProperty (const char* name, math::vec4f& result) const;
    void GetProperty (const char* name, math::mat4f& result) const;

    const char*        GetString  (const char* name) const;
    int                GetInteger (const char* name) const;
    float              GetFloat   (const char* name) const;
    const math::vec4f& GetVector  (const char* name) const;
    const math::mat4f& GetMatrix  (const char* name) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetProperty (size_t property_index, stl::string& result) const;
    void GetProperty (size_t property_index, int& result) const;
    void GetProperty (size_t property_index, float& result) const;
    void GetProperty (size_t property_index, math::vec4f& result) const;
    void GetProperty (size_t property_index, math::mat4f& result) const;

    const char*        GetString  (size_t property_index) const;
    int                GetInteger (size_t property_index) const;
    float              GetFloat   (size_t property_index) const;
    const math::vec4f& GetVector  (size_t property_index) const;
    const math::mat4f& GetMatrix  (size_t property_index) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RemoveProperty (const char* name);
    void RemoveProperty (size_t index);
    void Clear          ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (PropertyMap&);
    
  private:
    struct Impl;  

    PropertyMap (Impl*);

  private:
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (PropertyMap&, PropertyMap&);

}

#endif
