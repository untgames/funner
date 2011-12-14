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
#include <xtl/iterator.h>
#include <xtl/token_parser.h>
#include <xtl/trackable.h>

#include <math/utility.h>

#include <common/component.h>
#include <common/strlib.h>
#include <common/property_map.h>

#include <media/compressed_image.h>
#include <media/image.h>
#include <media/font.h>
#include <media/rfx/material_library.h>
#include <media/rfx/sprite_material.h>
#include <media/video.h>

#include <sg/camera.h>
#include <sg/scene.h>
#include <sg/sprite.h>
#include <sg/height_map.h>
#include <sg/text_line.h>

#include <render/mid_level/renderer2d.h>

#include <render/custom_render.h>

namespace render
{

namespace obsolete
{

namespace render2d
{

//forward declaration
class Render;

typedef mid_level::renderer2d::IPrimitive    IPrimitive;
typedef mid_level::renderer2d::IRenderer     IRenderer;
typedef mid_level::renderer2d::IFrame        IFrame;
typedef mid_level::renderer2d::ITexture      ITexture;
typedef mid_level::IRenderTarget             IRenderTarget;
typedef mid_level::renderer2d::BlendMode     BlendMode;
typedef xtl::com_ptr<IPrimitive>             PrimitivePtr;
typedef xtl::com_ptr<IRenderer>              RendererPtr;
typedef xtl::com_ptr<IFrame>                 FramePtr;
typedef xtl::com_ptr<ITexture>               TexturePtr;
typedef xtl::com_ptr<IRenderTarget>          RenderTargetPtr;
typedef xtl::com_ptr<IRenderQuery>           RenderQueryPtr;
typedef media::rfx::obsolete::SpriteMaterial SpriteMaterial;
typedef SpriteMaterial::Pointer              SpriteMaterialPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, ��������� ���������� ��� ���������� entity
///////////////////////////////////////////////////////////////////////////////////////////////////
class IRenderablePrerequisite: public xtl::reference_counter
{
  public:
    virtual ~IRenderablePrerequisite () {}  
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Update () = 0;
};

typedef xtl::intrusive_ptr<IRenderablePrerequisite> PrerequisitePtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Renderable: public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
            Renderable  (scene_graph::Entity*);
    virtual ~Renderable () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Draw (IFrame& frame);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��� ���������� ����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetVideoPosition (float position);
    float VideoPosition    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������, ��������� �������������
///////////////////////////////////////////////////////////////////////////////////////////////////  
    void AddPrerender (const PrerequisitePtr&);

  private:
    void UpdateNotify ();    

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �� ���������� � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Update () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void DrawCore (IFrame& frame) = 0;
    
  private:
    typedef stl::vector<PrerequisitePtr> PrerequisiteList;

  private:
    xtl::auto_connection on_update_connection;  //���������� �� ������ ���������� �� ���������� �������
    bool                 need_update;           //���� ������������� ���������� ���������� �������� ������ �������
    float                video_position;        //������� ��� ����� �������
    PrerequisiteList     prerender;             //������ ��������, ��������� ���������������� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, ��������� �� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableSpriteModel: public Renderable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderableSpriteModel (scene_graph::SpriteModel* model, Render& render);
    ~RenderableSpriteModel ();

