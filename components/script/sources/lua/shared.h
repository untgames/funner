#ifndef SCRIPTLIB_LUA_SHARED_HEADER
#define SCRIPTLIB_LUA_SHARED_HEADER

#include <script/interpreter.h>
#include <script/environment.h>

#include <stl/hash_map>

#include <xtl/any.h>
#include <xtl/connection.h>
#include <xtl/shared_ptr.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/iterator.h>
#include <xtl/bind.h>
#include <xtl/reference_counter.h>

#include <common/heap.h>
#include <common/strlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

namespace script
{

namespace lua
{

//forward declaration
class Interpreter;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ����������� ���� ������ "�� ���������"
///////////////////////////////////////////////////////////////////////////////////////////////////
extern const char* VARIANT_DEFAULT_TYPE_NAME;

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ������ lua
///////////////////////////////////////////////////////////////////////////////////////////////////
class StateHolder
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    StateHolder  ();
    ~StateHolder ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    lua_State* State () const { return state; }

  private:
    StateHolder (const StateHolder&); //no impl
    StateHolder& operator = (const StateHolder&); //no impl

  protected:
    lua_State* state;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///����
///////////////////////////////////////////////////////////////////////////////////////////////////
class Stack: public IStack
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Stack (lua_State* state, Environment& environment);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ���������� � �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    size_t Size ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    float       GetFloat   (size_t index);
    int         GetInteger (size_t index);
    void*       GetPointer (size_t index);
    const char* GetString  (size_t index);
    const char* GetSymbol  (size_t index);
    xtl::any&   GetVariant (size_t index);

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� � ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Push       (float value);
    void Push       (int value);
    void Push       (void* pointer);
    void Push       (const char* string);
    void Push       (const xtl::any& object);
    void PushSymbol (const char* string);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ���������� �� �����
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Pop (size_t arguments_count);

  private:
    lua_State*   state;
    Environment& environment;
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� Lua
///////////////////////////////////////////////////////////////////////////////////////////////////
class Library: public xtl::reference_counter
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������������ / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Library  (Interpreter& interpreter, const char* name, InvokerRegistry& registry);
    ~Library ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������/�������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterInvoker   (const char* invoker_name, Invoker& invoker);
    void UnregisterInvoker (const char* invoker_name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� �����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Destroy ();

  private:
    Library (const Library&); //no impl
    Library& operator = (const Library&); //no impl

  private:
    lua_State*           state;                            //��������� Lua
    Interpreter&         interpreter;                      //�������������
    InvokerRegistry&     registry;                         //������ ������
    stl::string          table_name;                       //��� �������
    bool                 is_global;                        //�������� �� ���������� ����������
    xtl::auto_connection on_register_invoker_connection;   //���������� ����������� �����
    xtl::auto_connection on_unregister_invoker_connection; //���������� �������� �����
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///������������� Lua
///////////////////////////////////////////////////////////////////////////////////////////////////
class Interpreter: public IInterpreter, public StateHolder, public xtl::reference_counter
{
  public:
    typedef xtl::shared_ptr<Environment> EnvironmentPointer;
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� / ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    Interpreter  (const EnvironmentPointer&);
    ~Interpreter ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///��� ��������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    const char* Name ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///���� ����������
///////////////////////////////////////////////////////////////////////////////////////////////////
    IStack& Stack ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    bool HasFunction (const char* name);

///////////////////////////////////////////////////////////////////////////////////////////////////
///���������� ������ ������������� ���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void DoCommands (const char* buffer_name, const void* buffer, size_t buffer_size, const LogFunction& log);

///////////////////////////////////////////////////////////////////////////////////////////////////
///����� ������� ���
///////////////////////////////////////////////////////////////////////////////////////////////////
    void Invoke (size_t arguments_count, size_t results_count);

///////////////////////////////////////////////////////////////////////////////////////////////////
///������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void AddRef  ();
    void Release ();

  private:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�����������/�������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    void RegisterLibrary   (const char* name, InvokerRegistry& registry);
    void UnregisterLibrary (const char* name);

  private:
    typedef xtl::intrusive_ptr<Library>                           LibraryPtr;
    typedef stl::hash_map<stl::hash_key<const char*>, LibraryPtr> LibraryMap;

  private:
    EnvironmentPointer    environment;                  //���������� ���������
    lua::Stack            stack;                        //���� ����������
    LibraryMap            libraries;                    //����� ���������
    xtl::auto_connection  on_create_library_connection; //���������� �� ������� �������� ����������
    xtl::auto_connection  on_remove_library_connection; //���������� �� ������� �������� ����������
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������
///////////////////////////////////////////////////////////////////////////////////////////////////
int variant_destroy   (lua_State*); //�������� ������� ����������� ���� ������
int variant_tostring  (lua_State*); //������ � ������ ��������� ������� ����������������� ���� ������
int safe_call         (lua_State*, int (*f)(lua_State*)); //���������� ����� �����

}

}

#endif
