#ifndef COMMONLIB_PLATFORM_HEADER
#define COMMONLIB_PLATFORM_HEADER

#include <cstddef>

namespace common
{

//implementation forwards
class ICustomAllocator;
class ICustomFileSystem;

/*
    ���������-��������� ����������
*/

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
class DefaultPlatform
{
  public:
    struct lockable_t { void* data; };
  
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �������������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static ICustomAllocator* GetSystemAllocator ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static ICustomFileSystem* GetFileSystem ();
    static ICustomFileSystem* GetIOSystem   ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t GetMilliseconds ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void InitLockable    (lockable_t&);
    static void DestroyLockable (lockable_t&);
    static void Lock            (lockable_t&);
    static void Unlock          (lockable_t&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� Win32
///////////////////////////////////////////////////////////////////////////////////////////////////
class Win32Platform: public DefaultPlatform
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void InitLockable    (lockable_t&);
    static void DestroyLockable (lockable_t&);
    static void Lock            (lockable_t&);
    static void Unlock          (lockable_t&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Unistd
///////////////////////////////////////////////////////////////////////////////////////////////////
class UnistdPlatform: public DefaultPlatform
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������� ������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static ICustomFileSystem* GetFileSystem ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///������ � ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void InitLockable    (lockable_t&);
    static void DestroyLockable (lockable_t&);
    static void Lock            (lockable_t&);
    static void Unlock          (lockable_t&);
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Darwin
///////////////////////////////////////////////////////////////////////////////////////////////////
class MacOsXPlatform : public UnistdPlatform
{
  public:
    static size_t GetMilliseconds ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _WIN32
  typedef Win32Platform Platform;
#elif defined (__APPLE__)
  typedef MacOsXPlatform Platform;
#elif defined __GNUC__
  typedef UnistdPlatform Platform;
#else
  #error Unknown compiler
#endif

}

#endif
