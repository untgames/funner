#ifndef MEDIALIB_GEOMETRY_INDEX_BUFFER_HEADER
#define MEDIALIB_GEOMETRY_INDEX_BUFFER_HEADER

#include <media/geometry/defs.h>

namespace medialib
{

namespace geometry
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class IndexBuffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IndexBuffer  ();
    IndexBuffer  (size_t indices_count);
    IndexBuffer  (const IndexBuffer&, CloneMode mode = CloneMode_Default);
    ~IndexBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void         Assign     (const IndexBuffer&, CloneMode mode = CloneMode_Default);
    IndexBuffer& operator = (const IndexBuffer&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const size_t* Data () const;
          size_t* Data ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size   () const;
    void   Resize (size_t indices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Capacity () const;
    void   Reserve  (size_t indices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (IndexBuffer&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (IndexBuffer&, IndexBuffer&);

}

}

#endif
