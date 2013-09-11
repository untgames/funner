///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderableView: public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderableView  (const ConnectionPtr& connection, scene_graph::Viewport& viewport);
    ~RenderableView ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    interchange::uint8 Id ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const scene_graph::Viewport& Viewport ();   

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Synchronize ();

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

typedef xtl::intrusive_ptr<RenderableView> RenderableViewPtr;
