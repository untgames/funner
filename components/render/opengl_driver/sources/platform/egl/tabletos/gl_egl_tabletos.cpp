#include "../shared.h"

using namespace render::low_level;
using namespace render::low_level::opengl;
using namespace render::low_level::opengl::egl;

namespace render
{

namespace low_level
{

namespace opengl
{

namespace egl
{

void setup_window (const void* window_handle, const SwapChainDesc& desc)
{
  try
  {
    screen_window_t window = (screen_window_t)window_handle;

      //Set pixel format
    
    int format = SCREEN_FORMAT_RGBX8888;
   
    switch (desc.frame_buffer.color_bits)
    {
      case 32:
        if (desc.frame_buffer.alpha_bits)
          throw xtl::format_operation_exception ("", "Can't create primary swap chain with color bits %u alpha bits %u", desc.frame_buffer.color_bits, desc.frame_buffer.alpha_bits);

        format = SCREEN_FORMAT_RGBX8888;

        break;
      case 24:
        switch (desc.frame_buffer.alpha_bits)
        {
          case 0:
            format = SCREEN_FORMAT_RGBX8888;
            break;
          case 8:
            format = SCREEN_FORMAT_RGBA8888;
            break;
          default:
            throw xtl::format_operation_exception ("", "Can't create primary swap chain with color bits %u alpha bits %u", desc.frame_buffer.color_bits, desc.frame_buffer.alpha_bits);
        }

        break;
      case 16:
        switch (desc.frame_buffer.alpha_bits)
        {
          case 0:
            format = SCREEN_FORMAT_RGBX5551;
            break;
          case 1:
            format = SCREEN_FORMAT_RGBA5551;
            break;
          case 4:
            format = SCREEN_FORMAT_RGBA4444;
            break;
          default:
            throw xtl::format_operation_exception ("", "Can't create primary swap chain with color bits %u alpha bits %u", desc.frame_buffer.color_bits, desc.frame_buffer.alpha_bits);
        }

        break;
      default:
        throw xtl::format_operation_exception ("", "Can't create primary swap chain with color bits %u", desc.frame_buffer.color_bits);
    }

    if (screen_set_window_property_iv (window, SCREEN_PROPERTY_FORMAT, &format))
      raise_error ("::screen_set_window_property_iv(SCREEN_PROPERTY_FORMAT)");
      
      //Set usage
      
    int usage = 0;

    if (screen_get_window_property_iv (window, SCREEN_PROPERTY_USAGE, &usage))
      raise_error ("screen_get_window_property_iv(SCREEN_PROPERTY_USAGE)");
   
    usage |= SCREEN_USAGE_OPENGL_ES1;

    if (screen_set_window_property_iv (window, SCREEN_PROPERTY_USAGE, &usage))
      raise_error ("screen_set_window_property_iv(SCREEN_PROPERTY_USAGE)");
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::low_level::opengl::egl::setup_window");
    throw;
  }
}

}

}

}

}