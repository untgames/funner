#ifndef RENDER_SCENE_SERVER_WINDOW_MANAGER_SHARED_HEADER
#define RENDER_SCENE_SERVER_WINDOW_MANAGER_SHARED_HEADER

#include <stl/auto_ptr.h>

#include <shared/render_manager.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class WindowManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    WindowManager  (const RenderManager&);
    ~WindowManager ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � �������� ����  
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachWindow (size_t id, const char* name, const char* init_string, void* handle, size_t width, size_t height, const manager::Rect& rect);    
    void DetachWindow (size_t id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    manager::Window& GetWindow (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetWindowSize     (size_t id, size_t width, size_t height);
    void SetWindowViewport (size_t id, const manager::Rect& rect);
    void SetWindowHandle   (size_t id, void* handle);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RepaintWindow (size_t id);

  private:
    WindowManager (const WindowManager&); //no impl
    WindowManager& operator = (const WindowManager&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif