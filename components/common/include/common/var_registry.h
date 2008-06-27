#ifndef COMMONLIB_VAR_REGISTRY_HEADER
#define COMMONLIB_VAR_REGISTRY_HEADER

#include <xtl/functional_fwd>

namespace common
{

//forward declaration
class VarRegistryImpl;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ॥��� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
enum VarRegistryEvent
{
  VarRegistryEvent_OnCreateVar, //������ ����� ��६�����
  VarRegistryEvent_OnDeleteVar, //㤠����� ��६�����
  VarRegistryEvent_OnChangeVar, //��������� ���祭�� ��६�����

  VarRegistryEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class ICustomVarRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭��/��⠭���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual const char* GetValue (const char* var_name) = 0;
    virtual       void  SetValue (const char* var_name, const char* value) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�஢�ઠ ������ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual bool HasVariable (const char* var_name) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��室 ��� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const char* var_name)> EnumHandler;

    virtual void EnumerateVars (const EnumHandler& handler) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/㤠����� ��뫪�
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddRef () = 0;
    virtual void Release () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����᪠ �� ����������/���������/㤠����� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function <void (const char* var_name, VarRegistryEvent event)> EventHandler;

    virtual void                SetEventHandler (const EventHandler& handler) = 0;
    virtual const EventHandler& GetEventHandler () = 0;

  protected:
    virtual ~ICustomVarRegistry () {}
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����⪠ ��� ॥��஬ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class VarRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    VarRegistry ();
    VarRegistry (const char* branch_name);
    VarRegistry (const VarRegistry& source);
    ~VarRegistry ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����஢����
///////////////////////////////////////////////////////////////////////////////////////////////////
    VarRegistry& operator = (const VarRegistry& source);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭��/��⠭���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetValue (const char* var_name) const;
          void  SetValue (const char* var_name, const char* value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�஢�ઠ ������ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasVariable (const char* var_name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭�� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* BranchName () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�஢�ઠ ������祭 �� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsOpened () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������祭��/�⪫�祭�� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Open  (const char* branch_name);
    void Close ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��室 ��� ��६����� / ��६����� �� ��᪥
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef ICustomVarRegistry::EnumHandler EnumHandler;

    void EnumerateVars (const EnumHandler& handler);
    void EnumerateVars (const char* var_name_mask, const EnumHandler& handler);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����᪠ �� ����������/���������/㤠����� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function <void (const char* var_name)> EventHandler;

    xtl::connection RegisterEventHandler (const char* var_name_mask, VarRegistryEvent event, const EventHandler& handler) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (VarRegistry& source);

  private:
    VarRegistryImpl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (VarRegistry& source1, VarRegistry& source2);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ ��ப���� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class StringRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� / ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    StringRegistry ();
    StringRegistry (const StringRegistry& source);
    ~StringRegistry ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����஢����
///////////////////////////////////////////////////////////////////////////////////////////////////
    StringRegistry& operator = (const StringRegistry& source);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭��/��⠭���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetValue (const char* var_name) const;
          void  SetValue (const char* var_name, const char* value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RemoveVariable (const char* var_name);
    void RemoveAllVariables ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�஢�ઠ ������ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasVariable (const char* var_name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��ᮥ�������/��ᮥ������� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Mount      (const char* branch_name);
    void Unmount    (const char* branch_name);
    void UnmountAll ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (StringRegistry& source);

  private:
    struct Impl;
    Impl* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (StringRegistry& source1, StringRegistry& source2);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���⥬� ॥��஢ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
class VarRegistrySystem
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��ᮥ�������/��ᮥ������� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void Mount      (const char* branch_name, ICustomVarRegistry* registry);
    static void Unmount    (const char* branch_name);
    static void UnmountAll ();
};

}

#endif