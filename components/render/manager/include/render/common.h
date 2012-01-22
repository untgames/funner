#ifndef RENDER_MANAGER_COMMON_HEADER
#define RENDER_MANAGER_COMMON_HEADER

namespace render
{

//implementation forwards
class RectAreaImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum PixelFormat
{
  PixelFormat_RGB8,
  PixelFormat_RGBA8,
  PixelFormat_L8,
  PixelFormat_A8,
  PixelFormat_LA8,
  PixelFormat_DXT1,
  PixelFormat_DXT3,
  PixelFormat_DXT5,
  PixelFormat_RGB_PVRTC2,
  PixelFormat_RGB_PVRTC4,
  PixelFormat_RGBA_PVRTC2,
  PixelFormat_RGBA_PVRTC4,
  PixelFormat_D16,
  PixelFormat_D24X8,
  PixelFormat_D24S8,
  PixelFormat_D32,
  PixelFormat_S8,

  PixelFormat_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
const char* get_name (PixelFormat); //��������� ����� �������

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Rect
{
  int    x;      //�������� ������ �������� ���� �������
  int    y;      //�������� ������ �������� ���� �������
  size_t width;  //������ �������
  size_t height; //������ �������
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
  Rect ();
  Rect (int x, int y, size_t width, size_t height);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
  bool operator == (const Rect&) const;
  bool operator != (const Rect&) const;    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ������� (��� ����������� ������� ���������� �������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
class RectArea
{
  friend class Wrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RectArea  ();
    RectArea  (const render::Rect&);
    ~RectArea ();
    
    RectArea& operator = (const RectArea&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                SetRect (const render::Rect& rect);
    void                SetRect (int x, int y, size_t width, size_t height);
    const render::Rect& Rect    () const;
    int                 X       () const;
    int                 Y       () const;
    size_t              Width   () const;
    size_t              Height  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (RectArea&);
  
  private:
    RectArea (RectAreaImpl*);
    
  private:
    RectAreaImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (RectArea&, RectArea&);

}

#endif