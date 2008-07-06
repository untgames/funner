#ifndef DEMOS_RENDER2D_SHARED_HEADER
#define DEMOS_RENDER2D_SHARED_HEADER

#include <cstdio>
#include <ctime>

#include <stl/auto_ptr.h>
#include <stl/vector>

#include <xtl/function.h>
#include <xtl/bind.h>
#include <xtl/ref.h>

#include <common/strlib.h>

#include <sg/scene.h>
#include <sg/camera.h>
#include <sg/sprite.h>

#include <render/scene_render.h>

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
