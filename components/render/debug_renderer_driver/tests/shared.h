#include <cstdio>
#include <exception>

#include <xtl/intrusive_ptr.h>
#include <xtl/function.h>
#include <xtl/connection.h>

#include <common/log.h>

#include <media/image.h>

#include <render/mid_level/driver.h>
#include <render/mid_level/renderer2d.h>

using namespace render::mid_level;
using namespace render::mid_level::renderer2d;

typedef xtl::com_ptr<IDriver>                      DriverPtr;
typedef xtl::com_ptr<render::mid_level::IRenderer> RendererPtr;
typedef xtl::com_ptr<renderer2d::IRenderer>        Renderer2dPtr;
typedef xtl::com_ptr<renderer2d::ITexture>         Texture2dPtr;
typedef xtl::com_ptr<renderer2d::IPrimitive>       Primitive2dPtr;
typedef xtl::com_ptr<renderer2d::IFrame>           Frame2dPtr;

//��騩 ��� ��⮢
class Test
{
  public:
    Test ()
    {
      log_connection = common::LogSystem::RegisterLogHandler ("render.mid_level.Debug", &Print);
    }
    
    ~Test ()
    {
      DriverManager::UnregisterDriver ("Debug"); //�஢�ઠ ���४⭮�� 㤠�����
    }    

  private:
    static void Print (const char*, const char* message)
    {
      printf ("%s\n", message);
    }
  
  private:
    xtl::auto_connection log_connection;  
};
