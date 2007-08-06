#ifndef MEDIALIB_COLLADA_MORPH_HEADER
#define MEDIALIB_COLLADA_MORPH_HEADER

#include <media/collada/geometry.h>
#include <math/mathlib.h>

namespace medialib
{

namespace collada
{

//forward declarations
class Morph;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���樠������ ������⥪� ��� ᮧ����� ����஢
///////////////////////////////////////////////////////////////////////////////////////////////////
template <> class ILibrary<Morph>: public IItemLibrary<Morph>
{
  public:
    virtual Morph& Create (Mesh& base_mesh, const char* id = 0) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��⮤ ���䨭��
///////////////////////////////////////////////////////////////////////////////////////////////////
enum MorphMethod
{
  MorphMethod_Normalized, //(Target1, Target2, ...)*(w1, w2, ...) = (1-w1-w2-...)*BaseMesh + w1*Target1 + w2*Target2 + ...
  MorphMethod_Relative    //(Target1, Target2, ...) + (w1, w2, ...) = BaseMesh + w1*Target1 + w2*Target2 + ...
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ���䨭��
///////////////////////////////////////////////////////////////////////////////////////////////////
class MorphTarget
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
          collada::Mesh& Mesh ();
    const collada::Mesh& Mesh () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void  SetWeight (float weight);
    float Weight    () const;

  protected:
    MorphTarget  (collada::Mesh&, float weight);
    ~MorphTarget ();

  private:
    MorphTarget (const MorphTarget&); //no impl
    MorphTarget& operator = (const MorphTarget&); //no impl

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� 楫�� ���䨭��
///////////////////////////////////////////////////////////////////////////////////////////////////
template <> class ICollection<MorphTarget>: public IItemCollection<MorphTarget>
{
  public:
    virtual MorphTarget& Create (Mesh& mesh, float weight) = 0;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Morph: public Entity
{
  public:
    typedef ICollection<MorphTarget> TargetList;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��⮤ ���䨭��
///////////////////////////////////////////////////////////////////////////////////////////////////
    MorphMethod Method    () const;
    void        SetMethod (MorphMethod);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���
///////////////////////////////////////////////////////////////////////////////////////////////////
          Mesh& BaseMesh ();
    const Mesh& BaseMesh () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���᮪ 楫�� ���䨭��
///////////////////////////////////////////////////////////////////////////////////////////////////
          TargetList& Targets ();
    const TargetList& Targets () const;

  protected:
    Morph  (Mesh& base_mesh, ModelImpl*, const char* id);
    ~Morph ();

  private:
    struct Impl;
    Impl* impl;
};

}

}

#endif
