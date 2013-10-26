//forward declarations
class Scene;
class SceneObject;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct SceneUpdateListNode
{
  SceneObject* prev_update;
  SceneObject* next_update;
  bool         need_update;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct SceneUpdateList
{
  SceneObject* first;
  SceneObject* last;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class SceneObject: private SceneUpdateListNode
{
  friend class SceneManager;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    SceneObject  (Scene&);
    ~SceneObject ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateNotify ();

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    client::Connection& Connection () { return scene.Connection (); }

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void UpdateCore () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update ();

  private:
    SceneObject (const SceneObject&); //no implementation
    SceneObject& operator = (const SceneObject&); //no implementation

  private:
    Scene& scene;
};
