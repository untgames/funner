#ifndef RENDER_SCENE_SERVER_ENTITY_SHARED_HEADER
#define RENDER_SCENE_SERVER_ENTITY_SHARED_HEADER

#include <bv/axis_aligned_box.h>

#include <shared/sg/node.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Entity: public Node
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Entity  ();
    ~Entity ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                         SetBounds        (bool is_infinite, const bound_volumes::aaboxf& box);
    bool                         IsInfiniteBounds () const;
    const bound_volumes::aaboxf& BoundBox         () const;

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
