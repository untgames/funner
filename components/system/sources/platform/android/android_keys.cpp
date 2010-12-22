#include "shared.h"

using namespace syslib;

/*
    ��������� ����� �������
*/

//������������ ����� ������ ��� ����� '\0'
size_t Platform::GetKeyName (ScanCode scan_code, size_t buffer_size, char* buffer)
{
  static const char* METHOD_NAME = "syslib::DefaultPlatform::GetKeyName";

  if (scan_code < 0 || scan_code >= ScanCode_Num)
    throw xtl::make_argument_exception (METHOD_NAME, "scan_code", scan_code);

  if (!buffer && buffer_size)
    throw xtl::make_null_argument_exception (METHOD_NAME, "buffer");

  if (!buffer_size)
    return 0;
    
  strncpy (buffer, "Unknown", buffer_size);

  return strlen (buffer);
}