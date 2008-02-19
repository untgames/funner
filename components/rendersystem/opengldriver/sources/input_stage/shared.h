#ifndef RENDER_GL_DRIVER_INPUT_STAGE_SHARED_HEADER
#define RENDER_GL_DRIVER_INPUT_STAGE_SHARED_HEADER

#include <common/exception.h>
#include <common/singleton.h>

#include <xtl/uninitialized_storage.h>
#include <xtl/trackable_ptr.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/array>

#include <stl/vector>
#include <stl/algorithm>

#include <render/low_level/utils.h>

#include <shared/input_stage.h>
#include <shared/context_object.h>
#include <shared/object.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Buffer: virtual public IBuffer, virtual public IBindableBuffer, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Buffer (const ContextManager&, const BufferDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool   IsVertexBuffer () const { return (desc.bind_flags & BindFlag_VertexBuffer) != 0; }
    bool   IsIndexBuffer  () const { return (desc.bind_flags & BindFlag_IndexBuffer) != 0; }
    size_t GetBindFlags   () const { return desc.bind_flags; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (BufferDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetData (size_t offset, size_t size, const void* data);
    void GetData (size_t offset, size_t size, void* data);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ������ ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetDataCore (size_t offset, size_t size, const void* data) = 0;
    virtual void GetDataCore (size_t offset, size_t size, void* data) = 0;

  private:
    BufferDesc desc; //���������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////    
typedef xtl::trackable_ptr<Buffer> BufferPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� � ��������� � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SystemMemoryBuffer: public Buffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SystemMemoryBuffer  (const ContextManager&, const BufferDesc&, bool need_hash = true); //????
    ~SystemMemoryBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    void* GetDataPointer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ������ (0 - ������ �� ����������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetDataHash ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ������ ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDataCore (size_t offset, size_t size, const void* data);
    void GetDataCore (size_t offset, size_t size, void* data);

  private:
    xtl::uninitialized_storage <char> buffer;                //����� � ��������� ������
    size_t                            data_hash;             //��� ������
    bool                              need_data_hash_recalc; //������ ����������
    bool                              need_hash;             //���������� �� �����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� � ��������� � ����������� � �������������� ���������� GL_ARB_vertex_buffer_object
///////////////////////////////////////////////////////////////////////////////////////////////////
class VboBuffer: public Buffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VboBuffer  (const ContextManager&, GLenum target, const BufferDesc&);
    ~VboBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///C������� �� ������ ������ (��� ���������� �������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void* GetDataPointer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ������ (0 - ������ �� ����������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetDataHash () { return 0; }

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ������ ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDataCore (size_t offset, size_t size, const void* data);
    void GetDataCore (size_t offset, size_t size, void* data);

  private:
    GLenum target;     //������� ��� ����������� ������ (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER)
    GLuint buffer_id;  //����� ������ � ��������� OpenGL
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputLayout: virtual public IInputLayout, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputLayout  (const ContextManager&, const InputLayoutDesc&, size_t tex_units_count);
    ~InputLayout ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDesc (const InputLayoutDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
//��������� ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
   void Bind (size_t         base_vertex,
              size_t         base_index,
              BufferPtr*     vertex_buffers,
              BufferPtr      index_buffer,
              IndicesLayout* out_indices_layout);

  private:
    struct GlVertexAttribute;
    struct GlVertexAttributeGroup;

    typedef stl::vector<GlVertexAttribute>      GlVertexAttributeArray;
    typedef stl::vector<GlVertexAttributeGroup> GlVertexAttributeGroupArray;

  private:
    GlVertexAttributeArray      vertex_attributes;       //��������� ��������
    GlVertexAttributeGroupArray vertex_attribute_groups; //������ ��������� ���������
    GLenum                      index_data_type;         //��� ��������
    size_t                      index_size;              //������ �������
    size_t                      index_buffer_offset;     //�������� � ��������� ������ �� ������� �������
    size_t                      tex_units_count;         //���������� ���������� ������ �������������� ���������
};

}

}

}

#endif