  private:
    void Update ();
    void DrawCore (IFrame&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, ��������� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableHeightMap: public Renderable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderableHeightMap (scene_graph::HeightMap* model, Render& render);
    ~RenderableHeightMap ();

  private:
    void Update ();
    void DrawCore (IFrame&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� � ���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableFont
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderableFont (const char* font_name, Render& in_render);
    ~RenderableFont ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const media::Font& GetFont () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ITexture* GetTexture () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ����� ������� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetMaxGlyphSide () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const render::mid_level::renderer2d::Sprite& GetSprite (size_t index) const;
      //������ ������ ���������!!!!

  private:
    typedef xtl::uninitialized_storage<render::mid_level::renderer2d::Sprite> SpritesBuffer;

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableTextLine: public Renderable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderableTextLine (scene_graph::TextLine* text_line, Render& render);
    ~RenderableTextLine ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void PreprocessFont ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void DrawCore (IFrame&);

  private:
    typedef xtl::uninitialized_storage<render::mid_level::renderer2d::Sprite> SpritesBuffer;

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
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
///������� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void           SetRenderTargets      (IRenderTarget* render_target, IRenderTarget* depth_stencil_target);
    IRenderTarget* GetRenderTarget       ();
    IRenderTarget* GetDepthStencilTarget ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetViewport (const render::obsolete::Rect& rect);
    void GetViewport (render::obsolete::Rect& out_rect);

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

  private:
    RenderPtr            render; //������
    FramePtr             frame;  //����
    scene_graph::Scene*  scene;  //�����
    scene_graph::Camera* camera; //������
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
///������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadResource   (const char* tag, const char* file_name);
    void UnloadResource (const char* tag, const char* file_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetLogHandler (const LogFunction&);
    const LogFunction& GetLogHandler ();

    void LogPrintf (const char* format, ...);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                 SetQueryHandler (const QueryFunction&);
    const QueryFunction& GetQueryHandler ();

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
///������ � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    Renderable*     GetRenderable (scene_graph::SpriteModel*);  // ������������!!!
    Renderable*     GetRenderable (scene_graph::HeightMap*);  // ������������!!!
    Renderable*     GetRenderable (scene_graph::TextLine*);     // ������������!!!
    ITexture*       GetTexture    (const char* file_name, bool need_alpha, Renderable* renderable = 0);
    SpriteMaterial* GetMaterial   (const char* name);
    RenderableFont* GetFont       (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddFrame (IFrame*);

  private:
    typedef xtl::intrusive_ptr<Renderable> RenderablePtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void InsertRenderable (scene_graph::Entity*, const RenderablePtr&);
    void RemoveRenderable (scene_graph::Entity*);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadMaterialLibrary   (const char* file_name);
    void UnloadMaterialLibrary (const char* file_name);
    void InsertMaterial        (const char* id, const SpriteMaterialPtr&);
    void RemoveMaterial        (const char* id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    TexturePtr CreateTexture        (const char* file_name, bool need_alpha, bool& has_alpha, bool& is_shared, Renderable* renderable, PrerequisitePtr& prerender);
    TexturePtr CreateDynamicTexture (const char* name, PrerequisitePtr& prerender);
    TexturePtr CreateVideoTexture   (const char* name, Renderable* renderable, PrerequisitePtr& prerender);

  private:
    struct RenderableHolder
    {
      RenderablePtr        renderable;
      xtl::auto_connection on_destroy;

      RenderableHolder (const RenderablePtr& in_renderable)
        : renderable (in_renderable) {}
    };

    struct TextureHolder
    {
      TexturePtr      base_texture;   //������� ��������
      TexturePtr      alpha_texture;  //�����-��������
      PrerequisitePtr prerender;      //���������

      TextureHolder (const TexturePtr& in_base_texture, const TexturePtr& in_alpha_texture, const PrerequisitePtr& in_prerender) 
        : base_texture (in_base_texture)
        , alpha_texture (in_alpha_texture)
        , prerender (in_prerender)
      { }
    };

    typedef stl::hash_map<scene_graph::Entity*, RenderableHolder>        RenderableMap;
    typedef stl::hash_map<stl::hash_key<const char*>, SpriteMaterialPtr> MaterialMap;
    typedef stl::hash_map<stl::hash_key<const char*>, TextureHolder>     TextureMap;
    typedef xtl::shared_ptr<RenderableFont>                              RenderableFontPtr;
    typedef stl::hash_map<stl::hash_key<const char*>, RenderableFontPtr> RenderableFontMap;

  private:
    LogFunction       log_handler;       //������� ����������������
    QueryFunction     query_handler;     //������� �������� �������� ��������
    RendererPtr       renderer;          //������� ����������
    RenderableMap     renderables_cache; //��� ��������������� ��������
    MaterialMap       materials;         //���������
    TextureMap        textures;          //��������
    RenderableFontMap fonts;             //������
};

}

}

}

#endif
