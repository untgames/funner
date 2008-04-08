#ifndef DEMO_WATER_SLIDES_SHARED_HEADER
#define DEMO_WATER_SLIDES_SHARED_HEADER

#include <time.h>

#include <stl/auto_ptr.h>

#include <xtl/intrusive_ptr.h>
#include <xtl/function.h>
#include <xtl/bind.h>

#include <common/file.h>
#include <common/streams.h>
#include <common/strlib.h>

#include <syslib/window.h>
#include <syslib/application.h>

#include <media/image.h>

#include <render/low_level/driver.h>
#include <render/low_level/device.h>
#include <render/low_level/utils.h>
#include <render/low_level/opengl_driver.h>

typedef xtl::com_ptr<render::low_level::IDriver>                  DriverPtr;
typedef xtl::com_ptr<render::low_level::ISwapChain>               SwapChainPtr;
typedef xtl::com_ptr<render::low_level::IDevice>                  DevicePtr;
typedef xtl::com_ptr<render::low_level::ITexture>                 TexturePtr;
typedef xtl::com_ptr<render::low_level::ISamplerState>            SamplerStatePtr;
typedef xtl::com_ptr<render::low_level::IView>                    ViewPtr;
typedef xtl::com_ptr<render::low_level::IBlendState>              BlendStatePtr;
typedef xtl::com_ptr<render::low_level::IDepthStencilState>       DepthStencilStatePtr;
typedef xtl::com_ptr<render::low_level::IInputLayout>             InputLayoutPtr;
typedef xtl::com_ptr<render::low_level::IBuffer>                  BufferPtr;
typedef xtl::com_ptr<render::low_level::IRasterizerState>         RasterizerStatePtr;
typedef xtl::com_ptr<render::low_level::IProgram>                 ProgramPtr;
typedef xtl::com_ptr<render::low_level::IProgramParametersLayout> ProgramParametersLayoutPtr;
typedef xtl::com_ptr<render::low_level::IPredicate>               PredicatePtr;

//����� ����������
class MyApplication
{
  public:
      //��������� ���������� ����������
    static MyApplication& Instance ();
    
      //����������������
    void LogMessage        (const char* message);
    void LogFormatMessage  (const char* format, ...);
    void VLogFormatMessage (const char* format, va_list list);
    
      //��������� ���������� ����������, ��������� �� ������� ������� ����������
    static size_t Milliseconds ();
  
  private:
      //������������ / ���������� / ������������
    MyApplication  ();
    ~MyApplication ();

    MyApplication  (const MyApplication&); // no impl
    MyApplication& operator = (const MyApplication&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

#endif
