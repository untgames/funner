#ifndef RENDER_SCENE_RENDER_VIEWPORT_HEADER
#define RENDER_SCENE_RENDER_VIEWPORT_HEADER

#include <stl/string_fwd>

#include <render/common.h>

namespace scene_graph
{

//forward declaration
class Camera;

}

namespace render
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Viewport
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Viewport  ();
    Viewport  (const Viewport&);
    ~Viewport ();

    Viewport& operator = (const Viewport&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���� ���������� ����������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetRenderPath  (const char* path_name);
    const char* RenderPath     () const;
    size_t      RenderPathHash () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetArea   (const Rect& rect);
    void        SetArea   (size_t left, size_t top, size_t width, size_t height);    
    void        SetOrigin (size_t left, size_t top);
    void        SetSize   (size_t width, size_t height);
    const Rect& Area      () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ��������� �������� ������ (��������� �� ���������� ������� �� ���������� ������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetZOrder (int z_order);
    int  ZOrder    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������, ��������� � �������� ������ (�������� �������� - weak-reference)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void                       SetCamera (scene_graph::Camera*);
    const scene_graph::Camera* Camera    () const;
          scene_graph::Camera* Camera    ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����������� ������� ������ (��������� ������� �� ��������� � ���������)
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetActive  (bool state);
    bool IsActive   () const;
    void Activate   () { SetActive (true); }
    void Deactivate () { SetActive (false); }

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetProperty (const char* name, const char* value);
    const char* GetProperty (const char* name) const;
    bool        HasProperty () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Viewport&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Viewport&, Viewport&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
template <class T> void set_property (Viewport&, const char* name, const T& value);
template <class T> T    get_property (Viewport&, const char* name);
template <class T> T    get_property (Viewport&, const char* name, const T& default_value);

#include <render/detail/viewport.inl>

}

#endif
