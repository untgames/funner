#include "shared.h"

using namespace tools::ui;
using namespace tools::ui::windows_forms;

/*
    �������� ���������� ������� �����
*/

namespace tools
{

namespace ui
{

namespace windows_forms
{

private ref class ChildFormImpl: public WeifenLuo::WinFormsUI::Docking::DockContent
{
  public:
///�����������
    ChildFormImpl (ICustomChildWindow* in_child_window) : child_window (in_child_window)
    {
        //������������� ������� �����
      
      Text           = "Fucking dock!";
//      ShowHint     = DockState::DockRightAutoHide;
      HideOnClose    = true;
//      DockAreas      = (WeifenLuo::WinFormsUI::Docking::DockAreas)((WeifenLuo::WinFormsUI::Docking::DockAreas::Float | WeifenLuo::WinFormsUI::Docking::DockAreas::Document));
      ShowHint       = WeifenLuo::WinFormsUI::Docking::DockState::Float;
      DoubleBuffered = true;      

        //�������� �� ������� �����

      HandleCreated   += gcnew EventHandler (this, &ChildFormImpl::OnCreateHandle);
      HandleDestroyed += gcnew EventHandler (this, &ChildFormImpl::OnDestroyHandle);
      Resize          += gcnew EventHandler (this, &ChildFormImpl::OnResize);

        //��������� ���������� ����������

      UpdateParent ();
      UpdateRect ();

        //����������� ����

      child_window->Show (true);
    }    

  private:
///���������� ������������� ����
    void UpdateParent ()
    {
      child_window->SetParent ((const void*)Handle);
    }

///���������� ��������
    void UpdateRect ()
    {
      System::Drawing::Rectangle^ rect = ClientRectangle;

      child_window->SetPosition (rect->Left, rect->Top);
      child_window->SetSize     (rect->Width, rect->Height);
    }

///��������� ������� �������� ����������� �����
    void OnCreateHandle (System::Object^, EventArgs^)
    {
//      printf ("ChildFormImpl::OnCreateHandle (%p)\n", (const void*)Handle);
      child_window->SetParent ((const void*)Handle);      
    }

///��������� ������� ����������� ����������� �����
    void OnDestroyHandle (System::Object^, EventArgs^)
    {
//      printf ("ChildFormImpl::OnDestroyHandle (%p)\n", (const void*)Handle);      
      child_window->SetParent (0);
    }

///��������� ������� ��������� �������� �����
    void OnResize (Object^, EventArgs^)
    {
      UpdateRect ();
    }        

  private:
    ICustomChildWindow* child_window;
};

}

}

}

/*
    ����������� / ����������
*/

ChildForm::ChildForm (tools::ui::windows_forms::WindowSystem& window_system, const char* init_string)
  : Form (window_system)
{
  try
  {
      //�������� ����������������� ��������� ����

    IApplicationServer& application_server = window_system.ApplicationServer ();

    child_window = ChildWindowPtr (application_server.CreateChildWindow (init_string), false);

      //�������� ����������

    form = gcnew ChildFormImpl (&*child_window);
    
      //�����������
      
    window_system.MainForm ().Insert (form);
  }
  catch (xtl::exception& exception)
  {
    exception.touch ("tools::ui::ChildForm::ChildForm");
    throw;
  }
}

ChildForm::~ChildForm ()
{
}

/*
    �������� �����
*/

ChildForm::Pointer ChildForm::Create (tools::ui::windows_forms::WindowSystem& window_system, const char* init_string)
{
  return Pointer (new ChildForm (window_system, init_string), false);
}

/*
    ��������� ref-��������� �����
*/

System::Windows::Forms::Form^ ChildForm::FormHandle ()
{
  return form;
}

/*
    ����������� ������
*/

void ChildForm::RegisterInvokers (script::Environment& environment, const char* library_name, const char* base_library_name)
{
  using namespace script;  

  InvokerRegistry& lib = environment.CreateLibrary (library_name);

    //������������ �� Form

  lib.Register (environment.Library (base_library_name));  

    //����������� ����� ������

  environment.RegisterType<ChildForm> (library_name);
}
