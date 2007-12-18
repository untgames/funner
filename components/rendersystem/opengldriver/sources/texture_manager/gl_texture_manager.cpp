#include "shared.h"

using namespace common;
using namespace render::low_level;
using namespace render::low_level::opengl;

/*
    �������� ���������� TextureManager
*/

struct TextureManager::Impl: public ContextObject
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Impl (const ContextManager& context_manager);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� � ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ITexture*      CreateTexture (const TextureDesc&);    
    ISamplerState* CreateSamplerState (const SamplerDesc&);

  public:
    GLint max_texture_size;
};

/*
   �����������
*/

TextureManager::Impl::Impl (const ContextManager& context_manager) : ContextObject (context_manager) 
{
  MakeContextCurrent ();
  glEnable (GL_TEXTURE_2D);
  glGetIntegerv (GL_MAX_TEXTURE_SIZE, &max_texture_size);
  CheckErrors ("render::low_level::opengl::TextureManager::Impl::Impl");
}

/*
   �������� �������� � ��������
*/
  
ITexture* TextureManager::Impl::CreateTexture (const TextureDesc& tex_desc)
{
  if ((int)tex_desc.width > max_texture_size)
    RaiseOutOfRange ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.width", (int)tex_desc.width, 1, max_texture_size);
  else if ((int)tex_desc.height > max_texture_size)
    RaiseOutOfRange ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.height", (int)tex_desc.height, 1, max_texture_size);
  
  MakeContextCurrent ();

  switch (tex_desc.dimension)
  {
    case TextureDimension_1D: 
    {
      if ((tex_desc.width - 1) & tex_desc.width) 
        RaiseInvalidArgument ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.width");

      GLint width;

      glTexImage1D (GL_PROXY_TEXTURE_1D, 0, GLInternalFormat (tex_desc.format), tex_desc.width, 0, GLFormat (tex_desc.format), GL_UNSIGNED_BYTE, NULL);
      glGetTexLevelParameteriv (GL_PROXY_TEXTURE_1D, 0, GL_TEXTURE_WIDTH, &width);
      if (!width)
        Raise <Exception> ("render::low_level::opengl::TextureManager::Impl::CreateTexture", 
                           "Not enough space to create texture with width = %u", tex_desc.width);

      return new Texture1D (GetContextManager (), tex_desc);
    }
    case TextureDimension_2D:
    {
      if ((tex_desc.width - 1) & tex_desc.width) 
        RaiseInvalidArgument ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.width");
      if ((tex_desc.height - 1) & tex_desc.height) 
        RaiseInvalidArgument ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.height");

      GLint width;

      glTexImage2D (GL_PROXY_TEXTURE_2D, 0, GLInternalFormat (tex_desc.format), tex_desc.width, tex_desc.height, 0, 
                    GLFormat (tex_desc.format), GL_UNSIGNED_BYTE, NULL);
      glGetTexLevelParameteriv (GL_PROXY_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
      if (!width)
        Raise <Exception> ("render::low_level::opengl::TextureManager::Impl::CreateTexture", 
                           "Not enough space to create texture with width = %u and height = %u", tex_desc.width, tex_desc.height);

      return new Texture2D (GetContextManager (), tex_desc);
    }
    case TextureDimension_3D: 
    {
      RaiseNotImplemented ("render::low_level::opengl::TextureManager::Impl::CreateTexture"); 
      break;
    }
    case TextureDimension_Cubemap: RaiseNotImplemented ("render::low_level::opengl::TextureManager::Impl::CreateTexture"); break;
    default: RaiseInvalidArgument ("render::low_level::opengl::TextureManager::Impl::CreateTexture", "tex_desc.dimension", tex_desc.dimension);
  }

  CheckErrors ("render::low_level::opengl::TextureManager::Impl::CreateTexture");

  return 0;
}

ISamplerState* TextureManager::Impl::CreateSamplerState (const SamplerDesc&)
{
  RaiseNotImplemented ("render::low_level::opengl::TextureManager::Impl::CreateSamplerState");
  return 0;
}


/*
   ����������� / ����������
*/

TextureManager::TextureManager (const ContextManager& context_manager)
  : impl (new Impl (context_manager))
  {}

TextureManager::~TextureManager ()
{
}
    
/*
   �������� �������� � ��������
*/

ITexture* TextureManager::CreateTexture (const TextureDesc& tex_desc)
{
  return impl->CreateTexture (tex_desc);
}

ISamplerState* TextureManager::CreateSamplerState (const SamplerDesc& sampler_desc)
{
  return impl->CreateSamplerState (sampler_desc);
}

/*
   ��������� ������� �������� � ��������
*/

void TextureManager::SetTexture (size_t sampler_slot, ITexture* texture)
{
  RaiseNotImplemented ("render::low_level::opengl::TextureManager::SetTexture");
}

void TextureManager::SetSampler (size_t sampler_slot, ISamplerState* state)
{
  RaiseNotImplemented ("render::low_level::opengl::TextureManager::SetSampler");
}

ITexture* TextureManager::GetTexture (size_t sampler_slot) const
{
  RaiseNotImplemented ("render::low_level::opengl::TextureManager::GetTexture");
  return 0;
}

ISamplerState* TextureManager::GetSampler (size_t sampler_slot) const
{
  RaiseNotImplemented ("render::low_level::opengl::TextureManager::GetSampler");
  return 0;
}
