#ifndef RENDER_MANAGER_COMMON_HEADER
#define RENDER_MANAGER_COMMON_HEADER

namespace render
{

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
  
  Rect ();
  Rect (int x, int y, size_t width, size_t height);
};

}

#endif
