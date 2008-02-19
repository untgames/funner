#ifndef RENDER_LOW_LEVEL_STATE_HEADER
#define RENDER_LOW_LEVEL_STATE_HEADER

#include <render/low_level/object.h>
#include <render/low_level/common.h>
#include <stl/vector>

namespace render
{

namespace low_level
{

/*
===================================================================================================
    Input stage
===================================================================================================
*/

//////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum VertexAttributeSemantic
{
  VertexAttributeSemantic_Position,  //���������
  VertexAttributeSemantic_Normal,    //�������
  VertexAttributeSemantic_Color,     //����
  VertexAttributeSemantic_TexCoord0, //������ ���������� ���������
  VertexAttributeSemantic_TexCoord1,
  VertexAttributeSemantic_TexCoord2,
  VertexAttributeSemantic_TexCoord3,
  VertexAttributeSemantic_TexCoord4,
  VertexAttributeSemantic_TexCoord5,
  VertexAttributeSemantic_TexCoord6,  
  VertexAttributeSemantic_TexCoord7,
  
  VertexAttributeSemantic_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum InputDataType
{
  InputDataType_Byte,   //������������ ����� �������� �����
  InputDataType_UByte,  //������������ ����� ����������� �����
  InputDataType_Short,  //����������� ����� �������� �����
  InputDataType_UShort, //����������� ����� ����������� �����
  InputDataType_Int,    //�������������� ����� �������� �����
  InputDataType_UInt,   //�������������� ����� ����������� �����
  InputDataType_Float,  //�������������� ������������ �����

  InputDataType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum InputDataFormat
{
  InputDataFormat_Value,                           //��������� ��������
  InputDataFormat_Vector1 = InputDataFormat_Value, 
  InputDataFormat_Vector2,                         //������ �� ���� ���������
  InputDataFormat_Vector3,                         //������ �� ��� ���������
  InputDataFormat_Vector4,                         //������ �� ������ ���������
  
  InputDataFormat_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct VertexAttribute
{
  VertexAttributeSemantic semantic; //��������� ���������� ��������
  InputDataFormat         format;   //������ ������
  InputDataType           type;     //��� ���������
  size_t                  slot;     //����� ����� � ��������� �������
  size_t                  offset;   //�������� �� ������ ���������� ������
  size_t                  stride;   //��� � ��������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct InputLayoutDesc
{
  size_t                 vertex_attributes_count; //���������� ��������� ���������
  const VertexAttribute* vertex_attributes;       //��������� ��������
  InputDataType          index_type;              //��� �������� � ��������� ������
  size_t                 index_buffer_offset;     //�������� � ��������� ������
};

/*
===================================================================================================
    Shader stage
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ProgramParameterType
{
  ProgramParameterType_Int,         //����� �����
  ProgramParameterType_Float,       //������������ �����
  ProgramParameterType_Int2,        //������ �� 2-� ����� �����
  ProgramParameterType_Float2,      //������ �� 2-� ������������ �����
  ProgramParameterType_Int3,        //������ �� 3-� ����� �����
  ProgramParameterType_Float3,      //������ �� 3-� ������������ �����
  ProgramParameterType_Int4,        //������ �� 4-� ����� �����
  ProgramParameterType_Float4,      //������ �� 4-� ������������ �����
  ProgramParameterType_Float2x2,    //������� 2x2 ������������ �����
  ProgramParameterType_Float3x3,    //������� 3x3 ������������ �����
  ProgramParameterType_Float4x4,    //������� 4x4 ������������ �����

  ProgramParameterType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ProgramParameter
{
  const char*          name;   //��� ���������
  ProgramParameterType type;   //��� ���������
  size_t               slot;   //����� ����� � ���������� �������
  size_t               offset; //�������� ������������ ������ ������������ ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������ ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ProgramParametersLayoutDesc
{
  size_t                  parameters_count; //���������� ���������� �������
  const ProgramParameter* parameters;       //��������� �������
};

#if 0

/*
===================================================================================================
    Shader stage (viewer)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ViewerDesc
{
  Matrix4f projection; //������� �������������
  Matrix4f view;       //������� ����
};

/*
===================================================================================================
    Shader stage (transform)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TransformDesc
{
  Matrix4f transform; //������� ��������������
};

/*
===================================================================================================
    Shader stage (lighting)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum LightType
{
  LightType_Point,  //�������� �������� �����
  LightType_Direct, //�������������� ������������ �������� �����
  LightType_Spot,   //�������������� ������������ �������� �����
  
  LightType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ����� � ����������� �� ���������� (I(D) = Ibase / (A0 + A1 * d + A2 * d * d))
///////////////////////////////////////////////////////////////////////////////////////////////////
enum LightAttenuation
{
  LightAttenuation_Constant,  //���������� ����������� ��������� (A0)
  LightAttenuation_Linear,    //�������� ����������� ��������� (A1)
  LightAttenuation_Quadratic, //������������ ����������� ��������� (A2)

  LightAttenuation_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct LightDesc
{
  LightType type;           //��� ��������� �����  
  bool      enable;         //��������� ��������� �����: �������/��������
  Color3f   ambient_color;  //���� ����������� ������������ �����
  Color3f   diffuse_color;  //���� ������������ ������������ �����
  Color3f   specular_color; //���� ��������� ������������ �����
  float     inner_angle;    //���������� ���� ���������
  float     outer_angle;    //������� ���� ���������
  float     attenuation [LightAttenuation_Num]; //������������ ���������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct LightingDesc
{
  size_t           lights_count; //���������� ���������� �����
  const LightDesc* lights;       //�������� ���������� �����
};

#endif

/*
===================================================================================================
    Shader stage (sampling)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TexMinFilter
{
  TexMinFilter_Default,         //���������� ���������� � ������������ � �������������� ���������� ������������
  TexMinFilter_Point,           //�������� ����������
  TexMinFilter_Linear,          //�������� ����������
  TexMinFilter_PointMipPoint,   //�������� ���������� �� ���������� ����
  TexMinFilter_LinearMipPoint,  //�������� ���������� �� ���������� ����
  TexMinFilter_PointMipLinear,  //�������� ���������� � �������� ������������� �����
  TexMinFilter_LinearMipLinear, //����������� ����������
  
  TexMinFilter_Num
};

enum TexMagFilter
{
  TexMagFilter_Default, //���������� ���������� � ������������ � �������������� ���������� ������������
  TexMagFilter_Point,   //�������� ����������
  TexMagFilter_Linear,  //�������� ����������

  TexMagFilter_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TexcoordWrap
{
  TexcoordWrap_Repeat,        //����������
  TexcoordWrap_Mirror,        //���������� ���������
  TexcoordWrap_Clamp,         //���������
  TexcoordWrap_ClampToBorder, //��������� �� ����� �������
  
  TexcoordWrap_Num,
  
  TexcoordWrap_Default = TexcoordWrap_Repeat
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct SamplerDesc
{
  TexMinFilter min_filter;           //����������, ������������ ���� ������ ������� ������ ������� �������
  TexMagFilter mag_filter;           //����������, ������������ ���� ������ ������� ������ ������� �������
  TexcoordWrap wrap_u;               //������ �� ���������� U
  TexcoordWrap wrap_v;               //������ �� ���������� V
  TexcoordWrap wrap_w;               //������ �� ���������� W
  CompareMode  comparision_function; //������� ��������� ��� depth ������������ �������
  float        mip_lod_bias;         //�������� �� ������������ mip-������
  float        min_lod;              //����������� mip-�������
  float        max_lod;              //������������ mip-�������
  size_t       max_anisotropy;       //������������ ������� �����������
  float        border_color [4];     //���� �������
};

#if 0

/*
===================================================================================================
    Shader stage (material)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum TexcoordSource
{
  TexcoordSource_Explicit,      //���������� ���������� �������� ����
  TexcoordSource_SphereMap,     //��������� ���������� ���������: ����������� �����
  TexcoordSource_ReflectionMap, //��������� ���������� ���������: ����� ���������
  TexcoordSource_ObjectSpace,   //��������� ���������� ���������: texmap.transform * position
  TexcoordSource_ViewerSpace,   //��������� ���������� ���������: texmap.transform * modelviewprojection * position
  
  TexcoordSource_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TexmapDesc
{
  bool           enable;                   //��������� �� �����
  size_t         sampler_slot;             //����� ����� � ���������  
  Matrix4f       transform;                //������� �������������� ���������� ���������  
  int            dynamic_transform_index;  //������ � ������� ������ �������������� (-1 - ������������ �������������� �����������)
  TexcoordSource source_u;                 //�������� ���������� ��������� ��� U-����������
  TexcoordSource source_v;                 //�������� ���������� ��������� ��� V-����������
  TexcoordSource source_w;                 //�������� ���������� ��������� ��� W-����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ���� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum MaterialMap
{
  MaterialMap_Diffuse,     //������� �������� (���������� ���������)
  MaterialMap_Ambient,     //�������� ���������� �����
  MaterialMap_Specular,    //�������� ������� ��������� �����
  MaterialMap_Transparent, //�������� ������������
  MaterialMap_Emission,    //�������� ������� (self-illumination)
  MaterialMap_Reflective,  //�������� ����� ��������� (env-map)
  MaterialMap_Bump,        //�������� ������� �����������
    //+MaterialMap_Shadow   //�������� ������� �����
  
  MaterialMap_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct CommonMaterialDesc
{
  Color4f      emission;                //���� ���������
  Color4f      ambient;                 //���� ����������
  Color4f      diffuse;                 //���� �����������
  Color4f      specular;                //���� ���������
  float        shininess;               //�������������
  CompareMode  alpha_compare_mode;      //����� ����� �����
  float        alpha_reference;         //��������� ����� �����
  TexmapDesc   maps [MaterialMap_Num];  //���������� �����
};

#endif

/*
===================================================================================================
    Rasterizer stage
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FillMode
{
  FillMode_Wireframe, //��������� ������ �������
  FillMode_Solid,     //�������� ������ �������
  
  FillMode_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CullMode
{
  CullMode_None,  //��� ���������
  CullMode_Front, //�������� �������� �����
  CullMode_Back,  //�������� ������ �����
  
  CullMode_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct RasterizerDesc
{
  FillMode fill_mode;               //����� �������
  CullMode cull_mode;               //����� ���������
  bool     front_counter_clockwise; //����� ����������� �������� ������ (�� ������� ������� - true, ������ - false)
  int      depth_bias;              //�������� ������������ � ������� ������� 
  bool     scissor_enable;          //�������� �� scissor-���������
  bool     multisample_enable;      //�������� �� �������������������
  bool     antialiased_line_enable; //������� �� ������������ �����
};

/*
===================================================================================================
    Output stage (depth-stencil)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������, ����������� ��� ���������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum StencilOperation
{
  StencilOperation_Keep,      //������� �������� �� ����������
  StencilOperation_Zero,      //�������� �������� ��������������� ������ ����
  StencilOperation_Replace,   //�������� �������� ���������� ��������� stencil_reference
  StencilOperation_Increment, //�������� ������������� �� 1 � ���������� �� �������� �������
  StencilOperation_Decrement, //�������� ����������� �� 1 � ���������� �� ������� �������
  StencilOperation_Invert,    //�������� �������������
  
  StencilOperation_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct StencilDesc
{
  CompareMode      stencil_compare_mode;   //����� ��������� �������� � stencil-test
  StencilOperation stencil_fail_operation; //��������, ����������� ��� ��������� ������ ��������� � ������ ������� stencil-test
  StencilOperation depth_fail_operation;   //��������, ����������� ��� ��������� ������ ��������� � ������ ������� depth-test
  StencilOperation stencil_pass_operation; //��������, ����������� ��� ��������� ������ ��������� � ������ ����������� stencil-test
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum FaceMode
{
  FaceMode_Front, //�������� �����
  FaceMode_Back,  //������ �����
  
  FaceMode_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct DepthStencilDesc
{
  bool          depth_test_enable;      //������� �� ���� �������
  bool          depth_write_enable;     //�������� �� ������ � ����� �������
  bool          stencil_test_enable;    //������� �� ���� ���������
  CompareMode   depth_compare_mode;     //����� ��������� � ����� �������
  unsigned char stencil_read_mask;      //�����, ������������� �� �������� ������ ��������� ��� ������
  unsigned char stencil_write_mask;     //�����, ������������� �� �������� ������ ��������� ��� ������
  StencilDesc   stencil_desc [FaceMode_Num]; //����������� ������ ��������� ��� ��������� ����� ������
};

/*
===================================================================================================
    Output stage (blending)
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum BlendOperation
{
  BlendOperation_Add,                //arg1 + arg2
  BlendOperation_Subtraction,        //arg1 - arg2
  BlendOperation_ReverseSubtraction, //arg2 - arg1
  BlendOperation_Min,                //min (arg1, arg2)
  BlendOperation_Max,                //max (arg1, arg2)
  
  BlendOperation_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum BlendArgument
{
  BlendArgument_Zero,                    //0
  BlendArgument_One,                     //1
  BlendArgument_SourceColor,             //���� ���������
  BlendArgument_SourceAlpha,             //����� ���������
  BlendArgument_InverseSourceColor,      //1 - ���� ���������
  BlendArgument_InverseSourceAlpha,      //1 - ����� ���������
  BlendArgument_DestinationColor,        //���� ��������
  BlendArgument_DestinationAlpha,        //����� ��������
  BlendArgument_InverseDestinationColor, //1 - ���� ��������
  BlendArgument_InverseDestinationAlpha, //1 - ����� ��������
  
  BlendArgument_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ColorWriteFlag
{
  ColorWriteFlag_Red   = 1, //���������� �� ���������� ������� ���������� �����
  ColorWriteFlag_Green = 2, //���������� �� ���������� ������ ���������� �����
  ColorWriteFlag_Blue  = 4, //���������� �� ���������� ����� ���������� �����
  ColorWriteFlag_Alpha = 8, //���������� �� ���������� ����� ���������� �����
  ColorWriteFlag_All   = ColorWriteFlag_Red | ColorWriteFlag_Green | ColorWriteFlag_Blue | ColorWriteFlag_Alpha
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct BlendDesc
{
  bool           blend_enable;                      //�������� �� ���������� ������
  bool           sample_alpha_to_coverage;          //������ � ����� ��� ���������������
  BlendOperation blend_color_operation;             //��� �������� ���������� ������
  BlendArgument  blend_color_source_argument;       //�������� ������� ���������� ������, ��������� �� ��������� �����
  BlendArgument  blend_color_destination_argument;  //�������� ������� ���������� ������, ��������� �� �������� �����
  BlendOperation blend_alpha_operation;             //��� �������� ���������� ����� ���������
  BlendArgument  blend_alpha_source_argument;       //�������� ������� ���������� ����� ���������, ��������� �� ��������� �����
  BlendArgument  blend_alpha_destination_argument;  //�������� ������� ���������� ����� ���������, ��������� �� �������� �����
  unsigned char  color_write_mask;                  //����� ������ ������
};

/*
===================================================================================================
    ������ ���������
===================================================================================================
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Desc> class IStateTemplate: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetDesc (const Desc&) = 0;
    virtual void GetDesc (Desc&) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ��������� ���������� ��������� ��� ����������� ������� ����������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class Desc> class ILayoutTemplate: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetDesc (const Desc&) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� ���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
typedef ILayoutTemplate<InputLayoutDesc>             IInputLayout;
typedef ILayoutTemplate<ProgramParametersLayoutDesc> IProgramParametersLayout;
typedef IStateTemplate<SamplerDesc>                  ISamplerState;
typedef IStateTemplate<RasterizerDesc>               IRasterizerState;
typedef IStateTemplate<DepthStencilDesc>             IDepthStencilState;
typedef IStateTemplate<BlendDesc>                    IBlendState;

}

}

#endif
