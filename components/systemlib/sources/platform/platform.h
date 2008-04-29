#ifndef SYSLIB_PLATFORM_HEADER
#define SYSLIB_PLATFORM_HEADER

#include <syslib/window.h>

namespace syslib
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum WindowFlag
{
  WindowFlag_Visible, //��������� ����
  WindowFlag_Active,  //���������� ����
  WindowFlag_Focus    //����� ����� ����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Platform
{
  public:
    struct window_handle;
  
    typedef const window_handle* window_t;
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������/��������/����������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef void (*WindowMessageHandler)(WindowEvent, const WindowEventContext&, void* user_data);

    static window_t CreateWindow  (WindowStyle, WindowMessageHandler, void* user_data);
    static void     CloseWindow   (window_t);
    static void     DestroyWindow (window_t);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetWindowTitle (window_t, const wchar_t* title);
    static void GetWindowTitle (window_t, size_t buffer_size, wchar_t* buffer);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���� / ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetWindowRect (window_t, const Rect&);
    static void GetWindowRect (window_t, Rect&);
    static void GetClientRect (window_t, Rect&);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void SetWindowFlag (window_t, WindowFlag flag, bool state);
    static bool GetWindowFlag (window_t, WindowFlag flag);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void InvalidateWindow (window_t);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void  SetCursorPosition (const Point& position);
    static Point GetCursorPosition ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t GetKeyName (ScanCode scan_code, size_t buffer_size, char* buffer); //������������ ����� ������ ��� ����� '\0'

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ ���������� ���� �� miliseconds ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void Sleep (size_t miliseconds);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / ����������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    struct timer_handle;
    typedef const timer_handle* timer_t;
    typedef void (*TimerHandler)(void* user_data);

    static timer_t CreateTimer (size_t period_in_milliseconds, TimerHandler, void* user_data);
    static void    KillTimer   (timer_t handle);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � �������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static bool IsMessageQueueEmpty ();
    static void DoNextEvent         ();
    static void WaitMessage         (); //������������ ���������� ���������� �� ��������� ���������� ���������

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    struct dynamic_library_handle;

    typedef dynamic_library_handle* dll_t;

    static dll_t LoadLibrary   (const wchar_t* name);
    static void  UnloadLibrary (dll_t);
    static void* GetSymbol     (dll_t, const char* symbol_name);
};

}

#endif
