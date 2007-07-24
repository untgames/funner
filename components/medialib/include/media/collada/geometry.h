#ifndef MEDIALIB_COLLADA_GEOMETRY_HEADER
#define MEDIALIB_COLLADA_GEOMETRY_HEADER

#include <media/collada/material.h>
#include <math/mathlib.h>

namespace medialib
{

namespace collada
{

//forward declarations
class Mesh;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef ILibrary<Mesh> MeshLibrary;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Vertex
{
  math::vec3f coord;    //���������� �������
  math::vec3f normal;   //������� � �������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TexVertex
{
  math::vec3f coord;    //���������� ���������� �������
  math::vec3f tangent;  //����������� � texture space
  math::vec3f binormal; //��������� � texture space
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum PrimitiveType
{
  PrimitiveType_LineList,      //������ ��������
  PrimitiveType_LineStrip,     //������� ��������
  PrimitiveType_TriangleList,  //������ �������������
  PrimitiveType_TriangleStrip, //������� �������������
  PrimitiveType_TriangleFan    //����� �������������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Surface
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
          collada::Material& Material ();
    const collada::Material& Material () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    collada::PrimitiveType PrimitiveType () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t VerticesCount () const;
    size_t IndicesCount  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
          Vertex* Vertices ();
    const Vertex* Vertices () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      ColorChannelsCount     () const;                 //���������� ������� ��������� ������
    size_t      CreateColorChannel     (const char* name = 0);   //�������� ������ ��������� ������
    void        RemoveColorChannel     (size_t channel);         //�������� ������ ��������� ������
    void        RemoveAllColorChannels ();                       //�������� ���� ������� ��������� ������
    const char* ColorChannelName       (size_t channel) const;   //��� ������ ��������� ������    
    bool        HasColorChannel        (size_t channel) const;   //�������� ������� ������ ��������� ������    
    int         FindColorChannel       (const char* name) const; //���������� ������ ������ ��������� ������ ��� -1 � ������ �������

          math::vec3f* Colors (size_t channel);
    const math::vec3f* Colors (size_t channel) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      TextureChannelsCount     () const;                 //���������� ������� ���������������
    size_t      CreateTextureChannel     (const char* name = 0);   //�������� ������ ���������������
    void        RemoveTextureChannel     (size_t channel);         //�������� ������ ���������������
    void        RemoveAllTextureChannels ();                       //�������� ���� ������ ���������������
    const char* TextureChannelName       (size_t channel) const;   //��� ����������������� ������    
    bool        HasTextureChannel        (size_t channel) const;   //�������� ������� ������ ���������������
    int         FindTextureChannel       (const char* name) const; //���������� ������ ������ ��������������� ��� -1 � ������ �������

      //���������������� �������
    const TexVertex* TextureVertices (size_t channel) const;    
          TexVertex* TextureVertices (size_t channel);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
          size_t* Indices ();
    const size_t* Indices () const;

  protected:
    Surface  (collada::Material& material, collada::PrimitiveType type, size_t verts_count, size_t indices_count);
    ~Surface ();

  private:
    Surface (const Surface&); //no impl
    Surface& operator = (const Surface&); //no impl

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <> class ICollection<Surface>: public IItemCollection<Surface>
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual Surface& Create (Material& material, PrimitiveType type, size_t verts_count, size_t indices_count) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
class Mesh: public Entity
{
  public:
    typedef ICollection<Surface> SurfaceList;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
          SurfaceList& Surfaces ();
    const SurfaceList& Surfaces () const;

  protected:
    Mesh (MeshLibrary& library, const char* id);

  private:
    struct Impl;
    Impl* impl;
};

}

}

#endif
