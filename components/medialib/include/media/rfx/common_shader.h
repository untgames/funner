#ifndef MEDIALIB_RFX_COMMON_SHADER_HEADER
#define MEDIALIB_RFX_COMMON_SHADER_HEADER

#include <media/rfx/shader.h>
#include <media/rfx/texmap.h>
#include <mathlib.h>

namespace medialib
{

namespace rfx
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum BlendEquation
{
  BlendEquation_Add,                //arg1 + arg2
  BlendEquation_Subtraction,        //arg1 - arg2
  BlendEquation_ReverseSubtraction, //arg2 - arg1
  BlendEquation_Min,                //min (arg1, arg2)
  BlendEquation_Max,                //max (arg1, arg2)
  
  BlendEquation_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ������
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
///������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct BlendFunction
{
  BlendEquation equation;     //��������� ���������� ������
  BlendArgument argument [2]; //���������
  
  BlendFunction (BlendEquation, BlendArgument, BlendArgument);
};

BlendFunction make_blend_filter   (); //src_color * src_alpha + dst_color * (1 - src_alpha)
BlendFunction make_blend_additive (); //src_color + dst_color
BlendFunction make_blend_solid    (); //src_color

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CompareMode
{
  CompareMode_AlwaysFail,   //��������� ��������� ������ ����
  CompareMode_AlwaysPass,   //��������� ��������� ������ ������
  CompareMode_Equal,        //new_value == reference_value
  CompareMode_NotEqual,     //new_value != reference_value
  CompareMode_Less,         //new_value <  reference_value
  CompareMode_LessEqual,    //new_value <= reference_value
  CompareMode_Greater,      //new_value >  reference_value
  CompareMode_GreaterEqual, //new_value >= reference_value
  
  CompareMode_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CommonShaderType
{
  CommonShaderType_Flat,    //�������� �������
  CommonShaderType_Gourand, //������� �� ����
  CommonShaderType_Phong,   //������� �� �����
  
  CommonShaderType_Default = CommonShaderType_Gourand,
  
  CommonShaderType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CommonShaderColor
{
  CommonShaderColor_Ambient,   //���� ����������
  CommonShaderColor_Diffuse,   //���� �����������
  CommonShaderColor_Specular,  //���� ���������
  CommonShaderColor_Emission,  //���� ��������� 
  
  CommonShaderColor_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����, ������������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum CommonShaderMap
{
  CommonShaderMap_Diffuse,     //������� �������� (���������� ���������)
  CommonShaderMap_Ambient,     //�������� ���������� �����
  CommonShaderMap_Specular,    //�������� ������� ��������� �����
  CommonShaderMap_Transparent, //�������� ������������
  CommonShaderMap_Emission,    //�������� ������� (self-illumination)
  CommonShaderMap_Reflective,  //�������� ����� ��������� (env-map)
  CommonShaderMap_Bump,        //�������� ������� �����������

  CommonShaderMap_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum MapState
{
  MapState_Disabled, //����� ���������
  MapState_Enabled   //����� ���������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class CommonShader: public Shader
{
  public:
    typedef xtl::com_ptr<CommonShader>       Pointer;
    typedef xtl::com_ptr<const CommonShader> ConstPointer;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer Create ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    CommonShaderType Type    () const;
    void             SetType (CommonShaderType);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const math::vec3f& Color    (CommonShaderColor color_id) const;
    void               SetColor (CommonShaderColor color_id, const math::vec3f& color);
    void               SetColor (CommonShaderColor color_id, float red, float green, float blue);

///////////////////////////////////////////////////////////////////////////////////////////////////
///"�������������"
///////////////////////////////////////////////////////////////////////////////////////////////////
    float Shininess    () const;
    void  SetShininess (float value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    float Transparency    () const;
    void  SetTransparency (float value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const BlendFunction& Blend    () const;
    void                 SetBlend (const BlendFunction&);
    void                 SetBlend (BlendEquation equation, BlendArgument src_argument, BlendArgument dst_argument);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����-���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetAlphaTestMode      (CompareMode mode);
    void        SetAlphaTestReference (float alpha_reference);
    void        SetAlphaTest          (CompareMode mode, float alpha_reference);
    CompareMode AlphaTestMode         () const;
    float       AlphaTestReference    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const Texmap& Map (CommonShaderMap map) const;
          Texmap& Map (CommonShaderMap map);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    float MapWeight    (CommonShaderMap map) const;
    void  SetMapWeight (CommonShaderMap map, float weight);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / ���������� ���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    rfx::MapState MapState    (CommonShaderMap map) const;
    void          SetMapState (CommonShaderMap map, rfx::MapState state);

    bool IsMapEnabled (CommonShaderMap map) const { return MapState (map)  == MapState_Enabled; }
    void EnableMap    (CommonShaderMap map)       { SetMapState (map, MapState_Enabled);        }
    void DisableMap   (CommonShaderMap map)       { SetMapState (map, MapState_Disabled);       }

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    CommonShader  ();
    CommonShader  (const CommonShader&);
    ~CommonShader ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AcceptCore (Visitor&);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Shader* CloneCore () const;

  private:
    struct Impl;
    Impl* impl;
};

#include <media/rfx/detail/blend.inl>

}

}

#endif
