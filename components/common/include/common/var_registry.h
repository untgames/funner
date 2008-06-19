#ifndef COMMONLIB_VAR_REGISTRY_HEADER
#define COMMONLIB_VAR_REGISTRY_HEADER

#include <xtl/functional_fwd>

namespace common
{

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
///��室 ��� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef xtl::function<void (const char* var_name)> EnumHandler;

    virtual void ForEach (const EnumHandler& handler) = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������/㤠����� ��뫪�
///////////////////////////////////////////////////////////////////////////////////////////////////
    virtual void AddRef () = 0;
    virtual void Release () = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////
///TODO: �������� ������� �� ����������/���������/㤠�����!!!!!!!!!!!
///////////////////////////////////////////////////////////////////////////////////////////////////

  protected:
    virtual ~ICustomVarRegistry ();
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
    VarRegistry (ICustomVarRegistry* registry, bool add_ref = true);
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
///�஢�ઠ ��⠭����� �� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool IsBinded () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///������祭��/�⪫�祭�� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Bind   (ICustomVarRegistry* registry);
    void Unbind ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��室 ��� ��६����� / ��६����� �� ��᪥
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef ICustomVarRegistry::EnumHandler EnumHandler;

    void ForEach (const EnumHandler& handler);
    void ForEach (const char* mask, const EnumHandler& handler);

  private:
    ICustomVarRegistry* impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��뫪� �� ���� ॥��� ��६����� ����� ���ன ��稭����� �� prefix
///////////////////////////////////////////////////////////////////////////////////////////////////
class RegistryReference : public VarRegistry
{
  RegistryReference (const char* prefix, const VarRegistry& source);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��뫪� �� ���� ॥��� ��६����� ����� ���ன ��稭����� �� prefix
///////////////////////////////////////////////////////////////////////////////////////////////////
class StringRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭��/��⠭���� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* GetValue (const char* var_name) const;
          void  SetValue (const char* var_name, const char* value);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RemoveVariable (const char* var_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�஢�ઠ ������ ��६�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasVariable (const char* var_name) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭�� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    VarRegistry GetRegistry () const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���⠢��� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
class CompositeVarRegistry
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��ᮥ�������/��ᮥ������� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Attach (const char* prefix, const VarRegistry& registry);
    void Detach (const char* prefix);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����祭�� ॥���
///////////////////////////////////////////////////////////////////////////////////////////////////
    VarRegistry GetComposite () const;

  private:
    struct Impl;
    Impl* impl;
};

}

#endif