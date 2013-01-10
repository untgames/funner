#ifndef WP8_COMPATIBILITY_WINDOWS_H_HEADER
#define WP8_COMPATIBILITY_WINDOWS_H_HEADER

#include <../../8.0/Include/windows.h>
#include <minwin/fileapi.h>

#include <signal.h>

#ifdef __cplusplus
extern "C"
{
#endif


__inline DWORD GetTickCount () { return (DWORD)GetTickCount64 (); }

__inline HANDLE GetModuleHandle () { return (HANDLE)0; }

__inline HWND GetDesktopWindow () { return (HWND)0; }

__inline int _getpid () { return (int)GetCurrentProcessId (); }

#ifdef getenv
#undef getenv
#endif

__inline char* getenv (const char* name) { return 0; }

void Sleep (DWORD milliseconds);

__inline DWORD SleepEx (DWORD dwMilliseconds, BOOL bAlertable) { Sleep (dwMilliseconds); return 0; }

HANDLE WINAPI FindFirstFileA (LPCTSTR lpFileName, LPWIN32_FIND_DATA lpFindFileData);

#ifdef UNICODE
#define FindFirstFile  FindFirstFileW
#else
#define FindFirstFile  FindFirstFileA
#endif // !UNICODE

#ifdef __cplusplus
}
#endif

#endif
