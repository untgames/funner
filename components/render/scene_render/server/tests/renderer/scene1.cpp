#include "shared.h"

struct Test
{
  RenderTarget&            target;
  scene_graph::StaticMesh& mesh;

  Test (RenderTarget& in_target, scene_graph::StaticMesh& in_mesh)
    : target (in_target)
    , mesh (in_mesh)
  {
  }
};

void log_print (const char* log_name, const char* message)
{
  printf ("%s: %s\n", log_name, message);
  fflush (stdout);
}

void on_window_close ()
{
  syslib::Application::Exit (0);
}

void idle (Test& test)
{
  try
  {
    static size_t last_fps = 0;
    static size_t frames_count = 0;

    if (common::milliseconds () - last_fps > 1000)
    {
      printf ("FPS: %.2f\n", float (frames_count)/float (common::milliseconds () - last_fps)*1000.f);
      fflush (stdout);

      last_fps = common::milliseconds ();
      frames_count = 0;
      return;
    }
    
    frames_count++;
    
    float angle = common::milliseconds () / 10000.0f;
    
    test.mesh.SetWorldOrientation (math::degree (angle), 0.0f, 0.0f, 1.0f);        

    test.target.Update ();      
  }
  catch (std::exception& e)
  {
    printf ("exception in idle: %s\n", e.what ());
  }  
}

int main ()
{
  printf ("Results of scene1_test:\n");

  try
  {
    common::LogFilter log_filter ("render.*", &log_print);

    syslib::Window window (syslib::WindowStyle_Overlapped, 400, 300);

    window.RegisterEventHandler (syslib::WindowEvent_OnClose, xtl::bind (&on_window_close));

    const char* SERVER_NAME = "MyServer";

    Server server (SERVER_NAME);
    Client client (SERVER_NAME);

    common::PropertyMap window_properties;
    
    window_properties.SetProperty ("ColorBits", 24);
    window_properties.SetProperty ("DepthBits", 16);

    server.AttachWindow ("my_window", window, window_properties);

    client.LoadResource ("data/render.rfx");
    client.LoadResource ("data/u1/texture0000.dds");
    client.LoadResource ("data/u1/texture0001.dds");
    client.LoadResource ("data/u1/texture0002.dds");
    client.LoadResource ("data/u1.xmtl");
    client.LoadResource ("data/u1.binmesh");

    RenderTarget target = client.CreateRenderTarget ("my_window", "color_binding=main_color_target depth_stencil_binding=main_depth_stencil_target");

    scene_graph::Screen screen;
    
    target.SetScreen (&screen);
    
    screen.SetBackgroundState (false);    

    scene_graph::OrthoCamera::Pointer camera = scene_graph::OrthoCamera::Create ();
    
    camera->SetLeft   (-10.0f);
    camera->SetRight  (10.0f);    
    camera->SetBottom (-10.0f);
    camera->SetTop    (10.0f);    
    camera->SetZNear  (-1000.0f);
    camera->SetZFar   (1000.0f);    

    camera->SetPosition (0, 400.0f, 0.0f);
    camera->LookTo (math::vec3f (0.0f), math::vec3f (0, 1.0f, 0), scene_graph::NodeTransformSpace_World);
    
    scene_graph::Scene scene;
    
    camera->BindToScene (scene);
    
    scene_graph::StaticMesh::Pointer model = scene_graph::StaticMesh::Create ();
    
    model->SetMeshName ("u1.polySurface2.mesh#0");

    model->BindToScene (scene);    
    
      //��������� ������� ������
    
    scene_graph::Viewport vp;
    
    vp.SetArea       (0, 0, 100, 100);
    vp.SetCamera     (&*camera);
    vp.SetTechnique  ("default");
    
    screen.Attach (vp);

    window.Show ();    

    Test test (target, *model);

    syslib::Application::RegisterEventHandler (syslib::ApplicationEvent_OnIdle, xtl::bind (&idle, xtl::ref (test)));
    
    syslib::Application::Run ();
  }
  catch (std::exception& e)
  {
    printf ("%s\n", e.what ());
  }
}
