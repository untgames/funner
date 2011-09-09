///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TraverseResults
{
  typedef stl::vector<Renderable> RenderableArray;
//  typedef stl::vector<Light>      LightArray;
  
  RenderableArray renderables; //������ ������������ ��������
//  LightArray      lights;      //������ ���������� �����  
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �������� ��� ������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class IVisitor
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void Visit (Node& entity) {}
    virtual void Visit (Renderable& entity) {}
    virtual void Visit (VisualModel& entity) {}
    virtual void Visit (Light& entity) {}    

  protected:
    virtual ~IVisitor () {}
};

