#include "shared.h"

using namespace scene_graph;
using namespace bound_volumes;
using namespace stl;
using namespace common;
using namespace xtl;

/*
    �������� ���������� �����
*/

//typedef xtl::com_ptr<ISceneManager> SceneManagerPtr;
typedef com_ptr<Node> NodePtr;

struct Scene::Impl: public SceneSpace
{
//  SceneManagerPtr scene_manager; //�������� �����
  string  name; //��� �����  
  NodePtr root; //������ �����
  
  template <class Fn>
  void ForEach (Fn& fn)
  {
    SceneObject* object = FirstObject ();    

    for (size_t count=ObjectsCount (); count--; object=object->NextObject ())
      fn (object->Entity ());
  }  
};

/*
    ����������� / ����������
*/

Scene::Scene ()
  : impl (new Impl)
{
    //�������� ��������� ���� �����
    
  try
  {
    impl->root = Node::Create ();
    
      //��������� ��������� �� ������ �����

    impl->root->SetScene (this);        
  }
  catch (...)
  {
    delete impl;
    throw;
  }   
}

Scene::~Scene ()
{
    //������������ ����� �����

  impl->root->UnbindAllChildren ();

    //�������� ����������
  
  delete impl;
}
    
/*
    ��� �����
*/

void Scene::SetName (const char* name)
{
  if (!name)
    throw xtl::make_null_argument_exception ("scene_graph::Scene::SetName", "name");
    
  impl->name = name;
}

const char* Scene::Name () const
{
  return impl->name.c_str ();
}

/*
    ������ �����
*/

Node& Scene::Root ()
{
  return *impl->root;
}

const Node& Scene::Root () const
{
  return *impl->root;
}

/*
    ���������� �������� � �����
*/

size_t Scene::EntitiesCount () const
{
  return impl->ObjectsCount ();
}

/*
    ����������� �������� �����
*/

void Scene::Attach (SceneObject& object)
{
  object.BindToSpace (impl);
}

/*
    �������� ��� ������ �������� �����
*/

namespace
{

//������� ��� �������� ����������
struct VisitorWrapper
{
  VisitorWrapper (Scene::Visitor& in_visitor) : visitor (in_visitor) {}

  void operator () (Entity& entity) const
  {
    entity.Accept (visitor);
  }

  Scene::Visitor& visitor;
};

//������� ��� �������� ��������� � ��������� ��������� �������� � �������������� �����
template <class Bound, class Fn>
struct BoundsCheckFunction
{
  BoundsCheckFunction (const Bound& in_bound, Fn& in_fn) : bound (in_bound), fn (in_fn) {}
  
  template <class Entity> void operator () (Entity& entity) const
  {
      //���� ������ ����� ����������� �������������� ������ - ������������ ���

    if (entity.IsInfiniteBounds ())
    {
      fn (entity);
      return;
    }

      //���� ������ ����� �������� �������������� ������ - ��������� ��� ��������� � �������� �����

    if (intersects (bound, entity.WorldBoundBox ()))
      fn (entity);
  }

  const Bound& bound;
  Fn&          fn;
};

}

/*
    ����� ��������, ������������� �����
*/

void Scene::Traverse (const TraverseFunction& fn) const
{
  impl->ForEach (fn);
}

void Scene::Traverse (INodeTraverser& traverser) const
{
  impl->ForEach (traverser);
}

void Scene::VisitEach (Visitor& visitor) const
{
  VisitorWrapper visitor_wrapper (visitor);

  const_cast<Impl*> (impl)->ForEach (visitor_wrapper);
}

/*
    ����� ��������, ������������� ����� � �������� � �������������� �����
*/

void Scene::Traverse (const aaboxf& box, const TraverseFunction& fn) const
{
  BoundsCheckFunction<aaboxf, const TraverseFunction> checker (box, fn);

  impl->ForEach (checker);
}

void Scene::Traverse (const aaboxf& box, INodeTraverser& traverser) const
{
  BoundsCheckFunction<aaboxf, INodeTraverser> checker (box, traverser);

  impl->ForEach (checker);
}

void Scene::VisitEach (const aaboxf& box, Visitor& visitor) const
{
  VisitorWrapper visitor_wrapper (visitor);
  BoundsCheckFunction<aaboxf, VisitorWrapper> checker (box, visitor_wrapper);

  const_cast<Impl*> (impl)->ForEach (checker);
}

void Scene::Traverse (const plane_listf& box, const TraverseFunction& fn) const
{
  BoundsCheckFunction<plane_listf, const TraverseFunction> checker (box, fn);

  impl->ForEach (checker);
}

void Scene::Traverse (const plane_listf& box, INodeTraverser& traverser) const
{
  BoundsCheckFunction<plane_listf, INodeTraverser> checker (box, traverser);

  impl->ForEach (checker);
}

void Scene::VisitEach (const plane_listf& box, Visitor& visitor) const
{
  VisitorWrapper visitor_wrapper (visitor);
  BoundsCheckFunction<plane_listf, VisitorWrapper> checker (box, visitor_wrapper);

  const_cast<Impl*> (impl)->ForEach (checker);
}
