#ifndef DEMOS_RENDER2D_SHARED_HEADER
#define DEMOS_RENDER2D_SHARED_HEADER

#include <cstdio>
#include <ctime>

#include <stl/auto_ptr.h>
#include <stl/vector>

#include <xtl/bind.h>
#include <xtl/function.h>
#include <xtl/ref.h>
#include <xtl/shared_ptr.h>

#include <common/file.h>
#include <common/strlib.h>

#include <sg/scene.h>
#include <sg/camera.h>
#include <sg/sprite.h>

#include <render/scene_render.h>

#include <script/bind_libraries.h>
#include <script/environment.h>
#include <script/bind.h>
#include <script/shell.h>

#include <input/low_level/device.h>
#include <input/low_level/driver.h>
#include <input/low_level/window_driver.h>

#include <input/translation_map.h>

using namespace script;
using namespace script::binds;
using namespace scene_graph;
using namespace render;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��� ��� ������ ������ ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class TestApplication
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TestApplication  ();
    ~TestApplication ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SceneRender& Render ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    input::low_level::IDevice& InputDevice ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::RenderTarget& RenderTarget ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void PostRedraw ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    int Run ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� idle-������� 
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (TestApplication&)> IdleFunction;
    
    void SetIdleHandler (const IdleFunction&);

  private:
    TestApplication (const TestApplication&); //no impl
    TestApplication& operator = (const TestApplication&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

#endif
