#ifndef SCENE_GRAPH_RENDER2D_HEADER
#define SCENE_GRAPH_RENDER2D_HEADER

#include <stl/hash_map>

#include <xtl/common_exceptions.h>
#include <xtl/function.h>
#include <xtl/reference_counter.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/connection.h>
#include <xtl/bind.h>
#include <xtl/visitor.h>

#include <common/component.h>

#include <sg/scene.h>
#include <sg/camera.h>
#include <sg/sprite.h>

#include <render/mid_level/renderer2d.h>

#include <render/custom_render.h>

namespace render
{

namespace render2d
{

//forward declaration
class Render;

typedef mid_level::renderer2d::IPrimitive IPrimitive;
typedef mid_level::renderer2d::IRenderer  IRenderer;
typedef mid_level::renderer2d::IFrame     IFrame;

typedef xtl::com_ptr<IPrimitive> PrimitivePtr;
typedef xtl::com_ptr<IRenderer>  RendererPtr;
typedef xtl::com_ptr<IFrame>     FramePtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Renderable: public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Renderable (scene_graph::Entity*);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Draw (IFrame& frame) {}

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �� ���������� � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void UpdateNotify () {}
  
  private:
    xtl::auto_connection on_update_connection;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableSprite: public Renderable
{
  public:
    RenderableSprite (scene_graph::Sprite* sprite, IRenderer& renderer);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Draw (IFrame& frame);

  private:
    void UpdateNotify ();

  private:
    scene_graph::Sprite* sprite;
    PrimitivePtr         primitive;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderView: public IRenderView, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderView  (scene_graph::Scene*, Render*);
    ~RenderView ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetViewport (float left, float top, float width, float height);
    void GetViewport (float viewport [4]);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                 SetCamera (scene_graph::Camera*);
    scene_graph::Camera* GetCamera ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetProperty (const char* name, const char* value);
    void GetProperty (const char* name, size_t buffer_size, char* value_buffer);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Draw ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();
    void Release ();

  private:
    typedef xtl::intrusive_ptr<Render> RenderPtr;

    RenderPtr            render;       //������
    FramePtr             frame;        //����
    scene_graph::Scene*  scene;        //�����
    scene_graph::Camera* camera;       //������
    float                viewport [4]; //������� ������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Render: public ICustomSceneRender, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Render  (mid_level::IRenderer*);
    ~Render ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IRenderView* CreateRenderView (scene_graph::Scene* scene);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ������� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetBackgroundColor (const math::vec4f& color);
    void GetBackgroundColor (math::vec4f& color);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����������� ����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetLogHandler (const LogFunction&);
    const LogFunction& GetLogHandler ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();
    void Release ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const RendererPtr& Renderer () const { return renderer; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Renderable* GetRenderable (scene_graph::Sprite*);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddFrame (IFrame*);

  private:
    typedef xtl::intrusive_ptr<Renderable> RenderablePtr;
    
    struct RenderableHolder
    {
      RenderablePtr        renderable;
      xtl::auto_connection on_destroy;

      RenderableHolder (const RenderablePtr& in_renderable, const xtl::connection& in_on_destroy) :
        renderable (in_renderable), on_destroy (in_on_destroy) {}
    };

    void InsertRenderable (scene_graph::Entity*, const RenderablePtr&);
    void RemoveRenderable (scene_graph::Entity*);

  private:
    typedef stl::hash_map<scene_graph::Entity*, RenderableHolder> RenderableMap;

  private:
    math::vec4f    clear_color;       //���� �������
    LogFunction    log_handler;       //������� ����������������
    RendererPtr    renderer;          //������� ����������
    RenderableMap  renderables_cache; //��� ��������������� ��������
};

}

}

#endif
