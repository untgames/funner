#ifndef RENDER_GL_DRIVER_SHADER_STAGE_SHARED_HEADER
#define RENDER_GL_DRIVER_SHADER_STAGE_SHARED_HEADER

#include <stl/vector>
#include <stl/algorithm>
#include <stl/string>

#include <xtl/intrusive_ptr.h>
#include <xtl/trackable_ptr.h>
#include <xtl/uninitialized_storage.h>
#include <xtl/common_exceptions.h>

#include <common/strlib.h>

#include <render/low_level/utils.h>

#include <render/low_level/helpers/program_parameters_layout.h>

#include <shared/shader_stage.h>
#include <shared/input_stage.h>

namespace render
{

namespace low_level
{

namespace opengl
{

using helpers::ProgramParameterGroup;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ��������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ShadingStageCacheEntry
{
  CacheEntry_UsedProgram = CacheEntry_ShadingStagePrivateFirst, //ID ������� ������������ ���������
  CacheEntry_FfpViewerStateHash,             //��� ���������� �����������
  CacheEntry_FfpObjectStateHash,             //��� ���������� �������
  CacheEntry_FfpRasterizationStateHash,      //��� ���������� ������������
  CacheEntry_FfpMaterialStateHash,           //��� ���������� ���������
  CacheEntry_FfpLightingStateHash,           //��� ���������� ���������
  CacheEntry_FfpTexmapsStateHash,            //��� ���������� ���������������
  CacheEntry_FfpModesStateHash,              //��� ������� ������������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ���������� ��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ProgramParametersLayout: public helpers::ProgramParametersLayout, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ProgramParametersLayout (const ContextManager& manager, const ProgramParametersLayoutDesc& desc)
      : helpers::ProgramParametersLayout (desc)
      , ContextObject (manager)
    {
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IShader: virtual public IObject
{
  protected:
    virtual ~IShader () {}
};

typedef xtl::trackable_ptr<IBindableBuffer> ConstantBufferPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� � ������������ ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
class IBindableProgram: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Bind (ConstantBufferPtr* constant_buffers) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Validate () = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������������� ��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ICompiledProgram: virtual public IProgram
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� � ������������ ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual IBindableProgram* CreateBindableProgram (ProgramParametersLayout* layout) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual IVertexAttributeDictionary* GetVertexAttributeDictionary () = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IShaderManager : virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual size_t GetProfilesCount () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual const char* GetProfile (size_t index) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� / ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
   virtual IShader*          CreateShader  (const ShaderDesc& shader_desc, const LogFunction& error_log) = 0;
   virtual ICompiledProgram* CreateProgram (size_t shaders_count, IShader** shaders, const LogFunction& error_log) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
IShaderManager* create_ffp_shader_manager  (const ContextManager& manager);
IShaderManager* create_glsl_shader_manager (const ContextManager& manager);

}

}

}

#endif
