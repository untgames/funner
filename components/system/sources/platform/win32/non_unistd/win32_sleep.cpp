#include "../shared.h"

using namespace syslib;

/*
    Приостановка выполнения приложения на miliseconds милисекунд
*/

void Platform::Sleep (size_t miliseconds)
{
  SetLastError (0);
  ::Sleep (miliseconds);
}
