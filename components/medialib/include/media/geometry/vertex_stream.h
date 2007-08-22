#ifndef MEDIALIB_GEOMETRY_VERTEX_STREAM_HEADER
#define MEDIALIB_GEOMETRY_VERTEX_STREAM_HEADER

#include <media/geometry/defs.h>
#include <media/geometry/vertex_format.h>

namespace medialib
{

namespace geometry
{

//forward declarations
class VertexBuffer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class VertexDeclaration
{
  public:
    VertexDeclaration (const VertexFormat&);
    VertexDeclaration (const VertexFormat&, size_t vertex_size);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const VertexFormat& Format     () const;
    size_t              VertexSize () const;

  private:
    const VertexFormat* format;
    size_t              vertex_size;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Vertex> VertexDeclaration make_vertex_declaration ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class VertexStream
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VertexStream  (const VertexDeclaration& declaration);
    VertexStream  (size_t vertices_count, const VertexDeclaration& declaration);
    VertexStream  (const VertexBuffer& source);
    VertexStream  (const VertexStream& source, const VertexDeclaration& declaration);
    VertexStream  (const VertexBuffer& source, const VertexDeclaration& declaration);
    VertexStream  (const VertexStream&, BufferCloneMode mode = BufferCloneMode_Default);
    ~VertexStream ();
    
    template <class Vertex> VertexStream (size_t);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VertexStream& operator = (const VertexStream&);
    VertexStream& operator = (const VertexBuffer&);
    void          Assign     (const VertexStream&, BufferCloneMode mode = BufferCloneMode_Default);    
    void          Assign     (const VertexBuffer&);
    void          Assign     (const VertexStream&, const VertexDeclaration& declaration);
    void          Assign     (const VertexBuffer&, const VertexDeclaration& declaration);

//////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const VertexFormat& Format () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t VertexSize () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* Data () const;
          void* Data ();
          
    template <class Vertex> const Vertex* Data () const;
    template <class Vertex>       Vertex* Data ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size   () const;
    void   Resize (size_t vertices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Capacity () const;
    void   Reserve  (size_t vertices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (VertexStream&);

  private:
    void Convert (const VertexStream&);
    void Convert (const VertexBuffer&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (VertexStream&, VertexStream&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���
///////////////////////////////////////////////////////////////////////////////////////////////////
struct VertexWeight
{
  size_t joint_index;  //������ ����������
  float  joint_weight; //��� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class VertexWeightStream
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VertexWeightStream  ();
    VertexWeightStream  (size_t weights_count);
    VertexWeightStream  (const VertexWeightStream&, BufferCloneMode mode = BufferCloneMode_Default);
    ~VertexWeightStream ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VertexWeightStream& operator = (const VertexWeightStream&);
    void                Assign     (const VertexWeightStream&, BufferCloneMode mode = BufferCloneMode_Default);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const VertexWeight* Data () const;
          VertexWeight* Data ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size   () const;
    void   Resize (size_t weights_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Capacity () const;
    void   Reserve  (size_t weights_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (VertexWeightStream&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (VertexWeightStream&, VertexWeightStream&);

#include <media/geometry/detail/vertex_stream.inl>

}

}

#endif
