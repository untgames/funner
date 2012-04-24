#include "shared.h"

using namespace media::physics;

namespace
{

const math::vec3f DEFAULT_GRAVITY (0, -9.8f, 0);
const float       DEFAULT_SIMULATION_STEP = 1.f / 60.f;

}

/*
   ���������� ���������
*/

struct Scene::Impl : public xtl::reference_counter
{
  stl::string               name;              //���
  CollisionFilterCollection collision_filters; //������� ��������
  math::vec3f               gravity;           //����������
  float                     simulation_step;   //��� ���������

  Impl ()
    : gravity (DEFAULT_GRAVITY)
    , simulation_step (DEFAULT_SIMULATION_STEP)
    {}

  Impl (const Impl& source)
    : name (source.name)
    , gravity (source.gravity)
    , simulation_step (source.simulation_step)
  {
    collision_filters.Reserve (source.collision_filters.Size ());

    for (CollisionFilterCollection::ConstIterator iter = source.collision_filters.CreateIterator (); iter; ++iter)
      collision_filters.Add (*iter);
  }
};

/*
   ������������ / ���������� / ������������
*/

Scene::Scene ()
  : impl (new Impl)
{
}

Scene::Scene (const Scene& source)
  : impl (source.impl)
{
  addref (impl);
}

Scene::Scene (Impl* in_impl)
  : impl (in_impl)
{
}

Scene::~Scene ()
{
  release (impl);
}

Scene& Scene::operator = (const Scene& source)
{
  Scene (source).Swap (*this);

  return *this;
}
    
/*
   �������� �����
*/

Scene Scene::Clone () const
{
  return Scene (new Impl (*impl));
}

/*
   �������������
*/

size_t Scene::Id () const
{
  return (size_t)impl;
}

/*
   ��� �����
*/

const char* Scene::Name () const
{
  return impl->name.c_str ();
}

void Scene::Rename (const char* name)
{
  if (!name)
    throw xtl::make_null_argument_exception ("media::physics::Scene::Rename", "name");

  impl->name = name;
}

/*
   ��������� ��������� �������� ��������
*/

const Scene::CollisionFilterCollection& Scene::CollisionFilters () const
{
  return const_cast<Scene&> (*this).CollisionFilters ();
}

Scene::CollisionFilterCollection& Scene::CollisionFilters ()
{
  return impl->collision_filters;
}

/*
   ����������
*/

const math::vec3f& Scene::Gravity () const
{
  return impl->gravity;
}

void Scene::SetGravity (const math::vec3f& gravity)
{
  impl->gravity = gravity;
}

/*
   �������� ���������
*/

float Scene::SimulationStep () const
{
  return impl->simulation_step;
}

void Scene::SetSimulationStep (float value)
{
  impl->simulation_step = value;
}

/*
   �����
*/

void Scene::Swap (Scene& source)
{
  stl::swap (impl, source.impl);
}

namespace media
{

namespace physics
{

/*
   �����
*/

void swap (Scene& scene1, Scene& scene2)
{
  scene1.Swap (scene2);
}

}

}