#ifndef RENDER_GL_DRIVER_GLX_SHARED_HEADER
#define RENDER_GL_DRIVER_GLX_SHARED_HEADER

#include <dlfcn.h>

#include <stl/algorithm>
#include <stl/auto_ptr.h>
#include <stl/hash_map>
#include <stl/vector>

#include <xtl/bind.h>
#include <xtl/intrusive_ptr.h>

#include <common/singleton.h>
#include <common/strlib.h>

#include <syslib/window.h>
#include <syslib/platform/x11.h>

#include <render/low_level/utils.h>

#include <shared/log.h>
#include <shared/object.h>
#include <shared/platform.h>
#include <shared/property_list.h>

#ifndef NO_XRAND
#define HAS_XRANDR
#endif

#ifndef NO_X86VMODE
#define HAS_X86VMODE
#endif

/* Xlib.h is the default header that is included and has the core functionallity */
#include <X11/Xlib.h>

/* X RandR is used to configure which display ports are enabled (e.g. LCD, VGA and DVI), 
 * and to configure display modes and properties such as orientation, reflection and DPI.
 */
#ifdef HAS_XRANDR
#include <X11/extensions/Xrandr.h>
#endif

/* The XF86 Video Mode extension allows us to change the displaymode of the server
 * this allows us to set the display to fullscreen and also read videomodes and   
 * other information.                                                             
 */  
#ifdef HAS_X86VMODE
#include <X11/extensions/xf86vmode.h>
#endif

#include <GL/gl.h>
#include <GL/glx.h>

