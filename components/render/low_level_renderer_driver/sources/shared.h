#ifndef RENDER_MID_LEVEL_LOW_LEVEL_DRIVER_SHARED_HEADER
#define RENDER_MID_LEVEL_LOW_LEVEL_DRIVER_SHARED_HEADER

#include <climits>

#include <stl/string>
#include <stl/vector>

#include <xtl/common_exceptions.h>
#include <xtl/function.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>
#include <xtl/shared_ptr.h>
#include <xtl/string.h>

#include <common/log.h>
#include <common/singleton.h>

#include <media/image.h>

#include <render/low_level/device.h>
#include <render/low_level/driver.h>
#include <render/low_level/utils.h>

#include <render/mid_level/driver.h>
#include <render/mid_level/low_level_driver.h>
#include <render/mid_level/renderer2d.h>

#ifdef _MSC_VER
  #pragma warning (disable : 4250) //'class1' : inherits 'class2::member' via dominance
#endif

namespace render
{

namespace mid_level
{

namespace low_level_driver
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Object: virtual public IObject, public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();    
    void Release ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum RenderTargetType
{
  RenderTargetType_Color,        //����� �����
  RenderTargetType_DepthStencil, //����� ������������� ���������
  
  RenderTargetType_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderTarget: virtual public IRenderTarget, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTarget (render::low_level::IView* render_target_view, RenderTargetType type);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTargetType GetType () { return type; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetWidth  ();
    size_t GetHeight ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������ �������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void CaptureImage (media::Image&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� View
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::low_level::IView* GetView () { return render_target_view.get (); } 
  
  private:
    typedef xtl::com_ptr<render::low_level::IView> IViewPtr;

  private:
    IViewPtr         render_target_view;
    RenderTargetType type;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class BasicFrame: virtual public IFrame, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    BasicFrame ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void           SetRenderTargets      (IRenderTarget* render_target, IRenderTarget* depth_stencil_target);
    IRenderTarget* GetRenderTarget       (); //������� ����� �����
    IRenderTarget* GetDepthStencilTarget (); //������� ����� ������������� ���������

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetViewport (const render::mid_level::Viewport&);
    void GetViewport (render::mid_level::Viewport&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetClearBuffers      (bool clear_render_target, bool clear_depth_stencil_target);
    void GetClearBuffers      (bool& clear_render_target, bool& clear_depth_stencil_target);
    void SetClearColor        (const math::vec4f& color);
    void SetClearDepthStencil (float depth_value, unsigned char stencil_index);
    void GetClearColor        (math::vec4f& color);
    void GetClearDepthStencil (float& depth_value, unsigned char& stencil_index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Draw (render::low_level::IDevice* device);
    
  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void DrawCore (render::low_level::IDevice* device) = 0;

  private:
    typedef xtl::com_ptr<RenderTarget>               RenderTargetPtr;

  private:
    RenderTargetPtr             render_target;
    RenderTargetPtr             depth_stencil_target;
    render::low_level::Viewport viewport;
    render::low_level::Color4f  clear_color;
    float                       clear_depth_value;
    unsigned char               clear_stencil_index;
    bool                        need_clear_render_target;
    bool                        need_clear_depth_stencil_target;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class BasicRenderer: virtual public IRenderer, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    BasicRenderer (render::low_level::IDevice* device, render::low_level::ISwapChain* swap_chain);
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetDescription ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������� ���� ��������
///  (��������� ��� ����������� ������������� ��������, ��������� �� ������ IRenderer)
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetResourcePoolId ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ����� � ������ ������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IRenderTarget* GetColorBuffer ();
    IRenderTarget* GetDepthStencilBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IRenderTarget* CreateDepthStencilBuffer ();
    IRenderTarget* CreateRenderBuffer       ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����� � ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddFrame (IFrame*);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������� / ����� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void DrawFrames   ();
    void CancelFrames ();
    
  private:
    typedef xtl::com_ptr<IRenderTarget>                 RenderTargetPtr;
    typedef xtl::com_ptr<render::low_level::IDevice>    DevicePtr;
    typedef xtl::com_ptr<render::low_level::ISwapChain> SwapChainPtr;
    typedef xtl::com_ptr<BasicFrame>                    FramePtr;
    typedef stl::vector<FramePtr>                       FrameArray;

  protected:
    DevicePtr device;

  private:
    RenderTargetPtr color_buffer;
    RenderTargetPtr depth_stencil_buffer;
    SwapChainPtr    swap_chain;
    FrameArray      frames;
    size_t          resource_pool_id;  
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Driver: virtual public IDriver
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Driver  ();
    ~Driver ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetDescription ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ������ ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      GetRenderersCount ();    
    const char* GetRendererName   (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IRenderer* CreateRenderer (const char* name);    

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������ �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterRenderer       (const char* name, render::low_level::IDevice* device, render::low_level::ISwapChain* swap_chain);
    void UnregisterRenderer     (const char* name);
    void UnregisterAllRenderers ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  () {}
    void Release () {}

  private:
    void UnregisterDriver ();

  private:
    struct RendererEntry
    {
      stl::string                                 renderer_name;
      xtl::com_ptr<render::low_level::IDevice>    device;
      xtl::com_ptr<render::low_level::ISwapChain> swap_chain;

      RendererEntry (const char* in_renderer_name, render::low_level::IDevice* in_device, render::low_level::ISwapChain* in_swap_chain)
        : renderer_name (in_renderer_name), device (in_device), swap_chain (in_swap_chain)
        {}
    };

    typedef xtl::shared_ptr<RendererEntry> RendererEntryPtr;
    typedef stl::vector<RendererEntryPtr>  RendererEntries;

  private:
    RendererEntries renderer_entries;
};

namespace renderer2d
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ImageTexture: virtual public mid_level::renderer2d::ITexture, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ImageTexture  (render::low_level::ITexture*);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetWidth  ();
    size_t GetHeight ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
    media::PixelFormat GetFormat ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������ �������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void CaptureImage (media::Image&);    

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::low_level::ITexture* GetTexture ();

  private:
    typedef xtl::com_ptr<render::low_level::ITexture> ITexturePtr;
    
  private:
    ITexturePtr texture;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� � ������������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderTargetTexture: virtual public mid_level::renderer2d::ITexture, public RenderTarget
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTargetTexture (render::low_level::IView* render_target_view);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct SpriteVertex
{
  math::vec3f position;
  math::vec2f texcoord;
  math::vec4f color;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Primitive: virtual public mid_level::renderer2d::IPrimitive, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Primitive  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetTransform (const math::mat4f&);
    void GetTransform (math::mat4f&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                             SetTexture (mid_level::renderer2d::ITexture*);
    mid_level::renderer2d::ITexture* GetTexture ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::low_level::ITexture* GetLowLevelTexture () { return low_level_texture; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                             SetBlendMode (mid_level::renderer2d::BlendMode blend_mode);
    mid_level::renderer2d::BlendMode GetBlendMode ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetSpritesCount  ();
    void   GetSprite        (size_t index, mid_level::renderer2d::Sprite& sprite);
    size_t AddSprites       (size_t sprites_count, const mid_level::renderer2d::Sprite* sprites);
    void   RemoveSprites    (size_t first_sprite, size_t sprites_count);
    void   RemoveAllSprites ();
    void   ReserveSprites   (size_t sprites_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ��� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SpriteVertex* GetVertexBuffer () { return sprite_vertex_buffer.data (); }

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ������ ��� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void BuildSpriteVertexData (size_t sprite_index);

  private:
    typedef stl::vector<mid_level::renderer2d::Sprite>    SpriteArray;
    typedef xtl::uninitialized_storage<SpriteVertex>      SpriteVertexArray;
    typedef xtl::com_ptr<mid_level::renderer2d::ITexture> TexturePtr;

  private:
    math::mat4f                      transform;
    TexturePtr                       texture;
    render::low_level::ITexture      *low_level_texture;
    mid_level::renderer2d::BlendMode blend_mode;
    SpriteArray                      sprites;
    SpriteVertexArray                sprite_vertex_buffer;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ProgramParameters
{
  math::mat4f view_matrix;
  math::mat4f projection_matrix;
};

class Renderer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� 2D ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Frame: virtual public mid_level::renderer2d::IFrame, public BasicFrame
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Frame  (Renderer* in_renderer, render::low_level::IDevice* device);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���� / ������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetView       (const math::mat4f&);
    void SetProjection (const math::mat4f&);
    void GetView       (math::mat4f&);
    void GetProjection (math::mat4f&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t PrimitivesCount ();
    void   AddPrimitive    (mid_level::renderer2d::IPrimitive*);
    void   Clear           ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void DrawCore (render::low_level::IDevice* device);

  private:
    typedef xtl::com_ptr<Primitive>                      PrimitivePtr;
    typedef stl::vector<PrimitivePtr>                    PrimitiveArray;

  private:
    math::mat4f    view_tm, proj_tm;
    PrimitiveArray primitives;
    Renderer*      renderer;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������� 2D-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Renderer: virtual public mid_level::renderer2d::IRenderer, public BasicRenderer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Renderer  (render::low_level::IDevice* device, render::low_level::ISwapChain* swap_chain);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    mid_level::renderer2d::ITexture*   CreateTexture   (const media::Image& image);
    mid_level::renderer2d::ITexture*   CreateTexture   (size_t width, size_t height, media::PixelFormat pixel_format);
    mid_level::renderer2d::IPrimitive* CreatePrimitive ();
    mid_level::renderer2d::IFrame*     CreateFrame     ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::low_level::IBuffer*     GetConstantBuffer () { return constant_buffer.get (); }
    render::low_level::IBlendState* GetBlendState (render::mid_level::renderer2d::BlendMode blend_mode) { return blend_states[blend_mode].get (); }
    
  private:
    xtl::com_ptr<render::low_level::IProgram>                 program;
    xtl::com_ptr<render::low_level::IProgramParametersLayout> program_parameters_layout;
    xtl::com_ptr<render::low_level::ISamplerState>            sampler;
    xtl::com_ptr<render::low_level::IBuffer>                  constant_buffer;
    xtl::com_ptr<render::low_level::IBlendState>              blend_states[render::mid_level::renderer2d::BlendMode_Num];
};

}

}

}

}

#endif

