#ifndef RENDER_GL_DRIVER_SHADER_STAGE_SHARED_HEADER
#define RENDER_GL_DRIVER_SHADER_STAGE_SHARED_HEADER

#include <shared/shader_stage.h>

#include <common/exception.h>

#include <xtl/trackable_ptr.h>
#include <xtl/uninitialized_storage.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ConstantBuffer : virtual public IBuffer, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ConstantBuffer (const ContextManager& manager, const BufferDesc& in_desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (BufferDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ / ������ �� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetData (size_t offset, size_t size, const void* data);
    void GetData (size_t offset, size_t size, void* data);

  private:
    BufferDesc desc;
    xtl::uninitialized_storage <char> buffer;     //����� � ��������� ������
};

typedef xtl::trackable_ptr<ConstantBuffer> ConstantBufferPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ShaderParametersLayout : virtual public IShaderParametersLayout, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ShaderParametersLayout (const ContextManager& manager);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDesc (const ShaderParametersLayoutDesc& in_desc);
    void GetDesc (ShaderParametersLayoutDesc& target_desc);

  private:
    ShaderParametersLayoutDesc desc;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Shader : virtual public IShader, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Bind (ConstantBufferPtr* constant_buffers, ShaderParametersLayout* shader_parameters_layout) = 0;

  protected:
    Shader (const ContextManager& manager) : ContextObject (manager) {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ShaderManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual ~ShaderManager () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual size_t GetProfilesCount () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual const char* GetProfile (size_t index) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual Shader* CreateShader (size_t shaders_count, const ShaderDesc* shader_descs, const LogFunction& error_log) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
ShaderManager* create_glsl_shader_manager (const ContextManager& manager);

}

}

}

#endif
