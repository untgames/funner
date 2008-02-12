#ifndef RENDER_GL_DRIVER_INPUT_STAGE_HEADER
#define RENDER_GL_DRIVER_INPUT_STAGE_HEADER

#include <stl/auto_ptr.h>
#include <render/low_level/device.h>
#include <shared/context_manager.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ��������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
class InputStage
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InputStage  (ContextManager&);
    ~InputStage ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IInputLayout* CreateInputLayoutState (const InputLayoutDesc& desc);
    IBuffer*      CreateVertexBuffer     (const BufferDesc& desc);
    IBuffer*      CreateIndexBuffer      (const BufferDesc& desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void          SetInputLayout  (IInputLayout* state);
    IInputLayout* GetInputLayout  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void     SetVertexBuffer (size_t vertex_buffer_slot, IBuffer* buffer);
    IBuffer* GetVertexBuffer (size_t vertex_buffer_slot) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void     SetIndexBuffer (IBuffer* buffer);
    IBuffer* GetIndexBuffer () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ������ ������� �������� � ���� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* GetIndices   () const;
    GLenum      GetIndexType () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind (size_t base_vertex, size_t base_index);

  private:
    InputStage (const InputStage&); //no impl
    InputStage& operator = (const InputStage&); //no impl

  private:  
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif
