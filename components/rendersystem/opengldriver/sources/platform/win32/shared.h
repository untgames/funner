#ifndef RENDER_GL_DRIVER_WIN32_SHARED_HEADER
#define RENDER_GL_DRIVER_WIN32_SHARED_HEADER

#define _WIN32_WINNT 0x0501 //for ChangeDisplaySettings

#include <windows.h>
#include <gl/glew.h>
#include <gl/wglew.h>

#include <shared/output_manager.h>
#include <shared/context_manager.h>
#include <shared/object.h>
#include <shared/property_list.h>
#include <shared/context.h>

#include <xtl/intrusive_ptr.h>

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

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �����-����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetGammaRamp (const Color3f table [256]);
    void GetGammaRamp (Color3f table [256]);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    HDC GetDC ();

//////////////////////////////////////////////////////////////////////////////////////////////////
///������ ������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IPropertyList* GetProperties ();
    
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
class SwapChain: virtual public ISwapChain, public Object
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SwapChain  (OutputManager&, const SwapChainDesc& desc);
    ~SwapChain ();
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void GetDesc (SwapChainDesc&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IOutput* GetOutput ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������� ������� ������ � ��������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Present ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ��������� full-screen mode
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetFullscreenState (bool state);
    bool GetFullscreenState ();
    
  private:
    typedef xtl::com_ptr<Output> OutputPtr;

  private:
    OutputPtr     output;                //��������� �� ���������� ������
    HWND          output_window;         //���� ������
    HDC           output_device_context; //�������� ���������� ������
    WGLEWContext  wglew_context;         //�������� WGLEW
    SwapChainDesc desc;                  //���������� ������� ������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
void check_errors (const char* source);
void raise_error  (const char* source);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ������� ������������� Windows OpenGL
///////////////////////////////////////////////////////////////////////////////////////////////////
HWND  create_dummy_window        (HWND parent);        //�������� ���������������� ����
HDC   get_device_context         (HWND window);        //��������� ��������� ����
HGLRC create_opengl_context      (HDC device_context); //�������� ��������� OpenGL
void  init_wglew_context         (const SwapChainDesc& swap_chain_desc, WGLEWContext* wglew_context); //������������� ��������� wglew
void  set_current_opengl_context (HDC device_context, HGLRC gl_context);                              //��������� �������� ��������� OpenGL
void  set_current_glew_context   (const GLEWContext*, const WGLEWContext* context);                   //��������� �������� ��������� GLEW/WGLEW
void  set_pixel_format           (HDC device_context, const SwapChainDesc& swap_chain_desc);          //��������� ������� ��������
void  get_pixel_format           (HDC device_context, SwapChainDesc& swap_chain_desc);                //��������� ������� ��������

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� WGLEW (��� ������� ������� ������ �� ���������� WGLEW)
///////////////////////////////////////////////////////////////////////////////////////////////////
const WGLEWContext* wglewGetContext ();

}

}

}

#endif
