#ifndef RENDER_HEADER
#define RENDER_HEADER

#include <stl/auto_ptr.h>
#include <xtl/functional_fwd>

namespace render
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Option
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const char* Name () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� / ������ ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void        SetValue (const char* value);
    virtual const char* Value () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� ��������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual size_t      PossibleValuesCount () const;
    virtual const char* PossibleValue       (size_t index) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Render
{
  public:  
      //depth-stencil???
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Render  ();
    ~Render ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    RenderTarget CreateRenderWindow (syslib::Window& window);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                      RenderTargetsCount () const;
    render::RenderTarget&       RenderTarget       (size_t index);
    const render::RenderTarget& RenderTarget       (size_t index) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���� ������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void UpdateAllRenderTargets ();    

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t                OptionsCount    () const;
    render::Option&       Option          (size_t index);
    const render::Option& Option          (size_t index) const;
    render::Option&       Option          (const char* name);
    const render::Option& Option          (const char* name) const;
    int                   FindOptionIndex (const char* name) const; //no throw, return -1 if fail    
    void                  SetOptionValue  (const char* name, const char* value);
    const char*           OptionValue     (const char* name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Prefetch     ();
    void Flush        ();
    void SetAutoFlush (bool state);
    bool IsAutoFlush  () const;    

  private:
    Render (const Render&); //no impl
    Render& operator = (const Render&); //no impl

  private:
    struct Impl;
    stl::auto_ptr<Impl> impl;
};

}

#endif
