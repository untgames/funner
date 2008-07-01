#ifndef RENDER_MID_LEVEL_RENDERER2D_HEADER
#define RENDER_MID_LEVEL_RENDERER2D_HEADER

#include <render/mid_level/renderer.h>
#include <render/mid_level/common.h>

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
///������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ISpriteList: virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t GetSize () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void SetSprites (size_t first, size_t count, const Sprite* sprites) = 0;
    virtual void GetSprites (size_t first, size_t count, Sprite* sprites) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Primitive
{
  ITexture*    texture;       //������� ��������
  ISpriteList* sprite_list;   //������ ��������
  math::mat4f  transform;     //������� �������������� ���������
  BlendMode    blend_mode;    //����� ���������  
  size_t       first_sprite;  //����� ������� �������
  size_t       sprites_count; //���������� ��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������ 2D-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Frame: public mid_level::Frame
{
  math::vec2f size;             //���������� ������� �����
  size_t      primitives_count; //���������� ���������� � �����
  Primitive*  primitives;       //���������
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
    virtual ITexture*    CreateTexture    (const media::Image& image) = 0;
    virtual ITexture*    CreateTexture    (size_t width, size_t height, media::PixelFormat pixel_format) = 0;
    virtual ISpriteList* CreateSpriteList (size_t sprites_count) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddFrame (Frame*) = 0;
};

}

}

}

#endif
