#ifndef RENDER_GL_DRIVER_WIN32_SHARED_HEADER
#define RENDER_GL_DRIVER_WIN32_SHARED_HEADER

#define _WIN32_WINNT 0x0501 //for ChangeDisplaySettingsEx

#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>

#include <shared/platform/output_manager.h>
#include <shared/platform/swap_chain_manager.h>
#include <shared/platform/context.h>
#include <shared/object.h>
#include <shared/property_list.h>
#include <shared/trackable.h>

#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>
#include <xtl/bind.h>

#include <stl/vector>
#include <stl/string>

#include <common/exception.h>
#include <common/strlib.h>

namespace render
{

namespace low_level
{

namespace opengl
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Output: virtual public IOutput, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Output  (const DISPLAY_DEVICE&);
    ~Output ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetName ();
    const char* GetWinName () { return win_name.c_str (); }

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ��������� � �������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetScreenRect (Rect&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();

  private:    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������������ ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    HDC GetDC ();    
    
  private:
    typedef stl::vector<OutputModeDesc> OutputModeArray;

  private:
    stl::string     name;        //��� ����������
    stl::string     win_name;    //��� ���������� � Windows
    PropertyList    properties;  //�������� ����������
    OutputModeArray modes;       //������ ������ ����������
    HDC             hDC;         //����� ��������� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class SwapChain: virtual public ISwapChain, public Object, public Trackable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� ������ / WGLEW ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual HDC                 GetDC           () = 0;
    virtual const WGLEWContext* GetWGLEWContext () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �� ������� ������ ��������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
//    typedef xtl::slot<void ()> LostDCHandler;

//    virtual void RegisterLostDCHandler (LostDCHandler&) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class PrimarySwapChain: public SwapChain
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PrimarySwapChain  (IOutput* output, const SwapChainDesc& desc);
    ~PrimarySwapChain ();
  
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
///�������� ���������� ������ / WGLEW ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    HDC                 GetDC           () { return output_context; }
    const WGLEWContext* GetWGLEWContext () { return &wglew_context; }

  private:
    typedef xtl::com_ptr<IOutput> OutputPtr;

  private:
    WGLEWContext     wglew_context;  //�������� WGLEW
    HWND             output_window;  //���� ������
    HDC              output_context; //�������� ������
    OutputPtr        output;         //��������� �� ���������� ������    
    SwapChainDesc    desc;           //���������� ������� ������    
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///PBuffer
///////////////////////////////////////////////////////////////////////////////////////////////////
  //������� �������� �� ������� PBuffer!!!
class PBuffer: public SwapChain
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    PBuffer  (PrimarySwapChain* primary_swap_chain, const SwapChainDesc& desc);
    ~PBuffer ();

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
///�������� ���������� ������ / WGLEW ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    HDC                 GetDC           ();
    const WGLEWContext* GetWGLEWContext ();

  private:
    typedef xtl::com_ptr<PrimarySwapChain> SwapChainPtr;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / ����������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////    
    void Create  ();
    void Destroy ();
    
  private:
    SwapChainPtr  primary_swap_chain; //�������� ������� ������
    SwapChainDesc desc;               //���������� ������
    HPBUFFERARB   pbuffer;            //���������� PBuffer'�
    HDC           output_context;     //�������� ���������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � ��������� ��������� ������ GetLastError ()
///////////////////////////////////////////////////////////////////////////////////////////////////
void raise_error (const char* source);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� / ������ ���������� � ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
int  choose_pixel_format (HDC device_context, const SwapChainDesc& swap_chain_desc);          //����� ������� ��������
void get_pixel_format    (HDC device_context, int format, SwapChainDesc& swap_chain_desc);    //��������� ������� ��������

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� ��������� WGLEW
///////////////////////////////////////////////////////////////////////////////////////////////////
void init_wglew_context (const SwapChainDesc& swap_chain_desc, WGLEWContext* wglew_context);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������/��������� ��������� GLEW/WGLEW (��� ������� ������� ������ �� ���������� GLEW)
///////////////////////////////////////////////////////////////////////////////////////////////////
void                glewSetContext  (const GLEWContext*);
void                wglewSetContext (const WGLEWContext*);
const GLEWContext*  glewGetContext  ();
const WGLEWContext* wglewGetContext ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������ � WGLEW ���������� (��������� ��������, ������������� ���������, ��������������� ��������)
///////////////////////////////////////////////////////////////////////////////////////////////////
class WGLEWScope
{
  public:
    WGLEWScope  ();
    WGLEWScope  (const WGLEWContext* new_context);
    ~WGLEWScope ();

  private:
    WGLEWScope (const WGLEWScope&); //no impl
    WGLEWScope& operator = (const WGLEWScope&); //no impl
    
  private:
    const WGLEWContext* old_context;
};

}

}

}

#endif
