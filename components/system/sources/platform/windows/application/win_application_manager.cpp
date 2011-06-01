#include "../shared.h"

using namespace syslib;

namespace
{

class Win32ApplicationDelegate: public IApplicationDelegate, public xtl::reference_counter
{
  public:
///�����������
    Win32ApplicationDelegate ()
    {
      idle_enabled    = false;
      is_exited       = false;
      listener        = 0;
      wake_up_message = RegisterWindowMessage ("Win32ApplicationDelegate.WakeUp");
      main_thread_id  = 0;
      
      if (!wake_up_message)
        raise_error ("::RegisterWindowMessage");
    }

///������ ����� ��������� ���������
    void Run ()
    {
      try
      {
        main_thread_id = GetCurrentThreadId ();
        
        if (listener)
          listener->OnInitialized ();
        
        while (!is_exited)
        {
          while (!IsMessageQueueEmpty ())
            DoNextEvent ();

           //���� ��� ������������ OnIdle - ���������������� ����������

          if (!idle_enabled)
          {
            if (IsMessageQueueEmpty () && !is_exited)
            {
              WaitMessage ();
            }
          }
          else
          {
            if (listener)
              listener->OnIdle ();
          }
        }
      }
      catch (xtl::exception& e)
      {
        e.touch ("syslib::Win32ApplicationDelegate::Run");
        throw;
      }
    }

///����� �� ����������
    void Exit (int code)
    {
      if (!PostThreadMessage (main_thread_id, WM_QUIT, code, 0))
        raise_error ("::PostThreadMessage");
    }

///��������� ������������� ������ ������� idle
    void SetIdleState (bool state)
    {
      idle_enabled = state;
      
      if (state)
      {
        if (!::PostMessage (0, wake_up_message, 0, 0))
          raise_error ("::PostMessage");
      }
    }

///��������� ��������� ������� ����������
    void SetListener (IApplicationListener* in_listener)
    {
      listener = in_listener;
    }
    
///������� ������
    void AddRef ()
    {
      addref (this);
    }
    
    void Release ()
    {
      release (this);
    }
    
  private:
///�������� ������� ������� �� �������
    bool IsMessageQueueEmpty ()
    {
      if (is_exited)
        return true;
      
      MSG msg;

      bool result = PeekMessage (&msg, 0, 0, 0, PM_NOREMOVE) == 0;

        //���������� ��� ������

      SetLastError (0);

      return result;
    }
    
///�������� �������
    void WaitMessage ()
    {
      try
      {
        if (!::WaitMessage ())
          raise_error ("::WaitMessage");
      }
      catch (xtl::exception& exception)
      {
        exception.touch ("syslib::Win32ApplicationDelegate::WaitMessage");
        throw;
      }
    }
    
///��������� ���������� �������
    void DoNextEvent ()
    {
      try
      {
        MSG msg;

        is_exited = GetMessage (&msg, 0, 0, 0) == 0;
        
        if (is_exited && listener)
          listener->OnExit (msg.wParam);

        TranslateMessage (&msg);
        DispatchMessage  (&msg);
        SetLastError     (0);
      }
      catch (xtl::exception& exception)
      {
        exception.touch ("syslib::Win32ApplicationDelegate::DoNextEvent");
        throw;
      }
    }

  private:
    bool                  idle_enabled;
    bool                  is_exited;
    IApplicationListener* listener;
    UINT                  wake_up_message;
    DWORD                 main_thread_id;
};

}

/*
    �������� �������� ����������
*/

IApplicationDelegate* WindowsApplicationManager::CreateDefaultApplicationDelegate ()
{
  return new Win32ApplicationDelegate;
}

/*
   �������� URL �� ������� ��������
*/

void WindowsApplicationManager::OpenUrl (const char* url)
{
  try
  {
    int result = (int)ShellExecuteA (0, "open", url, 0, 0, SW_SHOWNORMAL);

    if (result > 32)
      return;

    const char* error;

    switch (result)
    {
      case 0:
        error = "The operating system is out of memory or resources.";
        break;
      case ERROR_FILE_NOT_FOUND:
        error = "The specified file was not found.";
        break;
      case ERROR_PATH_NOT_FOUND:
        error = "The specified path was not found.";
        break;
      case ERROR_BAD_FORMAT:
        error = "The .exe file is invalid (non-Win32 .exe or error in .exe image).";
        break;
      case SE_ERR_ACCESSDENIED:
        error = "The operating system denied access to the specified file.";
        break;
      case SE_ERR_ASSOCINCOMPLETE:
        error = "The file name association is incomplete or invalid.";
        break;
      case SE_ERR_DDEBUSY:
        error = "The DDE transaction could not be completed because other DDE transactions were being processed.";
        break;
      case SE_ERR_DDEFAIL:
        error = "The DDE transaction failed.";
        break;
      case SE_ERR_DDETIMEOUT:
        error = "The DDE transaction could not be completed because the request timed out.";
        break;
      case SE_ERR_DLLNOTFOUND:
        error = "The specified DLL was not found.";
        break;
      case SE_ERR_NOASSOC:
        error = "There is no application associated with the given file name extension. This error will also be returned if you attempt to print a file that is not printable.";
        break;
      case SE_ERR_OOM:
        error = "There was not enough memory to complete the operation.";
        break;
      case SE_ERR_SHARE:
        error = "A sharing violation occurred.";
        break;
      default:
        error = "Unknown error";
    }

    throw xtl::format_operation_exception ("::ShellExecute", error);
  }
  catch (xtl::exception& e)
  {
    e.touch ("syslib::WindowsApplicationManager::OpenUrl");
    throw;
  }
}