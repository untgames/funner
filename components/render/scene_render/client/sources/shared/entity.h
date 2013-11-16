#ifndef RENDER_SCENE_CLIENT_ENTITY_SHARED_HEADER
#define RENDER_SCENE_CLIENT_ENTITY_SHARED_HEADER

#include <sg/entity.h>

#include <shared/node.h>

namespace render
{

namespace scene
{

namespace client
{


///////////////////////////////////////////////////////////////////////////////////////////////////
///��������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Entity: public Node
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Entity  (scene_graph::Entity&, SceneManager&, interchange::NodeType node_type = interchange::NodeType_Entity);
    ~Entity ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    scene_graph::Entity& SourceNode () const { return static_cast<scene_graph::Entity&> (Node::SourceNode ()); }

  protected:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateCore (client::Context&);

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

}

}

#endif
