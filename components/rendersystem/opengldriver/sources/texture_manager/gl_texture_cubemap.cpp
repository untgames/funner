#include "shared.h"

using namespace common;
using namespace render::low_level;
using namespace render::low_level::opengl;

/*
   ����������� / ����������
*/

TextureCubemap::TextureCubemap  (const ContextManager& manager, const TextureDesc& tex_desc)
  : Texture (manager, tex_desc, GL_TEXTURE_CUBE_MAP_ARB)
{
  TextureExtensions ext (GetContextManager ());

  Bind ();

  for (size_t i = 0; i < 6; i++)
  {
    if (is_compressed_format (tex_desc.format))   
    {
      if (ext.has_ext_texture_compression_s3tc)   
        glCompressedTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + i, 0, gl_internal_format (tex_desc.format), tex_desc.width, 
                                tex_desc.height, 0, ((tex_desc.width * tex_desc.height) >> 4) * compressed_quad_size (tex_desc.format), NULL);
      else
        glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + i, 0, unpack_internal_format (tex_desc.format), tex_desc.width, tex_desc.height, 0, 
                      unpack_format (tex_desc.format), unpack_type (tex_desc.format), NULL);
    }
    else
      glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + i, 0, gl_internal_format (tex_desc.format), tex_desc.width, tex_desc.height, 0, 
                    gl_format (tex_desc.format), gl_type (tex_desc.format), NULL);
  }

  if (tex_desc.generate_mips_enable)
  {
    mips_count = get_mips_count (tex_desc.width, tex_desc.height);

    if (ext.has_sgis_generate_mipmap)
      glTexParameteri (GL_TEXTURE_CUBE_MAP_ARB, GL_GENERATE_MIPMAP_SGIS, true);
    else
    {
      size_t width = tex_desc.width; size_t height = tex_desc.height;

      for (size_t i = 1; i < mips_count; i++)
      {
        for (size_t j = 0; j < 6; j++)
        {
          if (is_compressed_format (tex_desc.format))   
          {
            if (ext.has_ext_texture_compression_s3tc)   
              glCompressedTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + j, i, gl_internal_format (tex_desc.format), width, 
                                      height, 0, ((width * height) >> 4) / compressed_quad_size (tex_desc.format), NULL);
            else
              glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + j, i, unpack_internal_format (tex_desc.format), width, height, 0, 
                            unpack_format (tex_desc.format), unpack_type (tex_desc.format), NULL);
          }
          else
            glTexImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + j, i, gl_internal_format (tex_desc.format), width, height, 0, 
                          gl_format (tex_desc.format), gl_type (tex_desc.format), NULL);
        }
        
        if (width > 1)  width  /= 2;
        if (height > 1) height /= 2;
      }
    }
  }

  CheckErrors ("render::low_level::opengl::TextureCubemap::TextureCubemap");
}

/*
    ��������� �������� ���� ���� ��������
*/

GLenum TextureCubemap::GetLayerTarget (size_t layer)
{
  if (layer > 6)
    RaiseOutOfRange ("render::low_level::opengl::TextureCubemap::GetLayerTarget", "layer", layer, 6);
    
  return GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer;
}

/*
   ������ � �������
*/

namespace
{

void SetTexDataCubemap (size_t mip_level, size_t x, size_t y, size_t z, size_t width, size_t height, GLenum format, GLenum type, const void* data)
{
  glTexSubImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + z, mip_level, x, y, width, height, format, type, data);
}

}

