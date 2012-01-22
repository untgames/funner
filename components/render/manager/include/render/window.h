#ifndef RENDER_MANAGER_WINDOW_HEADER
#define RENDER_MANAGER_WINDOW_HEADER

#include <xtl/functional_fwd>

#include <render/render_target.h>

namespace render
{

//implementation forwards
class WindowImpl;
class Wrappers;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum WindowEvent
{
  WindowEvent_OnUpdate, //���� ������� �����������
  WindowEvent_OnResize, //������ ���� ���������
  
  WindowEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Window
{
  friend class Wrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Window  (const Window&);
    ~Window ();
    
    Window& operator = (const Window&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetName (const char* name);
    const char* Name    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTarget ColorBuffer        () const;
    RenderTarget DepthStencilBuffer () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Width  () const;
    size_t Height () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ���������� ����������� ���� (����� �������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SwapBuffers ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (Window&)> EventHandler;

    xtl::connection RegisterEventHandler (WindowEvent event, const EventHandler& handler) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Window&);
    
  private:
    Window (WindowImpl*);

  private:
    WindowImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Window&, Window&);

}

#endif