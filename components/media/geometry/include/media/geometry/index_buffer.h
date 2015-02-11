#ifndef MEDIALIB_GEOMETRY_INDEX_BUFFER_HEADER
#define MEDIALIB_GEOMETRY_INDEX_BUFFER_HEADER

#include <media/geometry/defs.h>
#include <xtl/intrusive_ptr.h>

namespace media
{

namespace geometry
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum IndexType
{
  IndexType_UInt32,
  IndexType_UInt16,
  IndexType_UInt8,  
  
  IndexType_Num,
  
  IndexType_Default = IndexType_UInt32
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
const char*   get_index_type_name (IndexType); //��� ����
unsigned char get_index_type_size (IndexType); //������ �������

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
    IndexBuffer  (uint32_t indices_count, IndexType type = IndexType_Default);
    IndexBuffer  (const IndexBuffer&);
    IndexBuffer  (const IndexBuffer&, IndexType type);
    ~IndexBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IndexBuffer& operator = (const IndexBuffer&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    IndexBuffer Clone () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ������ (����������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IndexType DataType    () const;
    void      SetDataType (IndexType type);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* Data () const;
          void* Data ();
          
    template <class T> const T* Data () const;
    template <class T>       T* Data ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    uint32_t Size   () const;
    void     Resize (uint32_t indices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    uint32_t Capacity () const;
    void     Reserve  (uint32_t indices_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (IndexBuffer&);

  private:
    struct Impl;

    IndexBuffer (Impl*);

  private:
    xtl::intrusive_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (IndexBuffer&, IndexBuffer&);

#include <media/geometry/detail/index_buffer.inl>

}

}

#endif
