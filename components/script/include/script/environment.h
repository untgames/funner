#ifndef SCRIPTLIB_ENVIRONMENT_HEADER
#define SCRIPTLIB_ENVIRONMENT_HEADER

#include <typeinfo>
#include <xtl/functional_fwd>
#include <stl/auto_ptr.h>
#include <script/invoker.h>

namespace script
{

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
enum EnvironmentLibraryEvent
{
  EnvironmentLibraryEvent_OnCreate, //������������ ����� �������� ����� ����������
  EnvironmentLibraryEvent_OnRemove, //������������ ����� ��������� ����������
  
  EnvironmentLibraryEvent_Num
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class Environment
{
  public:
    typedef xtl::function<void (EnvironmentLibraryEvent event, const char* library_id, InvokerRegistry& registry)> EventHandler;
    typedef xtl::iterator<InvokerRegistry>        Iterator;
    typedef xtl::iterator<const InvokerRegistry>  ConstIterator;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Environment  ();
    Environment  (const Environment&);
    ~Environment ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Environment& operator = (const Environment&);
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Iterator      CreateIterator ();
    ConstIterator CreateIterator () const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ����� ���������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* LibraryId (const ConstIterator&) const;    

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� / �������� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InvokerRegistry& CreateLibrary (const char* id);
    void             RemoveLibrary (const char* id);
    void             RemoveAllLibraries ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ���������� ����� C++ RTTI � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterType       (const std::type_info& type, const char* library_id);
    void UnregisterType     (const std::type_info& type);
    void UnregisterAllTypes ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InvokerRegistry* FindLibrary   (const char* id) const;
    InvokerRegistry* FindLibrary   (const std::type_info& type) const;
    const char*      FindLibraryId (const std::type_info& type) const;

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ���������� �� ����� � �������� � � ������ ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    InvokerRegistry& Library (const char* id);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Clear ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ������������ �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    xtl::connection RegisterEventHandler (EnvironmentLibraryEvent event, const EventHandler& handler);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Swap (Environment&);

  private:  
    struct Impl;

    stl::auto_ptr<Impl> impl;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�����
///////////////////////////////////////////////////////////////////////////////////////////////////
void swap (Environment&, Environment&);

}

#endif