void TextureCubemap::SetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat source_format, const void* buffer)
{
  Texture::SetData (layer, mip_level, x, y, width, height, source_format, buffer);
  
  if (layer > 5)
    RaiseOutOfRange ("render::low_level::opengl::TextureCubemap::SetData", "layer", layer, (size_t)0, (size_t)5);
  if (mip_level > mips_count)
    RaiseOutOfRange ("render::low_level::opengl::TextureCubemap::SetData", "mip_level", mip_level, (size_t)0, mips_count);
  if (((x + width) > (desc.width >> mip_level)) && ((x + width) != 1))
    RaiseOutOfRange ("render::low_level::opengl::TextureCubemap::SetData", "x + width", x + width, (size_t)0, desc.width >> mip_level);
  if (((y + height) > (desc.height >> mip_level)) && ((y + height) != 1))
    RaiseOutOfRange ("render::low_level::opengl::TextureCubemap::SetData", "y + height", y + height, (size_t)0, desc.height >> mip_level);
  if (!width || !height)
    return;
  if (is_compressed_format (desc.format))
  {
    if (desc.generate_mips_enable)
      RaiseInvalidOperation ("render::low_level::opengl::TextureCubemap::SetData", "Generate mipmaps not compatible with compressed textures.");
    if (x & 3)
      RaiseInvalidArgument ("render::low_level::opengl::TextureCubemap::SetData", "x", x, "x must be a multiple of 4.");
    if (y & 3)
      RaiseInvalidArgument ("render::low_level::opengl::TextureCubemap::SetData", "y", y, "y must be a multiple of 4.");
    if (width & 3)
      RaiseInvalidArgument ("render::low_level::opengl::TextureCubemap::SetData", "width", width, "width must be a multiple of 4.");
    if (height & 3)
      RaiseInvalidArgument ("render::low_level::opengl::TextureCubemap::SetData", "height", height, "height must be a multiple of 4.");
  }
  if (is_compressed_format (source_format))
    if (source_format != desc.format)
      RaiseInvalidArgument ("render::low_level::opengl::TextureCubemap::SetData", "source_format");

  TextureExtensions ext (GetContextManager ());

  MakeContextCurrent ();
  Bind ();

  if (is_compressed_format (source_format))
  {
    if (ext.has_ext_texture_compression_s3tc)
      glCompressedTexSubImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer, mip_level, x, y, width, height, gl_format (source_format), 
                                 ((width * height) >> 4) * compressed_quad_size (source_format), buffer);
    else
    {
      xtl::uninitialized_storage <char> unpacked_buffer (width * height * unpack_texel_size (source_format));

      unpack_dxt (source_format, width, height, buffer, unpacked_buffer.data ());
      glTexSubImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer, mip_level, x, y, width, height, unpack_format (source_format), unpack_type (source_format), unpacked_buffer.data ());
    }
  }
  else
  {
    if (mip_level && ext.has_sgis_generate_mipmap)
      glTexParameteri (GL_TEXTURE_CUBE_MAP_ARB, GL_GENERATE_MIPMAP_SGIS, false); 
    
    glTexSubImage2D (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer, mip_level, x, y, width, height, gl_format (source_format), gl_type (source_format), buffer);
    
    if (mip_level && ext.has_sgis_generate_mipmap)
      glTexParameteri (GL_TEXTURE_CUBE_MAP_ARB, GL_GENERATE_MIPMAP_SGIS, true);

    if (desc.generate_mips_enable && !mip_level && !ext.has_sgis_generate_mipmap)
    {    
      generate_mips (x, y, layer, width, height, source_format, buffer, &SetTexDataCubemap);
    }
  }

  CheckErrors ("render::low_level::opengl::TextureCubemap::SetData");
}

void TextureCubemap::GetData (size_t layer, size_t mip_level, size_t x, size_t y, size_t width, size_t height, PixelFormat target_format, void* buffer)
{
  static const char* METHOD_NAME = "render::low_level::opengl::TextureCubemap::GetData";

  Texture::GetData (layer, mip_level, x, y, width, height, target_format, buffer);

  if (layer > 5)
    RaiseOutOfRange (METHOD_NAME, "layer", layer, (size_t)0, (size_t)5);
  if (mip_level > mips_count)
    RaiseOutOfRange (METHOD_NAME, "mip_level", mip_level, (size_t)0, mips_count);
  if (x)
    RaiseOutOfRange (METHOD_NAME, "x", x, (size_t)0, (size_t)0);
  if (y)
    RaiseOutOfRange (METHOD_NAME, "y", y, (size_t)0, (size_t)0);
  if (width != (desc.width >> mip_level))
    RaiseOutOfRange (METHOD_NAME, "width", width, desc.width >> mip_level, desc.width >> mip_level);
  if (height != (desc.height >> mip_level))
    RaiseOutOfRange (METHOD_NAME, "height", height, desc.height >> mip_level, desc.height >> mip_level);
  if (is_compressed_format (target_format))
    if (target_format != desc.format)
      RaiseInvalidArgument (METHOD_NAME, "target_format", target_format, "Can't get compressed texture data, format is different.");

  MakeContextCurrent ();
  Bind ();

  TextureExtensions ext (GetContextManager ());

  if (is_compressed_format (target_format))
  {
    if (ext.has_ext_texture_compression_s3tc)
      glGetCompressedTexImage (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer, mip_level, buffer);
    else
      RaiseNotSupported (METHOD_NAME, "Texture packing not supported. Reason: GL_EXT_texture_compression_s3tc not supported.");
  }
  else
    glGetTexImage (GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB + layer, mip_level, gl_format (target_format), gl_type (target_format), buffer);
  
  CheckErrors (METHOD_NAME);
}
