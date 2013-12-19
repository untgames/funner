#include "shared.h"

using namespace render::manager;

/*
    DynamicPrimitiveEntityStorage
*/

/*
    �������� ���������� ��������� ������������ ����������
*/

namespace
{

struct DynamicPrimitiveDesc
{
  DynamicPrimitive*    primitive;
  xtl::auto_connection trackable_connection;

  DynamicPrimitiveDesc () : primitive () { }
};

}

typedef stl::vector<DynamicPrimitiveDesc>          DynamicPrimitiveArray;
typedef stl::vector<RendererDynamicPrimitiveGroup> GroupArray;

struct DynamicPrimitiveEntityStorage::Impl
{
  EntityImpl&           entity;             //������ �� ������
  DynamicPrimitiveArray primitives;         //������ ������������ ����������
  GroupArray            groups;             //������ ���������� ����������

/// �����������
  Impl (EntityImpl& in_entity)
    : entity (in_entity)
  {
  }
};

/*
    ����������� / ����������
*/

DynamicPrimitiveEntityStorage::DynamicPrimitiveEntityStorage (EntityImpl& entity)
  : impl (new Impl (entity))
{
}

DynamicPrimitiveEntityStorage::~DynamicPrimitiveEntityStorage ()
{
  RemoveAllPrimitives ();
}

/*
    ���������� ������������ ����������
*/

void DynamicPrimitiveEntityStorage::AddPrimitive (DynamicPrimitive* primitive)
{
  try
  {
    if (!primitive)
      throw xtl::make_null_argument_exception ("", "primitive");

    impl->primitives.push_back ();

    DynamicPrimitiveDesc& desc = impl->primitives.back ();

    try
    {
      desc.primitive            = primitive;
      desc.trackable_connection = primitive->connect_tracker (xtl::bind (&DynamicPrimitiveEntityStorage::RemovePrimitive, this, primitive));

      AttachCacheSource (*primitive);

      InvalidateCacheDependencies ();
    }
    catch (...)
    {
      impl->primitives.pop_back ();
      throw;
    }
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::manager::DynamicPrimitiveEntityStorage::AddPrimitive");
    throw;
  }
}

void DynamicPrimitiveEntityStorage::RemovePrimitive (DynamicPrimitive* primitive)
{
  if (!primitive)
    return;

  for (DynamicPrimitiveArray::iterator iter=impl->primitives.begin (), end=impl->primitives.end (); iter!=end; ++iter)
    if (iter->primitive == primitive)
    {
      DetachCacheSource (*primitive);

      impl->primitives.erase (iter);

      InvalidateCacheDependencies ();

      return;
    }
}

void DynamicPrimitiveEntityStorage::RemoveAllPrimitives ()
{
  DetachAllCacheSources ();

  impl->primitives.clear ();

  InvalidateCacheDependencies ();
}

/*
    ������ ���������� ����������
*/

size_t DynamicPrimitiveEntityStorage::RendererPrimitiveGroupsCount ()
{
  UpdateCache ();

  return impl->groups.size ();
}

RendererDynamicPrimitiveGroup* DynamicPrimitiveEntityStorage::RendererPrimitiveGroups ()
{
  UpdateCache ();

  if (impl->groups.empty ())
    return 0;

  return &impl->groups [0];
}

/*
    ���������� ������������
*/
      
void DynamicPrimitiveEntityStorage::UpdateCacheCore ()
{
  try
  {
      //������� �����

    impl->groups.clear ();

      //���������� �����

    impl->groups.reserve (impl->primitives.size ());

    for (DynamicPrimitiveArray::iterator iter=impl->primitives.begin (), end=impl->primitives.end (); iter!=end; ++iter)
      impl->groups.push_back (RendererDynamicPrimitiveGroup (iter->primitive->RendererPrimitiveGroup (), iter->primitive));

      //���������� ������������

    InvalidateCacheDependencies ();
  }
  catch (xtl::exception& e)
  {
    e.touch ("render::manager::DynamicPrimitiveEntityStorage::UpdateCacheCore");
    throw;
  }
}

void DynamicPrimitiveEntityStorage::ResetCacheCore ()
{
  impl->groups.clear ();
}

/*
    DynamicPrimitive
*/

DynamicPrimitive::DynamicPrimitive (const render::manager::RendererPrimitiveGroup& in_group, bool in_frame_dependent)
  : group (in_group)
  , frame_dependent (in_frame_dependent)
{
}
