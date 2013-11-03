#ifndef RENDER_SCENE_SERVER_NODE_SHARED_HEADER
#define RENDER_SCENE_SERVER_NODE_SHARED_HEADER

#include <stl/auto_ptr.h>

#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>

#include <render/scene/interchange/types.h>

namespace render
{

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Node: public xtl::reference_counter, public xtl::noncopyable
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Node  ();
    ~Node ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetName (const char* name);
    const char* Name    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetWorldMatrix (const math::mat4f&);
    const math::mat4f& WorldMatrix    () const;

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

typedef xtl::intrusive_ptr<Node> NodePtr;

}

}

}

#endif
