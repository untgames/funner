#include "shared.h"

using namespace common;

namespace
{

const GLEWContext*  current_glew_context  = 0; //������� �������� GLEW
const WGLEWContext* current_wglew_context = 0; //������� �������� WGLEW

}

namespace render
{

namespace low_level
{

namespace opengl
{

//��������� �������� ��������� GLEW
void glewSetContext (const GLEWContext* glew_context)
{
  current_glew_context  = glew_context;
}

//��������� �������� ��������� WGLEW
void wglewSetContext (const WGLEWContext* wglew_context)
{
  current_wglew_context = wglew_context;
}

//��������� �������� ��������� GLEW
const GLEWContext* glewGetContext ()
{
  return current_glew_context;
}

//��������� �������� ��������� WGLEW
const WGLEWContext* wglewGetContext ()
{
  return current_wglew_context;
}

namespace
{

//�������� ���������������� ���� ��� ������������� ���������� WGL
HWND create_dummy_window (HWND parent)
{
  HWND window = CreateWindow ("static", "", WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    parent, 0, GetModuleHandle (0), 0);

  if (!window)
    raise_error ("CreateWindow");
    
  return window;
}

}

//������������� ��������� WGLEW
void init_wglew_context (const SwapChainDesc& swap_chain_desc, WGLEWContext* wglew_context)
{
  WGLEWScope wglew_scope;

    //�������� ���������������� ��������� OpenGL

  HWND  window        = (HWND)swap_chain_desc.window_handle,
        dummy_window  = 0;
  HDC   dummy_dc      = 0;
  HGLRC dummy_context = 0;

    //������ �������� WGLEW ���������
    
  wglewSetContext (0);
  
  try
  {
    dummy_window = create_dummy_window (window);
    dummy_dc     = GetDC (dummy_window);
    
    if (!dummy_dc)
      raise_error ("GetDC");

    int pixel_format = choose_pixel_format (dummy_dc, swap_chain_desc); //����� ������� �������� ��� ������������� ����������
    
    PIXELFORMATDESCRIPTOR pfd;
  
    if (!DescribePixelFormat (dummy_dc, pixel_format, sizeof (pfd), &pfd))
      raise_error ("DescribePixelFormat");

    if (!SetPixelFormat (dummy_dc, pixel_format, &pfd))
      raise_error ("SetPixelFormat");

    dummy_context = wglCreateContext (dummy_dc);

    if (!dummy_context)
      raise_error ("wglCreateContext");

    if (!wglMakeCurrent (dummy_dc, dummy_context))
      raise_error ("wglMakeCurrent");

      //������������� ���������� WGL

    GLenum status = wglewContextInit (wglew_context);

    if (status != GLEW_OK)
      RaiseInvalidOperation ("wglewContextInit", "%s", glewGetString (status));

      //������������ ��������

    wglMakeCurrent   (0, 0);
    wglDeleteContext (dummy_context);
    ReleaseDC        (dummy_window, dummy_dc);
    DestroyWindow    (dummy_window);    
  }
  catch (...)
  {
    wglMakeCurrent (0, 0);

    if (dummy_context) wglDeleteContext (dummy_context);
    if (dummy_dc)      ReleaseDC        (dummy_window, dummy_dc);
    if (dummy_window)  DestroyWindow    (dummy_window);

    throw;
  }  
}

/*
    WGLEWScope
*/

WGLEWScope::WGLEWScope ()
  : old_context (wglewGetContext ())
{
}

WGLEWScope::WGLEWScope (const WGLEWContext* new_context)
  : old_context (wglewGetContext ())
{
  wglewSetContext (new_context);
}

WGLEWScope::~WGLEWScope ()
{
  wglewSetContext (old_context);
}

}

}

}
