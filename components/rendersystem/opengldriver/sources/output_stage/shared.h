#ifndef RENDER_GL_DRIVER_OUTPUT_STAGE_SHARED_HEADER
#define RENDER_GL_DRIVER_OUTPUT_STAGE_SHARED_HEADER

#include <memory.h>

#include <render/low_level/utils.h>

#include <shared/output_stage.h>
#include <shared/context_object.h>
#include <shared/object.h>
#include <shared/trackable.h>
#include <shared/texture_manager.h>
#include <shared/platform/swap_chain_manager.h>

#include <stl/list>

#include <xtl/intrusive_ptr.h>
#include <xtl/trackable_ptr.h>
#include <xtl/bind.h>
#include <xtl/uninitialized_storage.h>

#include <common/exception.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ColorBuffer: virtual public ITexture, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (TextureDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat source_format, const void* buffer);
    void GetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat target_format, void* buffer);

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ColorBuffer (const ContextManager&);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Bind () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void GetSize (size_t& width, size_t& height) = 0;

  private:
    TextureDesc desc; //���������� ��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������-��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DepthStencilBuffer: virtual public ITexture, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (TextureDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat source_format, const void* buffer);
    void GetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat target_format, void* buffer);

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DepthStencilBuffer (const ContextManager&);

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Bind () = 0;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void GetSize (size_t& width, size_t& height) = 0;    

  private:
    TextureDesc desc; //���������� ��������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SwapChainColorBuffer: public ColorBuffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SwapChainColorBuffer (const ContextManager& manager, ISwapChain* swap_chain, size_t buffer_index);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ � ����� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ISwapChain* GetSwapChain   () const { return swap_chain.get (); }
    size_t      GetBufferIndex () const { return buffer_index; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    GLenum GetBufferType () const { return buffer_type; }

  private:
    void Bind ();
    void GetSize (size_t& width, size_t& height);

  private:
    typedef xtl::com_ptr<ISwapChain> SwapChainPtr;

  private:
    SwapChainPtr swap_chain;   //������� ������
    size_t       buffer_index; //������ ������ ������ � ������� ������
    GLenum       buffer_type; //��� ������    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������-��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SwapChainDepthStencilBuffer: public DepthStencilBuffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SwapChainDepthStencilBuffer  (const ContextManager& manager, ISwapChain* swap_chain);
    SwapChainDepthStencilBuffer  (const ContextManager& manager, ISwapChain* swap_chain, size_t width, size_t height);
    ~SwapChainDepthStencilBuffer ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetContextId () const { return context_id; }

  private:
    void Bind ();
    void GetSize (size_t& width, size_t& height);

  private:
    size_t context_id;    //������������� ���������
    size_t width, height; //������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���, ������������ ��� �������� ���������� ����������� ��� �������� ������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct NullView {};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ViewType
{
  ViewType_Null,                        //����������� �����������
  ViewType_SwapChainColorBuffer,        //����������� �� ����� ����� ������� ������
  ViewType_SwapChainDepthStencilBuffer, //����������� �� ����� �������-�������� ������� ������
  ViewType_Texture,                     //����������� �� ��������
//  ViewType_RenderBuffer  //����������� ��������� �� ����� ��������� ��� ����� �����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class View: virtual public IView, public Object, public Trackable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    View (ITexture* texture, const ViewDesc& desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ViewType GetType () { return type; }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ITexture*                    GetTexture                     () { return base_texture.get (); }
    IBindableTexture*            GetBindableTexture             () { return bindable_texture.get (); }
    SwapChainColorBuffer*        GetSwapChainColorBuffer        () { return color_buffer.get (); }
    SwapChainDepthStencilBuffer* GetSwapChainDepthStencilBuffer () { return depth_stencil_buffer.get (); }
//    RenderBuffer*      GetRenderBuffer    () { return render_buffer.get (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (ViewDesc&);

  private:
    typedef xtl::com_ptr<ITexture>                    TexturePtr;
    typedef xtl::com_ptr<IBindableTexture>            BindableTexturePtr;
    typedef xtl::com_ptr<SwapChainColorBuffer>        ColorBufferPtr;
    typedef xtl::com_ptr<SwapChainDepthStencilBuffer> DepthStencilBufferPtr;

  private:
    ViewType              type;                 //��� �����������
    TexturePtr            base_texture;         //��������� �� ������� ��������
    BindableTexturePtr    bindable_texture;     //��������
    ColorBufferPtr        color_buffer;         //������ ����� ������� ������
    DepthStencilBufferPtr depth_stencil_buffer; //����� �������-�������� ������� ������
    ViewDesc              desc;                 //���������� �����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class FrameBuffer
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////  
    virtual ~FrameBuffer () {}
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Bind (bool& color_buffer_state, bool& depth_stencil_buffer_state) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void UpdateRenderTargets () = 0;    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������� �������� ��������� ��������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
class FrameBufferFactory
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ~FrameBufferFactory () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual ITexture* CreateTexture             (const TextureDesc&) = 0;
    virtual ITexture* CreateRenderTargetTexture (ISwapChain* swap_chain, size_t buffer_index) = 0;
    virtual ITexture* CreateDepthStencilTexture (ISwapChain* swap_chain) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual FrameBuffer* CreateFrameBuffer (NullView, NullView) = 0;
    virtual FrameBuffer* CreateFrameBuffer (NullView, SwapChainDepthStencilBuffer*) = 0;
    virtual FrameBuffer* CreateFrameBuffer (NullView, IBindableTexture*, const ViewDesc&) = 0;
    virtual FrameBuffer* CreateFrameBuffer (SwapChainColorBuffer*, NullView) = 0;
    virtual FrameBuffer* CreateFrameBuffer (SwapChainColorBuffer*, SwapChainDepthStencilBuffer*) = 0;
    virtual FrameBuffer* CreateFrameBuffer (SwapChainColorBuffer*, IBindableTexture*, const ViewDesc&) = 0;
    virtual FrameBuffer* CreateFrameBuffer (IBindableTexture*, const ViewDesc&, NullView) = 0;
    virtual FrameBuffer* CreateFrameBuffer (IBindableTexture*, const ViewDesc&, SwapChainDepthStencilBuffer*) = 0;
    virtual FrameBuffer* CreateFrameBuffer (IBindableTexture*, const ViewDesc&, IBindableTexture*, const ViewDesc&) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static FrameBufferFactory* CreateDefaultFactory (const ContextManager&, ISwapChain* default_swap_chain);
    static FrameBufferFactory* CreateFboFactory     (const ContextManager&, FrameBufferFactory* default_factory);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class BlendState: virtual public IBlendState, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    BlendState  (const ContextManager&, const BlendDesc&);
    ~BlendState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDesc (const BlendDesc&);
    void GetDesc (BlendDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind ();

  private:
    BlendDesc desc;         //���������� ���������
    int       display_list; //����� ������ ������ ������������ OpenGL
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DepthStencilState: virtual public IDepthStencilState, public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    DepthStencilState  (const ContextManager&, const DepthStencilDesc&);
    ~DepthStencilState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetDesc (const DepthStencilDesc&);
    void GetDesc (DepthStencilDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� � �������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind (size_t stencil_reference);

  private:
    DepthStencilDesc desc;                           //���������� ���������
    int              display_list;                   //����� ������ ������ ������������ OpenGL
    GLenum           gl_stencil_func [FaceMode_Num]; //������� ��������� ���������
    bool             need_two_side_stencil;          //��������� ������� ������������� ���������
};

}

}

}

#endif
