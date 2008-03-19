#ifndef RENDER_COMMON_HEADER
#define RENDER_COMMON_HEADER

namespace render
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct Rect
{
  int    x, y;
  size_t width, size_t height;
  
  Rect ();
  Rect (int x, int y, size_t width, size_t height);
};

}

#endif
