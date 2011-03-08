#ifndef RENDER_MANAGER_MANAGER_HEADER
#define RENDER_MANAGER_MANAGER_HEADER

///???�������������� �������� ���������� �� ���������� ����� entity

#include <render/entity.h>
#include <render/dynamic_resource.h>
#include <render/material.h>
#include <render/texture.h>
#include <render/window.h>

namespace syslib
{

//forward declaration
class Window;

}

namespace render
{

//implementation forwards
class RenderManagerImpl;
class Wrappers;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ��������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum RenderManagerWindowEvent
{
  RenderManagerWindowEvent_OnAdded,   //��������� ����� ���� ����������
  RenderManagerWindowEvent_OnRemoved, //������� ���� ����������
  
  RenderManagerWindowEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������������� ����������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum ResourceInstanceMode
{
  ResourceInstanceMode_Shared, //������ ������������ ���������
  ResourceInstanceMode_Copy,   //������ ���������� ��� ��������

  ResourceInstanceMode_Default = ResourceInstanceMode_Shared
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class RenderManager
{
  friend class Wrappers;
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderManager  ();
    RenderManager  (const RenderManager&);
    ~RenderManager ();
    
    RenderManager& operator = (const RenderManager&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �������� ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Description () const;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    render::Window CreateWindow (syslib::Window& window, common::PropertyMap& properties);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t               WindowsCount () const;
    const render::Window Window       (size_t index) const;
          render::Window Window       (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTarget CreateRenderBuffer       (size_t width, size_t height, PixelFormat format);
    RenderTarget CreateDepthStencilBuffer (size_t width, size_t height);
                                                         
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Primitive        CreatePrimitive        ();
    Primitive        CreatePrimitive        (const PrimitiveBuffers&);    
    Primitive        CreatePrimitive        (const char* name, ResourceInstanceMode mode = ResourceInstanceMode_Default);
    PrimitiveBuffers CreatePrimitiveBuffers (MeshBufferUsage lines_usage = MeshBufferUsage_Stream, MeshBufferUsage sprites_usage = MeshBufferUsage_Stream);
    Frame            CreateFrame            ();
    Texture          CreateTexture          (const media::Image& image, bool generate_mipmaps = true);
    Texture          CreateTexture          (const media::Image& image, TextureDimension dimension, bool generate_mipmaps = true);
    Texture          CreateTexture2D        (size_t width, size_t height, PixelFormat format, bool generate_mipmaps = true);
    Texture          CreateTexture3D        (size_t width, size_t height, size_t depth, PixelFormat format, bool generate_mipmaps = true);
    Texture          CreateTextureCubemap   (size_t size, PixelFormat format, bool generate_mipmaps = true);
    Material         CreateMaterial         ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void LoadResource   (const char* resource_name);
    void LoadResource   (const media::rfx::MaterialLibrary&);
    void LoadResource   (const media::geometry::MeshLibrary&);
    void UnloadResource (const char* resource_name);
    void UnloadResource (const media::rfx::MaterialLibrary&);
    void UnloadResource (const media::geometry::MeshLibrary&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� �� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (RenderManager& manager, render::Window& window)> WindowEventHandler;

    xtl::connection RegisterWindowEventHandler (RenderManagerWindowEvent event, const WindowEventHandler& handler) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (RenderManager&);
    
  private:
    RenderManager (RenderManagerImpl*);
    
  private:
    RenderManagerImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (RenderManager&, RenderManager&);

}

#endif