namespace render
{

namespace low_level
{

namespace opengl
{

namespace glx
{

//forward declarations
class Adapter;
class DynamicLibrary;

struct GlxExtensionEntries
{
  void Init (ILibrary&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ������������ ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum Caveat
{
  Caveat_None,                  //������������ ������ ����� �� ����� ��������������
  Caveat_Slow_Config,           //�����-���� ������ ������������ ������ ����� ����������� ���������, ��� ������ ������������
  Caveat_Non_Conformant_COnfig, //�����-���� ������ ������������ ������ ����� �����������
  
  Caveat_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct PixelFormatDesc
{
  Adapter*                   adapter;                 //�������, �������������� ��������� ������
  const GlxExtensionEntries* glx_extension_entries;   //������� GLX-���������� (������ ���� ����������� � ������, ���������� PixelFormatDesc, ����� ���� 0)
  GLXFBConfig                config;                  //������������ GLX-������ �����
  int                        pixel_format_index;      //����� ������������ GLX-������ �����
  int                        visual_id;               //
  size_t                     color_bits;              //���������� ��� �� ����
  size_t                     alpha_bits;              //���������� ��� �� �����
  size_t                     depth_bits;              //���������� ��� �� �������
  size_t                     stencil_bits;            //���������� ��� �� ��������
  size_t                     samples_count;           //���������� sample'�� (0=multisample off)
  size_t                     buffers_count;           //���������� ������� � ������� ������ (0=default 2 buffers)
  SwapMethod                 swap_method;             //����� ������ ������� � ��������� �������
  size_t                     aux_buffers;             //���������� ��������������� ������� ���������
  size_t                     max_pbuffer_width;       //������������ ������ PBuffer
  size_t                     max_pbuffer_height;      //������������ ������ PBuffer
  size_t                     max_pbuffer_pixels;      //������������ ���������� �������� ��� PBuffer
  bool                       support_stereo;          //��������� ������-����������  
  bool                       support_draw_to_window;  //��������� ��������� � Window
  bool                       support_draw_to_pbuffer; //��������� ��������� � PBuffer
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Output: virtual public IOutput, public Object
{
  public:
    typedef xtl::com_ptr<Output> Pointer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    Output  (Display* display, int screen_number);
    ~Output ();    

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    int GetScreenNumber ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ �����-�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t GetModesCount ();
    void   GetModeDesc   (size_t mode_index, OutputModeDesc& mode_desc);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� �����-������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetCurrentMode (const OutputModeDesc&);
    void GetCurrentMode (OutputModeDesc&);
    void RestoreDefaultMode ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetGammaRamp (const Color3f table [256]);
    void GetGammaRamp (Color3f table [256]);
    
  private:
    Output (const Output&); //no impl
    Output& operator = (const Output&); //no impl
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����, ��������������� ������ � ��������������� ������������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class OutputManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    OutputManager  ();
    ~OutputManager ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t  GetOutputsCount () const;
    Output* GetOutput       (size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� ������, ���������� �������� � ����� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Output* FindContainingOutput (Window window) const;

  private:
    OutputManager (const OutputManager&); //no impl
    OutputManager& operator = (const OutputManager&); //no impl

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IContextLostListener
{
  public:
    virtual void OnLostCurrent () = 0;

  protected:
    virtual ~IContextLostListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
class AdapterLibrary: virtual public ILibrary, public xtl::reference_counter
{
  public:
    typedef xtl::intrusive_ptr<AdapterLibrary> Pointer;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static Pointer LoadLibrary (const char* path);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ~AdapterLibrary ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    GLXPbuffer CreatePbuffer  (Display *dpy, GLXFBConfig config, const int *attrib_list); //�������� ����������� ������� ����������
    void       DestroyPbuffer (Display *dpy, GLXPbuffer pbuf);                            //����������� ����������� ������� ����������

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� � �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    GLXContext CreateContext (Display *dpy, GLXFBConfig config, int render_type, GLXContext share_list, Bool direct); //�������� ������ ��������� GLX-����������
    void       DestroyContext (Display *dpy, GLXContext ctx); //�������� ��������� GLX-����������

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool MakeCurrent (Display *dpy, GLXDrawable drawable, GLXContext ctx, IContextLostListener* = 0);
                              
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ��������� � drawable
///////////////////////////////////////////////////////////////////////////////////////////////////
    GLXContext  GetCurrentContext      (); //��������� �������� ���������
    GLXDrawable GetCurrentDrawable     (); //��������� ������� ������� drawable
    GLXDrawable GetCurrentReadDrawable (); //��������� ������� ������� drawable ��� ������
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    //���������� ���������� � ������������ GLX-������ �����
    int GetFBConfigAttrib (Display *dpy, GLXFBConfig config, int attribute, int *value); 
    
    //���������� ������ ���� ������������ GLX-������ ����� ��� ������� ������
    GLXFBConfig* GetFBConfigs (Display *dpy, int screen, int *nelements);
    
    //���������� ������ ������������ GLX-������ �����, ��������������� �������� ���������
    GLXFBConfig* ChooseFBConfig (Display *dpy, int screen, int *attrib_list, int *nelements);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������� �������� � �������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SwapBuffers (Display *dpy, GLXDrawable drawable);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ �������������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetExtensionsString (Display *dpy, int screen);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ����� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const void* GetProcAddress (const char* name, size_t search_flags);

  private:
    AdapterLibrary (stl::auto_ptr<DynamicLibrary>&);
    
  private:
    AdapterLibrary (const AdapterLibrary&);             //no impl
    AdapterLibrary& operator = (const AdapterLibrary&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

typedef xtl::intrusive_ptr<AdapterLibrary> AdapterLibraryPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Adapter: virtual public IAdapter, public Object
{
  friend class Output;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Adapter  (const char* name, const char* dll_path, const char* init_string);
    ~Adapter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �������� / ���� � ������ / ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName        ();
    const char* GetPath        ();
    const char* GetDescription ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t   GetOutputsCount ();
    IOutput* GetOutput       (size_t index);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    AdapterLibrary& GetLibrary ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Output::Pointer GetOutput (Window window);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ��������� �������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef stl::vector<PixelFormatDesc>     PixelFormatArray;
    typedef stl::vector<GlxExtensionEntries> GlxExtensionEntriesArray;

    void EnumPixelFormats (int screen, PixelFormatArray& pixel_formats, GlxExtensionEntriesArray& entries);

  private:
    Adapter (const Adapter&); //no impl
    Adapter& operator = (const Adapter&); //no impl    

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ISwapChainImpl: virtual public ISwapChain
{
  public:
    virtual Adapter*                   GetAdapterImpl         () = 0; //��������� ���������� ��������
    virtual Display*                   GetDisplay             () = 0; //���������� ����������� ��� �������� ���������
    virtual Window                     GetWindow              () = 0; //���� ���������
    virtual GLXFBConfig                GetFBConfig            () = 0; //������������ ������ �����
    virtual const GlxExtensionEntries& GetGlxExtensionEntries () = 0; //��������� ������� GLX-����������

  protected:
    virtual ~ISwapChainImpl () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class PrimarySwapChain: virtual public ISwapChainImpl, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimarySwapChain  (const SwapChainDesc& sc_desc, const PixelFormatDesc& pf_desc);
    ~PrimarySwapChain ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IAdapter * GetAdapter     ();
    Adapter  * GetAdapterImpl ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� ��� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Display * GetDisplay ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Window GetWindow ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� GLX-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const GlxExtensionEntries& GetGlxExtensionEntries ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    GLXFBConfig GetFBConfig ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (SwapChainDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ������ � ������������ �������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IOutput* GetContainingOutput ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ��������� full-screen mode
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetFullscreenState (bool state);
    bool GetFullscreenState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� ������� ������ � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Present ();    

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();
    
  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///PBuffer
///////////////////////////////////////////////////////////////////////////////////////////////////
class PBuffer: virtual public ISwapChainImpl, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PBuffer  (PrimarySwapChain* primary_swap_chain, size_t width, size_t height);
    PBuffer  (PrimarySwapChain* swap_chain);
    ~PBuffer ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IAdapter* GetAdapter ();
    Adapter*  GetAdapterImpl ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (SwapChainDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ������ � ������������ �������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IOutput* GetContainingOutput ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ��������� full-screen mode
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetFullscreenState (bool state);
    bool GetFullscreenState ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� ������� ������ � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Present ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� ��� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Display* GetDisplay ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Window GetWindow ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� GLX-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const GlxExtensionEntries& GetGlxExtensionEntries ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    GLXFBConfig GetFBConfig ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Context: virtual public IContext, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Context  (ISwapChain* swap_chain);
    ~Context ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void MakeCurrent (ISwapChain* swap_chain);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������� ������� ������ � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsCompatible (ISwapChain* swap_chain);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ���������� OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
    AdapterLibrary& GetLibrary ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachListener (IContextListener*);
    void DetachListener (IContextListener*);

  private:
    Context (const Context&); //no impl
    Context& operator = (const Context&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ � ������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
int     get_screen_number (Window window);
Screen* get_screen        (Window window);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
void check_errors (const char* source);
void raise_error  (const char* source);

using syslib::x11::DisplayManager;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� X11
///////////////////////////////////////////////////////////////////////////////////////////////////
class DisplayLock
{
  public:
    DisplayLock () : display ((Display*)DisplayManager::DisplayHandle ())
    {
      XLockDisplay (display);    
    }
  
    DisplayLock (Display* in_display) : display (in_display)
    {
      XLockDisplay (display);
    }

    ~DisplayLock ()
    {
      XUnlockDisplay (display);
    }

  private:
    Display* display;
};

}

}

}

}

#endif
