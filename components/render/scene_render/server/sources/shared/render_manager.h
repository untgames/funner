#ifndef RENDER_SCENE_SERVER_RENDER_MANAGER_SHARED_HEADER
#define RENDER_SCENE_SERVER_RENDER_MANAGER_SHARED_HEADER

#include <stl/auto_ptr.h>

#include <common/log.h>

#include <render/manager.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��� ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderManager: public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderManager  (const char* name);
    RenderManager  (const RenderManager&);
    ~RenderManager ();

    RenderManager& operator = (const RenderManager&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������� ����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    common::Log& Log ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    manager::RenderManager& Manager ();

  private:
    struct Impl;
    Impl* impl;
};

}

}

}

#endif
