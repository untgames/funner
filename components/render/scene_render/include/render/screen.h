#ifndef RENDER_Screen_HEADER
#define RENDER_Screen_HEADER

#include <render/viewport.h>

namespace render
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� �������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
class IScreenListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnChangeName       (const char* new_name) {}
    virtual void OnChangeBackground (bool state, const math::vec4f& new_color) {}
    virtual void OnAttachViewport   (Viewport&) {}
    virtual void OnDetachViewport   (Viewport&) {}
    virtual void OnDestroy          () {}

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddRef  () {}
    virtual void Release () {}
    
  protected:
    virtual ~IScreenListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������������� ������������ - ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Screen
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ���������� / ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Screen  ();
    Screen  (const Screen&); //�������� ����������� - ������� ������
    ~Screen ();

    Screen& operator = (const Screen&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� �������� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Id () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void        SetName (const char* name);
    const char* Name    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void               SetBackgroundColor (const math::vec4f& color);
    void               SetBackgroundColor (float red, float green, float blue, float alpha=0.0f);
    const math::vec4f& BackgroundColor    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �� ������� ������� ���� ��� ������ �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void SetBackgroundState (bool state);
    void EnableBackground   () { SetBackgroundState (true); }
    void DisableBackground  () { SetBackgroundState (false); }
    bool BackgroundState    () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / �������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Attach (const Viewport&);
    void Detach (const Viewport&);

    void DetachAllViewports ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t ViewportsCount () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////    
          render::Viewport& Viewport (size_t index);
    const render::Viewport& Viewport (size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ �� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AttachListener     (IScreenListener*);
    void DetachListener     (IScreenListener*);
    void DetachAllListeners ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Screen&);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Screen&, Screen&);

}

#endif
