#include "shared.h"

using namespace common;
using namespace script::lua;

namespace
{

/*
    ���������
*/

const size_t STACK_DUMP_BUFFER_RESERVE = 128; //������ ������, ������������� ��� ����� ����� ���

/*
    �������
*/

//��������� ������ � ������ ������
stl::string get_lua_position (lua_State* state)
{
  stl::string buffer;  
  lua_Debug   debug;
  
  for (int level=0; ; level++)
  {
    if (!lua_getstack (state, level, &debug))
      break;
      
    lua_getinfo (state, "Sln", &debug);
    
    if (debug.currentline == -1)
      continue;
    
    if (debug.name) buffer += common::format ("\n    at %s(%d): function=\"%s\"", debug.short_src, debug.currentline, debug.name);
    else            buffer += common::format ("\n    at %s(%d)", debug.short_src, debug.currentline);
  }

  return buffer;
}

//�������, ���������� ��������� ������ ��� �������� �������� ����������������� ���� ������
int unsafe_variant_destroy (lua_State* state)
{
  xtl::any* variant = reinterpret_cast<xtl::any*> (lua_touserdata (state, -1));

  if (variant && lua_getmetatable (state, -1))
  {
      //��� ���������������� ���� ������, �������� � �����, ���������� � xtl::any*. �������� ���������� ���������� �� ���������
    
    lua_pop (state, 1);
    
    stl::destroy (variant);
  }

  return 0;
}

//������ � ������ ��������� ������� ����������������� ���� ������
int unsafe_variant_tostring (lua_State* state)
{
  xtl::any* variant = reinterpret_cast<xtl::any*> (lua_touserdata (state, -1));
  
  if (variant && lua_getmetatable (state, -1))
  {
    lua_pop (state, 1);
    
    stl::string buffer;

    to_string      (buffer, *variant);
    lua_pushstring (state, buffer.c_str ());

    return 1;
  }

  return 0;
}

}

namespace script
{

namespace lua
{

//���������� ����� ������
int safe_call (lua_State* state, int (*f)(lua_State*))
{
  try
  {
    return f (state);
  }
  catch (xtl::bad_any_cast& exception)
  {
    luaL_error (state, "%s: %s -> %s%s", exception.what (), exception.source_type ().name (), exception.target_type ().name (),
                get_lua_position (state).c_str ());
  }
  catch (std::exception& exception)
  {
    luaL_error (state, "%s%s", exception.what (), get_lua_position (state).c_str ());
  }
  catch (...)
  {
    luaL_error (state, "%s%s", lua_gettop (state) ? lua_tostring (state, -1) : "internal error", get_lua_position (state).c_str ());
  }

  return 0;
}

//�������� �������
int variant_destroy (lua_State* state)
{
  return safe_call (state, &unsafe_variant_destroy);
}

//������ � ������ ��������� ������� ����������������� ���� ������
int variant_tostring (lua_State* state)
{
  return safe_call (state, &unsafe_variant_tostring);
}

//������ ��������� �����
void dump_stack (lua_State* state, stl::string& buffer)
{
    //�������������� ������ ��� ������ ����� �����
    
  buffer.clear   ();
  buffer.reserve (STACK_DUMP_BUFFER_RESERVE);
  
    //������� ��������� �����

  int count = lua_gettop (state) + 1;    

  for (int i=1; i<count; i++)
  {
      //���������� �����������
    
    if (!buffer.empty ())
      buffer += ", ";
      
      //������ ��������
      
    int type = lua_type (state, i);
      
    switch (type)
    {
      case LUA_TNIL:
        buffer += "NIL";
        break;
      case LUA_TBOOLEAN:
        buffer += lua_toboolean (state, i) ? "true" : "false";
        break;
      case LUA_TLIGHTUSERDATA:
        buffer += "<POINTER>";
        break;
      case LUA_TNUMBER:
        buffer += format ("%.4f", lua_tonumber (state, i));
        break;
      case LUA_TSTRING:
        buffer += format ("'%s'", lua_tostring (state, i));
        break;
      case LUA_TTABLE:
        buffer += "<TABLE>";
        break;
      case LUA_TFUNCTION:
        buffer += "<FUNCTION>";
        break;
      case LUA_TUSERDATA:
      {
        xtl::any* volatile variant = reinterpret_cast<xtl::any*> (lua_touserdata (state, i));
        
        if (!variant)
        {
          buffer += "<NIL>";
          continue;
        }
        
        stl::string value;
        
        try
        {
          variant->to_string (value);
          
          buffer += format ("[%s]", value.c_str ());          
        }
        catch (...)
        {
          buffer += format ("<%s>", variant->castable_type ().name ());
        }

        break;
      }
      case LUA_TTHREAD:
        buffer += "<THREAD>";
        break;
      default:
        buffer += format ("<UNKNOWN: %s>", lua_typename (state, i));
        break;
    }
  }
}

//�������� ����������� ��������� � ���� count ���������� 
void check_stack (lua_State* state, size_t count)
{
  if (!lua_checkstack (state, count))
    throw xtl::format_exception<StackException> ("script::lua::check_stack", "Not enough stack space."
    "Attempt to push %u items in stack with %u items (stack_size=%u)", count, lua_gettop (state), LUAI_MAXCSTACK);
}

namespace
{

//�������� ������� �������� � �����
void check_item_index (lua_State* state, size_t index, const char* function_name)
{
  size_t stack_size = lua_gettop (state) + 1; 

  if (index >= stack_size)
    throw xtl::format_exception<script::ArgumentException> (function_name, "Attempt to get item #%u from stack with %u items", index, stack_size);
}

}

//�������� ������������ ���� ��������, ������������ �� �����
void check_item (lua_State* state, size_t index, int expected_type, const char* function_name)
{
    //�������� ������������ ������� ��������

  check_item_index (state, index, function_name);

    //����������� ���� ��������, ������������ � �����

  int item_type = lua_type (state, index);

    //�������� ������������� �����

  switch (item_type)
  {
    case LUA_TNIL:
      switch (expected_type)
      {
        case LUA_TNUMBER:
        case LUA_TNIL:
        case LUA_TLIGHTUSERDATA:
        case LUA_TBOOLEAN:
          return;
      }
      break;
    case LUA_TNUMBER:
      switch (expected_type)
      {
        case LUA_TNUMBER:
        case LUA_TNIL:
        case LUA_TBOOLEAN:
          return;
      }
      
      break;
    case LUA_TBOOLEAN:
      switch (expected_type)
      {
        case LUA_TNUMBER:
        case LUA_TNIL:
        case LUA_TBOOLEAN:
          return;
      }
      break;
    case LUA_TSTRING:
      switch (expected_type)
      {
        case LUA_TSTRING:
        case LUA_TFUNCTION:
          return;
      }
      break;
    case LUA_TFUNCTION:
      switch (expected_type)
      {
        case LUA_TFUNCTION:
          return;
      }
      break;
    default:
      break;
  }
  
  if (item_type != expected_type)
  {
    throw xtl::format_exception<script::ArgumentException> (function_name, "Bad item #%u type (%s expected, got %s)", index, lua_typename (state, expected_type),
                             lua_typename (state, item_type));
  }  
}

//��������� ��������� �� ������
void raise_error (lua_State* state, const char* source)
{
  try
  {
    const char* reason = lua_tostring (state, -1);

    throw xtl::format_exception<RuntimeException> (source, "%s", reason ? reason : "internal error");
  }
  catch (...)
  {
    lua_pop (state, 1);
    throw;
  }
}

}

}
