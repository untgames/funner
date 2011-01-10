#ifndef SYSLIB_PLATFORM_ANDROID_HEADER
#define SYSLIB_PLATFORM_ANDROID_HEADER

#include <syslib/window.h>

namespace syslib
{

namespace android
{

typedef int touch_t;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
struct TouchDescription
{
  touch_t touch; //������������� �������
  float   x;     //������� ��������� ������ ������������ ���� (0 - � ����� ������� ����, 1 - � ������)
  float   y;     //������� ��������� ������ ������������ ���� (0 - � ������� ������� ����, 1 - � ������)
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class IWindowListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnTouchesBegan (size_t touches_count, const TouchDescription* touches) {} //���� ��� ��������� ������� ����������� �� ����
    virtual void OnTouchesMoved (size_t touches_count, const TouchDescription* touches) {} //���� ��� ��������� ������� ��������� � ����
    virtual void OnTouchesEnded (size_t touches_count, const TouchDescription* touches) {} //���� ��� ��������� ������� ��������� � ����

  protected:
    virtual ~IWindowListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
class WindowManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/�������� ����������� �� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void AttachWindowListener (const Window& window, IWindowListener* listener);
    static void DetachWindowListener (const Window& window, IWindowListener* listener);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ��������� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class IApplicationListener
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void OnMemoryWarning () {}   //�������� ������
    virtual void OnPause         () {}   //���������� �������������� (������� � ���)
    virtual void OnResume        () {}   //���������� ������������� (������� �� �������� ����)
    virtual void OnStop          () {}   //���������� �����������

  protected:
    virtual ~IApplicationListener () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
class ApplicationManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/�������� ����������� �� ������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void AttachApplicationListener (IApplicationListener* listener);
    static void DetachApplicationListener (IApplicationListener* listener);
};

}

}

#endif
