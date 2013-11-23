#ifndef RENDER_SCENE_SERVER_VISUAL_MODEL_SHARED_HEADER
#define RENDER_SCENE_SERVER_VISUAL_MODEL_SHARED_HEADER

#include <shared/sg/entity.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class VisualModel: public Entity
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VisualModel  ();
    ~VisualModel ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetScissor (Node*);
    Node* Scissor    () const;

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void VisitCore (ISceneVisitor&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif
