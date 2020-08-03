#ifndef MEDIALIB_SPINE_SHARED_MATERIAL_HEADER
#define MEDIALIB_SPINE_SHARED_MATERIAL_HEADER

#include <stl/string>

#include <media/spine/material.h>

#include <object.h>

namespace media
{

namespace spine
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///Mesh material
///////////////////////////////////////////////////////////////////////////////////////////////////
class MaterialImpl : virtual public IObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///Constructor
///////////////////////////////////////////////////////////////////////////////////////////////////
    MaterialImpl (const char* name, const char* texture_path, media::spine::BlendMode blend_mode, TexcoordWrap texcoord_wrap_u, TexcoordWrap texcoord_wrap_v);

///////////////////////////////////////////////////////////////////////////////////////////////////
///Name
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name () { return name.c_str (); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///Params
///////////////////////////////////////////////////////////////////////////////////////////////////
    media::spine::BlendMode BlendMode     () { return blend_mode; }
    TexcoordWrap            TexcoordWrapU () { return texcoord_wrap_u; }
    TexcoordWrap            TexcoordWrapV () { return texcoord_wrap_v; }
    const char*             TexturePath   () { return texture_path.c_str (); }

  private:
    stl::string             name;
    stl::string             texture_path;
    media::spine::BlendMode blend_mode;
    TexcoordWrap            texcoord_wrap_u;
    TexcoordWrap            texcoord_wrap_v;
};

}

}

#endif