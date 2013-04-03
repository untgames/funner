#include "../shared.h"

#include <wrl/client.h>
#include <ppltasks.h>

#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <locale.h>
#include <wrl/client.h>

#include <xtl/utility>

#include <common/strconv.h>
#include <common/utf_converter.h>

#include <syslib/mutex.h>

namespace syslib
{

/// ������������� �����
stl::string tostring (Platform::String^ input);

/// ������ ���������� � ���������� HRESULT
void raise_com_error (const char* method, HRESULT error);

}
