#ifndef RENDER_SCENE_SERVER_VIEWPORT_MANAGER_SHARED_HEADER
#define RENDER_SCENE_SERVER_VIEWPORT_MANAGER_SHARED_HEADER

#include <stl/auto_ptr.h>

#include <shared/render_target_map.h>

namespace render
{

namespace manager
{

//forward declarations
class Frame;

}

namespace scene
{

namespace server
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IViewportListener
{
  public:
    virtual void OnViewportZOrderUpdated (int zorder) = 0;

  protected:
    virtual ~IViewportListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Viewport
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Viewport  (RenderManager& render_manager, const RenderTargetMap& render_target_map);
    Viewport  (const Viewport&);
    ~Viewport ();

    Viewport& operator = (const Viewport&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetName (const char* name);
    const char* Name    () const;   

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetArea (const Rect&);
    const Rect& Area    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ��� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    float MinDepth    () const;
    float MaxDepth    () const;
    void  SetMinDepth (float value);
    void  SetMaxDepth (float value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetActive (bool active);
    bool IsActive  () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetZOrder (int order);
    int  ZOrder    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetBackground   (bool state, const math::vec4f& color);
    bool               BackgroundState () const;
    const math::vec4f& BackgroundColor () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetTechnique (const char* name);
    const char* Technique    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                       SetProperties (const common::PropertyMap&);
    const common::PropertyMap& Properties    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    manager::Frame& Frame () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Update (manager::Frame* parent_frame = 0);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachListener     (IViewportListener*);
    void DetachListener     (IViewportListener*);
    void DetachAllListeners ();

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ViewportManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    ViewportManager  ();
    ViewportManager  (const ViewportManager&);
    ~ViewportManager ();

    ViewportManager& operator = (const ViewportManager&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Viewport& GetViewport (object_id_t id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������ / �������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddViewport    (object_id_t id, const Viewport& viewport);
    void RemoveViewport (object_id_t id);

  private:
    struct Impl;
    Impl* impl;
};

}

}

}

#endif
