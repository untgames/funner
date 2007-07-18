#ifndef MEDIALIB_COLLADA_CONTROLLER_HEADER
#define MEDIALIB_COLLADA_CONTROLLER_HEADER

#include "base.h"
#include <math/mathlib.h>

namespace medialib
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ColladaControllerType
{
  COLLADA_CONTROLLER_SKIN,  //���� ����������
  COLLADA_CONTROLLER_MORPH  //���� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ColladaMorphMethod
{
  COLLADA_MORPH_NORMALIZED, //(Target1, Target2, ...)*(w1, w2, ...) = (1-w1-w2-...)*BaseMesh + w1*Target1 + w2*Target2 + ...
  COLLADA_MORPH_RELATIVE    //(Target1, Target2, ...) + (w1, w2, ...) = BaseMesh + w1*Target1 + w2*Target2 + ...
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ColladaJointWeight
{
  size_t joint;  //����� ����������
  float  weight; //��� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� � ����������� ����������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct ColladaVertexInfluence
{
  size_t first_weight;  //������ ������� ���� ���������� ������������ �� �������
  size_t weights_count; //���������� ����� ���������� ����������� �� �������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ColladaSkin: public ColladaEntity
{
  friend class ColladaWrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���
///////////////////////////////////////////////////////////////////////////////////////////////////  
    ColladaMesh Mesh () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������ 
///////////////////////////////////////////////////////////////////////////////////////////////////
    const math::mat4f& BindShapeMatrix () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t             JointsCount    () const;
    const char*        JointName      (size_t joint_index) const;
    const math::mat4f& JointInvMatrix (size_t joint_index) const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                        InfluencesCount () const; //��������� � ����������� ������ � ����
    size_t                        WeightsCount    () const; 
    const ColladaJointWeight*     Weights         () const;
    const ColladaVertexInfluence* Influences      () const;
    
  private:
    ColladaSkin (const ColladaSkinImpl*);
    
  private:
    const ColladaSkinImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ColladaMorph: public ColladaEntity
{
  friend class ColladaWrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���
///////////////////////////////////////////////////////////////////////////////////////////////////  
    ColladaMesh Mesh () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ColladaMorphMethod Method () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t      TargetsCount () const;
    float       TargetWeight (size_t index) const;
    ColladaMesh TargetMesh   (size_t index) const;
    
  private:
    ColladaMorph (const ColladaMorphImpl*);
    
  private:
    const ColladaMorphImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ColladaController: public ColladaEntity
{
  friend class ColladaWrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ColladaControllerType Type  () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���� / ����� � ����������� �� ���� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ColladaMorph Morph () const;
    ColladaSkin  Skin  () const;
    
  private:
    ColladaController (const ColladaControllerImpl*);
    
  private:
    const ColladaControllerImpl* impl;
};

}

#endif
