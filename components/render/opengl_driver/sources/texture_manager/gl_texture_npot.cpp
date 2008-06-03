#include "shared.h"

using namespace common;
using namespace render::low_level;
using namespace render::low_level::opengl;

/*
   ����������� / ����������
*/

TextureNpot::TextureNpot  (const ContextManager& manager, const TextureDesc& tex_desc)
  : Texture (manager, tex_desc, GL_TEXTURE_RECTANGLE_EXT, 1)
{
  static const char* METHOD_NAME = "render::low_level::opengl::TextureNpot::TextureNpot";

  if (tex_desc.generate_mips_enable)
    raise_not_supported (METHOD_NAME, "Mip maps for non power of two textures not supported");

  if (is_compressed (tex_desc.format))
    raise_not_supported (METHOD_NAME, "Non power of two texture can't be compressed");

  Bind ();

    //�������������� ������� ��������
    
  GLenum gl_internal_format = get_gl_internal_format (tex_desc.format),
         gl_format          = get_gl_format (tex_desc.format),
         gl_type            = get_gl_type (tex_desc.format);  
         
    //�������� ����������� �������� ��������

  glTexImage2D (GL_PROXY_TEXTURE_RECTANGLE_EXT, 0, gl_internal_format, tex_desc.width, tex_desc.height, 0, 
                gl_format, gl_type, NULL);
  
  GLint width = 0;

  glGetTexLevelParameteriv (GL_PROXY_TEXTURE_RECTANGLE_EXT, 0, GL_TEXTURE_WIDTH, &width);

  if (!width)
    raise_not_supported (METHOD_NAME, "Can't create rectangle texture %ux%ux%u@%s (proxy texture fail)", 
                       tex_desc.width, tex_desc.height, tex_desc.layers, get_name (tex_desc.format));

    //�������� ��������

  glTexImage2D (GL_TEXTURE_RECTANGLE_EXT, 0, gl_internal_format, tex_desc.width, tex_desc.height, 0, 
                gl_format, gl_type, 0);
                
    //�������� ������

  CheckErrors (METHOD_NAME);
}

/*
    ��������� ������
*/

void TextureNpot::SetUncompressedData
 (size_t      layer,
  size_t      mip_level,
  size_t      x,
  size_t      y,
  size_t      width,
  size_t      height,
  GLenum      format,
  GLenum      type,
  const void* buffer)
{
  if (mip_level)
    raise_not_supported ("render::low_level::opengl::TextureNpot::SetUncompressedData",
      "Mip-mapping not supported for rectangle-textures (mip_level=%u)", mip_level);

  glTexSubImage2D (GL_TEXTURE_RECTANGLE_EXT, 0, x, y, width, height, format, type, buffer);
}

void TextureNpot::SetCompressedData (size_t, size_t, size_t, size_t, size_t, size_t, GLenum, size_t, const void*)
{
  raise_not_supported ("render::low_level::opengl::TextureNpot::SetCompressedData", "Compression for Npot textures not supported");
}
