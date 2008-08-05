#include "shared.h"

using namespace render;
using namespace script;
using namespace xtl;

namespace
{

/*
    ��������� (����� ���������)
*/

const char* RENDER_VIEWPORT_LIBRARY = "Render.Viewport";

/*
    �������� ��������
*/

Viewport create_viewport ()
{
  return Viewport ();
}

/*
   ����������� ���������� ������ � ����������
*/

void bind_viewport_library (Environment& environment)
{
  InvokerRegistry& lib = environment.CreateLibrary (RENDER_VIEWPORT_LIBRARY);

    //����������� ������� ��������

  lib.Register ("Create", make_invoker (&create_viewport));

    //����������� ��������

  lib.Register ("set_Name",            make_invoker (&Viewport::SetName));
  lib.Register ("get_Name",            make_invoker (&Viewport::Name));
  lib.Register ("set_RenderPath",      make_invoker (&Viewport::SetRenderPath));
  lib.Register ("get_RenderPath",      make_invoker (&Viewport::RenderPath));
  lib.Register ("set_ZOrder",          make_invoker (&Viewport::SetZOrder));
  lib.Register ("get_ZOrder",          make_invoker (&Viewport::ZOrder));
  lib.Register ("set_Camera",          make_invoker (&Viewport::SetCamera));
  lib.Register ("get_Camera",          make_invoker (implicit_cast<scene_graph::Camera* (Viewport::*) ()> (&Viewport::Camera)));
  lib.Register ("set_Active",          make_invoker (&Viewport::SetActive));
  lib.Register ("get_Active",          make_invoker (&Viewport::IsActive));
  lib.Register ("set_BackgroundColor", make_invoker (implicit_cast<void (Viewport::*) (const math::vec4f&)> (&Viewport::SetBackgroundColor)));
  lib.Register ("get_BackgroundColor", make_invoker (&Viewport::BackgroundColor));
  lib.Register ("set_BackgroundState", make_invoker (&Viewport::SetBackgroundState));
  lib.Register ("get_HasBackground",   make_invoker (&Viewport::HasBackground));
  lib.Register ("get_Id",              make_invoker (&Viewport::Id));

  lib.Register ("SetArea",             make_invoker (implicit_cast<void (Viewport::*) (int, int, size_t, size_t)> (&Viewport::SetArea)));
  lib.Register ("SetOrigin",           make_invoker (&Viewport::SetOrigin));
  lib.Register ("SetSize",             make_invoker (&Viewport::SetSize));
  lib.Register ("Activate",            make_invoker (&Viewport::Activate));
  lib.Register ("Deactivate",          make_invoker (&Viewport::Deactivate));
  lib.Register ("SetBackgroundColor",  make_invoker (make_invoker (implicit_cast<void (Viewport::*) (float, float, float, float)> (&Viewport::SetBackgroundColor)),
                 make_invoker<void (Viewport&, float, float, float)> (bind (implicit_cast<void (Viewport::*) (float, float, float, float)> (&Viewport::SetBackgroundColor), _1, _2, _3, _4, 0.f))));
  lib.Register ("EnableBackground",    make_invoker (&Viewport::EnableBackground));
  lib.Register ("DisableBackground",   make_invoker (&Viewport::DisableBackground));
  lib.Register ("SetProperty",         make_invoker (&Viewport::SetProperty));
  lib.Register ("GetProperty",         make_invoker (&Viewport::GetProperty));
  lib.Register ("HasProperty",         make_invoker (&Viewport::HasProperty));
  lib.Register ("RemoveProperty",      make_invoker (&Viewport::RemoveProperty));
  lib.Register ("RemoveAllProperties", make_invoker (&Viewport::RemoveAllProperties));

  environment.RegisterType<Viewport> (RENDER_VIEWPORT_LIBRARY);
}


}

namespace script
{

namespace binds
{

/*
    ����������� ���������� �������
*/

void bind_render_library (Environment& environment)
{
    //����������� ���������
  
  bind_viewport_library (environment);
}

}

}
