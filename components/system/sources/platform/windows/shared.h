#include <stl/hash_map>
#include <stl/hash_set>

#include <xtl/common_exceptions.h>
#include <xtl/intrusive_ptr.h>
#include <xtl/reference_counter.h>

#include <common/component.h>
#include <common/file.h>
#include <common/log.h>
#include <common/property_map.h>
#include <common/singleton.h>
#include <common/strlib.h>
#include <common/utf_converter.h>
#include <common/xml_writer.h>

#include <syslib/application.h>

#ifdef LoadLibrary
#undef LoadLibrary
#endif

#include <shared/windows.h>

#include <process.h>

#define _WIN32_WINNT 0x0600 //��� ������������� WM_MOUSEWHEEL
#include <windows.h>

#include <mshtml.h>
#include <mshtmhst.h>
#include <mshtmdid.h>
#include <exdispid.h>
#include <exdisp.h>
#include <comdef.h>
#include <wininet.h>

#ifdef WINCE
#else
#include <Wtsapi32.h>

WINGDIAPI  HGDIOBJ   WINAPI SelectObject(HDC,HGDIOBJ);

#endif

namespace syslib
{

//�������� ������ ������������� WinAPI � ��������� ���������� � ������ �� �������
void check_errors    (const char* source);
void raise_error     (const char* source);
void raise_com_error (const char* source, const char* message, HRESULT result);

//��������� ������ � ���������� �� ������
stl::string get_error_message     (DWORD error_code);
stl::string get_com_error_message (HRESULT result);

//������� tls ����
void cleanup_tls ();

}
