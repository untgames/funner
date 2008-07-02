#ifndef RENDER_MID_LEVEL_RENDERER2D_HEADER
#define RENDER_MID_LEVEL_RENDERER2D_HEADER

#include <render/mid_level/renderer.h>

namespace media
{

//forward declarations
enum PixelFormat;
class Image;

}

namespace render
{

namespace mid_level
{

namespace renderer2d
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ITexture: virtual public IRenderTarget {};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������� ������ ��� ��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum BlendMode
{
  BlendMode_None,        //��� ����������
  BlendMode_Translucent, //����������������
  BlendMode_Mask,        //��������� �� ����� - ������ �������� ������ ��� ���������
  BlendMode_Additive,    //���������� ���������

  BlendMode_Num 
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Sprite
{
  math::vec3f position;   //��������� ������ ������ �������
  math::vec2f size;       //������ �������
  math::vec4f color;      //���� �������
  math::vec2f tex_offset; //�������� ������ ������� � �������� [0;1]
  math::vec2f tex_size;   //������ ������� � �������� [0;1]
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IPrimitive: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetTransform (const math::mat4f&) = 0;
    virtual void GetTransform (math::mat4f&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void      SetTexture (ITexture*) = 0;
    virtual ITexture* GetTexture () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void      SetBlendMode (BlendMode blend_mode) = 0;
    virtual BlendMode GetBlendMode () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t GetSpritesCount  () = 0;                                            //���������� ��������
    virtual void   GetSprite        (size_t index, Sprite& sprite) = 0;                //��������� �������
    virtual size_t AddSprites       (size_t sprites_count, const Sprite* sprites) = 0; //���������� ��������
    virtual void   RemoveSprites    (size_t first_sprite, size_t sprites_count) = 0;   //�������� ��������
    virtual void   RemoveAllSprites () = 0;                                            //�������� ���� ��������
    virtual void   ReserveSprites   (size_t sprites_count) = 0;                        //�������������� ����� ��� ��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� 2D ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IFrame: virtual public mid_level::IFrame
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���� / ������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetView       (const math::mat4f&) = 0;
    virtual void SetProjection (const math::mat4f&) = 0;
    virtual void GetView       (math::mat4f&) = 0;
    virtual void GetProjection (math::mat4f&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t PrimitivesCount () = 0;            //���������� ���������� � �����
    virtual void   AddPrimitive    (IPrimitive*) = 0; //���������� ���������
    virtual void   Clear           () = 0;            //������� �����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������� 2D-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IRenderer: virtual public mid_level::IRenderer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ITexture*   CreateTexture   (const media::Image& image) = 0;
    virtual ITexture*   CreateTexture   (size_t width, size_t height, media::PixelFormat pixel_format) = 0;
    virtual IPrimitive* CreatePrimitive () = 0;
    virtual IFrame*     CreateFrame     () = 0;
};

}

}

}

#endif
