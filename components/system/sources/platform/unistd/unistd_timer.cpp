#include <unistd.h>

#include <platform/platform.h>

using namespace syslib;

/*
    Приостановка выполнения приложения на miliseconds милисекунд
*/

void Platform::Sleep (size_t miliseconds)
{
  usleep (miliseconds * 1000);
}

