#ifndef RENDER_MANAGER_ENTITY_HEADER
#define RENDER_MANAGER_ENTITY_HEADER

#include <common/property_map.h>

#include <math/matrix.h>

#include <render/primitive.h>

namespace render
{

//implementation forwards
class EntityImpl;
class Wrappers;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Entity
{
  friend class Wrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Entity  (const Entity&);
    ~Entity ();
    
    Entity& operator = (const Entity&);   

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                       SetProperties (const common::PropertyMap&);
    const common::PropertyMap& Properties    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������� (��� ���������)
///  �������������� ���������� �� ������� Entity::Transformation � ������ ���� ��� �� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetJointsCount         (size_t count);
    size_t             JointsCount            () const;
    void               SetJointTransformation (size_t joint_index, const math::mat4f&);
    const math::mat4f& JointTransformation    (size_t joint_index) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t LodsCount () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::Primitive Primitive           (size_t level_of_detail = 0) const;
    const char*       PrimitiveName       (size_t level_of_detail = 0) const;
    void              SetPrimitive        (const render::Primitive&, size_t level_of_detail = 0);
    void              SetPrimitive        (const char* name, size_t level_of_detail = 0);
    void              ResetPrimitive      (size_t level_of_detail = 0);
    bool              HasPrimitive        (size_t level_of_detail = 0) const;
    void              ResetAllPrimitives  ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateCache ();
    void ResetCache  ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Entity&);
    
  private:
    Entity (EntityImpl*);
    
  private:
    EntityImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Entity&, Entity&);

}

#endif
