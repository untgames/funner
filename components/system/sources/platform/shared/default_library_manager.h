#ifndef SYSLIB_DEFAULT_LIBRARY_MANAGER_HEADER
#define SYSLIB_DEFAULT_LIBRARY_MANAGER_HEADER

#ifdef LoadLibrary
#undef LoadLibrary
#endif

namespace syslib
{

struct dynamic_library_handle;

typedef dynamic_library_handle* dll_t;

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ��������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DefaultLibraryManager
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������������ ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static dll_t LoadLibrary   (const wchar_t* name);
    static void  UnloadLibrary (dll_t);
    static void* GetSymbol     (dll_t, const char* symbol_name);
};

}

#endif
