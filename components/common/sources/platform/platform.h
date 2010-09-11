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
    typedef void* lockable_t;

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
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    typedef size_t threadid_t;
    
    static threadid_t GetCurrentThreadId ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void MountSystemPaths ();
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
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static threadid_t GetCurrentThreadId ();
    
///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void MountSystemPaths ();
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

///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� �������������� ������� ����
///////////////////////////////////////////////////////////////////////////////////////////////////
    static threadid_t GetCurrentThreadId ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///Carbon
///////////////////////////////////////////////////////////////////////////////////////////////////
class CarbonPlatform: public UnistdPlatform
{
  public:
///////////////////////////////////////////////////////////////////////////////////////////////////
///��������� ���������� �������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static size_t GetMilliseconds ();

///////////////////////////////////////////////////////////////////////////////////////////////////
///����������� ����� ������������
///////////////////////////////////////////////////////////////////////////////////////////////////
    static void MountSystemPaths ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///iPhone
///////////////////////////////////////////////////////////////////////////////////////////////////
class IPhonePlatform: public UnistdPlatform
{
  public:
    static size_t GetMilliseconds ();
};

///////////////////////////////////////////////////////////////////////////////////////////////////
///�������� ������� ���������
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef BADA_DEVICE
  typedef UnistdPlatform Platform;
#elif defined _WIN32
  typedef Win32Platform Platform;
#elif defined __IPHONE__
  typedef IPhonePlatform Platform;
#elif defined __APPLE__
  typedef CarbonPlatform Platform;
#elif defined __GNUC__
  typedef UnistdPlatform Platform;
#else
  #error Unknown compiler
#endif

}

#endif
