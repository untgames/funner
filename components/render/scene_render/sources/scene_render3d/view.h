///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class View: public xtl::noncopyable, public xtl::reference_counter, public ISceneRender
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    View  (RenderManager&, const char* technique);
    ~View ();    

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::Frame& Frame ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateCamera (scene_graph::Camera* camera);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateProperties (const common::PropertyMap&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateFrame ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();
    void Release ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* TechniqueName ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void ResetTechniqueCache ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};
