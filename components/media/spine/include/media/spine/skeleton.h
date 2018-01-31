#ifndef MEDIALIB_SPINE_SKELETON_HEADER
#define MEDIALIB_SPINE_SKELETON_HEADER

#include <math/vector.h>

namespace media
{

namespace geometry
{

//forward declarations
class Mesh;

}

namespace spine
{

//forward declarations
class AnimationState;
class Bone;
class Material;
class Slot;
class SkeletonImpl;
class Wrappers;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Spine skeleton instance
///////////////////////////////////////////////////////////////////////////////////////////////////
class Skeleton
{
  friend class Wrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructors / destructor / assignment
///////////////////////////////////////////////////////////////////////////////////////////////////
    Skeleton (const Skeleton&);
    ~Skeleton ();

    Skeleton& operator = (const Skeleton&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Animating
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetToSetupPose ();
    void Apply          (const AnimationState& animation);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Work with bones
///////////////////////////////////////////////////////////////////////////////////////////////////
          Bone& RootBone ();
    const Bone& RootBone () const;

          Bone* FindBone (const char* name);
    const Bone* FindBone (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Work with slots
///////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int               SlotsCount () const;
          media::spine::Slot&  Slot       (unsigned int index);
    const media::spine::Slot&  Slot       (unsigned int index) const;
          media::spine::Slot*  FindSlot   (const char* name);
    const media::spine::Slot*  FindSlot   (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Rendering. Meshes are sorted in draw order
///////////////////////////////////////////////////////////////////////////////////////////////////
    unsigned int    MeshesCount () const;
    geometry::Mesh  Mesh        (unsigned int mesh_index) const;
    const Material& Material    (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///Change skin (use 0 to set default skin)
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Skin          () const;  //may be 0
    bool        SetSkin       (const char* skin_name = 0);
    bool        SetAttachment (const char* slot_name, const char* attachment_name = 0); //Returns false if the slot or attachment was not found.

///////////////////////////////////////////////////////////////////////////////////////////////////
///Update transform after animation/bones manipulation
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateWorldTransform ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///Swap
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Skeleton&);

  protected:
    Skeleton (SkeletonImpl*);

  private:
    SkeletonImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Swap
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Skeleton&, Skeleton&);

}

}

#endif
